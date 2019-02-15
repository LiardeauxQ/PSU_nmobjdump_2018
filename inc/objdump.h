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

#define EXIT_ERROR	84

/* section_utils64.c */

Elf64_Shdr *get_section64(Elf64_Ehdr *header, char *name, void *data);

/* section_utils32.c */

Elf32_Shdr *get_section32(Elf32_Ehdr *header, char *name, void *data);

/* manage_error.c */

int check_file_stat(struct stat *statebuf, char *filename);
int check_data_conformity(void *data, char *filename);

/* stock_file.c */

void *stock_file(char *filename);

/* options_functions64.c */

int display_fill_header64(void *data, char *filename);
int display_sections_content64(void *data, char *filename);

/* options_functions32.c */

int display_fill_header32(void *data, char *filename);
int display_sections_content32(void *data, char *filename);

/* flags.c */

unsigned int compute_flags32(Elf32_Ehdr *header, void *data);
unsigned int compute_flags64(Elf64_Ehdr *header, void *data);
void print_flags(unsigned int flags);

/* objdump.c */

#endif
