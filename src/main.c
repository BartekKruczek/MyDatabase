// main pipeline executor, handles file and parser 
#include <getopt.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/file.h"

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
    bool newfile = false;
    bool deletefile = false;

    /*
    n -> newfile name
    f -> file path
    d -> delete file path 
    h -> print help
    */
    while ((c = getopt(argc, argv, "ndhf:")) != -1){
        switch (c){
            case 'n':
                newfile = true;
                break;
            case 'f':
                filepath = optarg;
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
        return 0;
    } else {
        db_fd = open_file(filepath);

        if (db_fd == -1){
            printf("Failed to open file\n");
            return 0;
        }
        
        printf("File opened successfully\n");
        return 0;
    }

    return 0;
}