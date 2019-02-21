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

typedef struct sym_s {
    unsigned char info_type;
    unsigned char bind;
    char type;
    int link;
    uint16_t index;
    unsigned long long value;
    char *name;
} sym_t;

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

char get_type64(Elf64_Shdr *section, Elf64_Shdr *strtab,
		sym_t *symbol, void *data);

/* type32.c */

char get_type32(Elf32_Shdr *section, Elf32_Shdr *strtab,
		sym_t *symbol, void *data);

/* manage_error.c */

int check_file_stat(struct stat *statebuf, char *filename);
int check_data_conformity(void *data, char *filename);

/* stock_file.c */

void *stock_file(char *filename);
int check_sections_values64(Elf64_Ehdr *header, char *filename, void *data);
int check_sections_values32(Elf32_Ehdr *header, char *filename, void *data);

/* nm.c */

int nm64(char *filename, void *data);
int nm32(char *filename, void *data);

#endif
