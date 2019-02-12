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
    char *name;
} sym_t;

int nm(char *filename);

#endif
