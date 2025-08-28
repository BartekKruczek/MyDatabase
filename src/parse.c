#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <arpa/inet.h>

#include "../include/parse.h"

int create_db_header(struct header_t **header_out){
    struct header_t *header = calloc(1, sizeof(struct header_t));

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


int validate_db_header(int fd, struct header_t **header_out){
    struct header_t *header = calloc(1, sizeof(struct header_t));
    struct stat dbstat = {0};

    if (fd < 0){
        perror("fd");
        return -1;
    }

    if (header == NULL){
        perror("header");
        return -1;
    }

    if (read(fd, header, sizeof(struct header_t)) != sizeof(struct header_t)){
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
    
    return 0;
}

void output_to_db_file(int fd, struct header_t *header){
    if (fd < 0){
        perror("fd");
        return;
    }

    header->magic = ntohl(header->magic);
    header->version = ntohs(header->version);
    header->count = ntohs(header->count);
    header->file_size = ntohl(header->file_size);

    lseek(fd, 0, SEEK_SET);

    write(fd, header, sizeof(struct header_t));

    return;
}