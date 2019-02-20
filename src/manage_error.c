/*
** EPITECH PROJECT, 2018
** manage_error.c
** File description:
** manage_error
*/

#include "nm.h"

int check_file_stat(struct stat *statbuf, char *filename)
{
    char *binary = (strcmp(program_invocation_short_name, "my_nm") == 0)
        ? "nm" : "objdump";
    DIR *dir = NULL;

    if (S_ISDIR(statbuf->st_mode)) {
        fprintf(stderr, "%s: Warning: '%s' is a directory\n", binary,
                filename);
        return (1);
    }
    if (access(filename, F_OK | R_OK)) {
        fprintf(stderr, "%s: %s: Permission denied\n", binary, filename);
        return (1);
    }
    dir = opendir(filename);
    if (dir != NULL) {
        fprintf(stderr, "%s: Warning: '%s' is a directory\n", binary,
                filename);
        closedir(dir);
        return (1);
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
    char *binary = (strcmp(program_invocation_short_name, "my_nm") == 0)
        ? "nm" : "objdump";

    if (st_cond || nd_cond) {
        fprintf(stderr, "%s: %s: file format not recognized\n",
                binary, filename);
        return (1);
    }
    if (e_ident[4] == ELFCLASS32)
        return (32);
    else if (e_ident[4] == ELFCLASS64)
        return (64);
    return (1);
}
