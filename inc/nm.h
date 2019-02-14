/*
** EPITECH PROJECT, 2018
** nm.h
** File description:
** nm header
*/

#ifndef NM_H_
#	define NM_H_

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <elf.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define EXIT_ERROR 84

typedef struct sym_s {
    unsigned char info_type;
    unsigned char bind;
    char type;
    int link;
    uint16_t index;
    unsigned long long value;
    char *name;
} sym_t;

/* section_utils.c */

sym_t *get_symbols(Elf64_Ehdr *header, void *data);
void get_symbols_type(Elf64_Ehdr *header, sym_t **symbols, void *data);
Elf64_Shdr *get_section(Elf64_Ehdr *header, char *name, void *data);

/* sort_symbols.c */

void order_symbols(sym_t *symbols, size_t sym_nb);
int ascii_cmp(char *s1, char *s2);

/* type.c */

char get_type(Elf64_Shdr *section, Elf64_Shdr *strtab,
		sym_t *symbol, void *data);

/* nm.c */

int nm(char *filename);

#endif
