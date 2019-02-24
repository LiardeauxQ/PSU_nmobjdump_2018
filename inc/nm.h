/*
** EPITECH PROJECT, 2018
** nm.h
** File description:
** nm header
*/

#ifndef NM_H_
#	define NM_H_

#define _GNU_SOURCE

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <elf.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>

#define ARMAG "!<arch>\n"
#define ARMAG_SIZE 8
#define AR_HEADER_SIZE 60
#define ARFMAG "`\n"

typedef struct sym_s {
    unsigned char info_type;
    unsigned char bind;
    char type;
    int link;
    uint16_t index;
    unsigned long long value;
    char *name;
} sym_t;

typedef struct ar_hdr_s {
    uint32_t str_off;
    uint32_t uid;
    uint32_t gid;
    uint32_t mode;
    uint32_t size;
    uint64_t date;
    uint64_t start_off;
    char *fmag;
    char *name;
} ar_hdr_t;

/* section_utils64.c */

sym_t *get_symbols64(Elf64_Ehdr *header, void *data);
void get_symbols_type64(Elf64_Ehdr *header, sym_t **symbols, void *data);
Elf64_Shdr *get_section64(Elf64_Ehdr *header, char *name, void *data);

/* section_utils32.c */

sym_t *get_symbols32(Elf32_Ehdr *header, void *data);
void get_symbols_type32(Elf32_Ehdr *header, sym_t **symbols, void *data);
Elf32_Shdr *get_section32(Elf32_Ehdr *header, char *name, void *data);

/* sort_symbols.c */

void order_symbols(sym_t *symbols, size_t sym_nb);
int ascii_cmp(char *s1, char *s2);

/* type64.c */

char get_type64(Elf64_Shdr *section, sym_t *symbol);

/* type32.c */

char get_type32(Elf32_Shdr *section, sym_t *symbol);

/* manage_error.c */

int check_file_stat(struct stat *statebuf, char *filename);
int check_data_conformity(void *data, char *filename);

/* stock_file.c */

void *stock_file(char *filename);
int check_sections_values64(Elf64_Ehdr *header, char *filename,
    long int file_size, void *data);
int check_sections_values32(Elf32_Ehdr *header, char *filename,
    long int file_size, void *data);

/* archive_utils.c */

int atoni(const char *nptr, size_t n);
long atonl(const char *nptr, size_t n);
void fetch_archive_header_name(void *data, ar_hdr_t *cvt);
void update_name(char *strtab, ar_hdr_t *cvt);

/* archive_manager.c */

ar_hdr_t create_archive_header(void *data);
int is_archive_format(void *data);
int parse_archive_file(void *data, char *filename,
    int (*func)(void*, int, char*));

/* nm.c */

void print_symbols(sym_t *symbols, size_t sym_nb);
int nm_with_data(void *data, int file_size, char *filename);

/* nm_architecture.c */

int nm64(char *filename, int file_size, void *data, int argc);
int nm32(char *filename, int file_size, void *data, int argc);

static inline char *find_bin_name(void)
{
    return ((strcmp(program_invocation_short_name, "my_nm") == 0) ? "nm"
        : "objdump");
}

static inline int print_error(char *filename, char *error_msg)
{
    fprintf(stderr, "%s: %s: %s\n", find_bin_name(),
        filename, error_msg);
    return (1);
}

#endif
