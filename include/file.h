#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdbool.h>

int create_file(char *filepath);
int open_file(char *filepath);
int delete_file(char *filepath);

#endif // FILE_H