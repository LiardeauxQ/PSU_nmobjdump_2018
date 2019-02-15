/*
** EPITECH PROJECT, 2018
** manage_error.c
** File description:
** manage_error
*/

#include "nm.h"

int check_file_stat(struct stat *statbuf, char *filename)
{
    if (S_ISDIR(statbuf->st_mode)) {
        fprintf(stderr, "%s: Warning: '%s' is a directory\n", 
                program_invocation_short_name, filename);
        return (-1);
    }
    if (access(filename, F_OK | R_OK)) {
        fprintf(stderr, "%s: %s: Permission denied\n",
                program_invocation_short_name, filename);
        return (-1);
    }
    return (0);
}

int check_data_conformity(void *data, char *filename)
{
    unsigned char *e_ident = data;
    uint16_t *type = (data + EI_NIDENT);
    int st_cond = (e_ident[0] != ELFMAG0 || e_ident[1] != ELFMAG1
            || e_ident[2] != ELFMAG2 || e_ident[3] != ELFMAG3);
    int nd_cond = (*type != ET_REL && *type != ET_EXEC && *type != ET_DYN);

    if (st_cond || nd_cond) {
        fprintf(stderr, "%s: %s: file format not recognized\n",
                program_invocation_short_name, filename);
        return (-1);
    }
    if (e_ident[4] == ELFCLASS32)
        return (32);
    else if (e_ident[4] == ELFCLASS64)
        return (64);
    return (-1);
}