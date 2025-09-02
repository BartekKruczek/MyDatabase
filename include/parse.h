#ifndef PARSE_H
#define PARSE_H

#define HEADER_MAGIC 0x4c4c4144

struct header_t {
    unsigned int magic;
    unsigned short version;
    unsigned short count;
    unsigned int file_size;
};

struct employee_t {
    char name[256];
    char address[256];
    unsigned int hours;
};

int create_db_header(struct header_t **header_out);
int validate_db_header(int fd, struct header_t **header_out);
int add_employee(struct header_t *header, struct employee_t *employee, char *addstring);
int read_employees(int fd, struct header_t *header, struct employee_t **employees_out);
void output_to_db_file(int fd, struct header_t *header); // write something to db file

#endif