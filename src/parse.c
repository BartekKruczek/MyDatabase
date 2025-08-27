#include <stdio.h>
#include <stdlib.h>

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