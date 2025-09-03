// main pipeline executor, handles file and parser 
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/file.h"
#include "../include/parse.h"

void print_help(char *argv[]){
    printf("Usage: %s -n -f -d -h <database file>\n", argv[0]);
    printf("\t -f - (required) path to new file\n");
    printf("\t -n - create new file\n");
    printf("\t -d - delete file\n");
    printf("\t -h - print help\n");
}

int main(int argc, char *argv[]){
    int c = 0;
    int db_fd = -1; // -1 to avoid uninitialized warning
    char *filepath = NULL;
    char *addstring = NULL;
    struct dbheader_t *header = NULL;
    struct employee_t *employees = NULL;
    bool newfile = false;
    bool deletefile = false;

    /*
    n -> newfile name
    f -> file path
    d -> delete file path 
    h -> print help
    */
    while ((c = getopt(argc, argv, "ndhf:a:")) != -1){
        switch (c){
            case 'n':
                newfile = true;
                break;
            case 'f':
                filepath = optarg;
                break;
            case 'a':
                addstring = optarg;
                break;
            case 'd':
                deletefile = true;
                break;
            case 'h':
                print_help(argv);
                break;
            case '?':
                print_help(argv);
                break;
        }
    }

    if (filepath == NULL){
        printf("User must provide file path\n");
        print_help(argv);

        return 0;
    }

    if (deletefile){
        db_fd = delete_file(filepath);

        if (db_fd == -1){
            printf("Failed to delete file\n");
            return 0;
        }

        printf("File deleted successfully\n");
        return 0;
    }

    if (newfile){
        db_fd = create_file(filepath);

        if (db_fd == -1){
            printf("Failed to create file\n");
            return 0;
        }

        printf("File created successfully\n");

        if (create_db_header(&header) == -1){
            printf("Failed to create database header\n");
            return 0;
        }
        printf("Database header created successfully\n");
    } else {
        db_fd = open_file(filepath);

        if (db_fd == -1){
            printf("Failed to open file\n");
            return -1;
        }
        
        printf("File opened successfully\n");

        if (validate_db_header(db_fd, &header) == -1){
            printf("Failed to validate database header\n");
            return -1;
        }
    }

    if (read_employees(db_fd, header, &employees) == -1){
        printf("Failed to read employees\n");
        return -1;
    }

    // add new employee to db
    if (addstring){

        // increase count by 1
        header->count++;
        employees = realloc(employees, header->count*sizeof(struct employee_t));

        add_employee(header, employees, addstring);
    }

    output_file(db_fd, header, employees);

    return 0;
}