#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <arpa/inet.h>

#include "../include/parse.h"

int create_db_header(struct dbheader_t **header_out){
    struct dbheader_t *header = calloc(1, sizeof(struct dbheader_t));

    if (header == NULL){
        perror("calloc");
        return -1;
    }

    header->magic = HEADER_MAGIC;
    header->version = 1;
    header->count = 0;
    header->file_size = 0;

    *header_out = header;

    return 0;
}


int validate_db_header(int fd, struct dbheader_t **header_out){
    struct dbheader_t *header = calloc(1, sizeof(struct dbheader_t));
    struct stat dbstat = {0};

    if (fd < 0){
        perror("fd");
        return -1;
    }

    if (header == NULL){
        perror("header");
        return -1;
    }

    if (read(fd, header, sizeof(struct dbheader_t)) != sizeof(struct dbheader_t)){
        perror("read");
        return -1;
    }

    header->magic = ntohl(header->magic);
    header->version = ntohs(header->version);
    header->count = ntohs(header->count);
    header->file_size = ntohl(header->file_size);

    if (header->magic != HEADER_MAGIC){
        printf("Invalid magic number\n");
        free(header);
        return -1;
    }

    if (header->version != 1){
        printf("Invalid version\n");
        free(header);
        return -1;
    }

    fstat(fd, &dbstat);
    if (header->file_size != dbstat.st_size){
        printf("Corrupted databse\n");
        free(header);
        return -1;
    }

    *header_out = header;
}

int add_employee(struct dbheader_t *header, struct employee_t *employee, char *addstring){
    if (addstring == NULL){
        printf("Please provide employee data\n");
        return -1;
    }

    char *name = strtok(addstring, ";");
    char *address = strtok(NULL, ";");
    char *hours = strtok(NULL, ";");

    if (name == NULL || address == NULL || hours == NULL){
        printf("Please provide valid employee data\n");
        return -1;
    }

    strncpy(employee[header->count-1].name, name, sizeof(employee[header->count-1].name));
    strncpy(employee[header->count-1].address, address, sizeof(employee[header->count-1].address));

    employee[header->count-1].hours = htonl(atoi(hours));
    printf("Employee added successfully\n");
    
}

int read_employees(int fd, struct dbheader_t *header, struct employee_t **employees_out){
    if (fd < 0){
        perror("fd");
        return -1;
    }

    int count = header->count;

    struct employee_t *employees = calloc(count, sizeof(struct employee_t));
    if (employees == NULL){
        printf("Malloc failed\n");
        return -1;
    }

    read(fd, employees, count*sizeof(struct employee_t));

    int i = 0;
    for (; i < count; i++){
        employees[i].hours = ntohl(employees[i].hours);
    }

    *employees_out = employees;
}

int output_file(int fd, struct dbheader_t *header, struct employee_t *employees){
    if (fd < 0){
        perror("fd");
        return -1;
    }

    int realcount = header->count;

    header->magic = htonl(header->magic);
    header->version = htons(header->version);
    header->count = htons(header->count);
    header->file_size = htonl(sizeof(struct dbheader_t) + sizeof(struct employee_t) * realcount);

    lseek(fd, 0, SEEK_SET);

    write(fd, header, sizeof(struct dbheader_t));

    for (int i = 0; i < realcount; i++){
        write(fd, &employees[i].hours, sizeof(struct employee_t));
    }
    printf("File written successfully\n");
}