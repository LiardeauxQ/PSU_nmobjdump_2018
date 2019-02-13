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
    int index;
    unsigned int value;
    char *name;
} sym_t;

/* section_utils.c */

sym_t *get_symbols(Elf64_Ehdr *header, void *data);
void get_symbols_type(Elf64_Ehdr *header, sym_t **symbols, void *data);
Elf64_Shdr *get_section(Elf64_Ehdr *header, char *name, void *data);

/* nm.c */

int nm(char *filename);

#endif
