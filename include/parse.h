#ifndef PARSE_H
#define PARSE_H

#define HEADER_MAGIC 0x4c4c4144

struct header_t {
    unsigned int magic;
    unsigned short version;
    unsigned short count;
    unsigned int file_size;
};

int create_db_header(struct header_t **header_out);
int validate_db_header(int fd, struct header_t **header_out);
void output_to_db_file(int fd, struct header_t *header); // write something to db file

#endif