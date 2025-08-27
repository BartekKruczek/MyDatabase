// create - open - delete functions
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "file.h"

int create_file(char *filepath){
    int fd = open(filepath, O_RDWR); // should always be -1

    if (fd != -1){
        close(fd);
        printf("File already exists\n");
        return -1;
    }

    fd = open(filepath, O_CREAT | O_RDWR, 0644);

    if (fd == -1){
        perror("open");
        return -1;
    }

    return fd;
}

int open_file(char *filepath){
    int fd = open(filepath, O_RDWR);

    if (fd == -1){
        perror("open");
        return -1;
    }
    return fd;
}

int delete_file(char *filepath){
    if (access(filepath, F_OK) != 0){
        printf("File does not exist\n");
        return -1;
    }

    if (unlink(filepath) == -1){
        perror("unlink");
        return -1;
    }

    return 0;
}