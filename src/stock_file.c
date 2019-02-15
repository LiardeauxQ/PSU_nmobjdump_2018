/*
** EPITECH PROJECT, 2018
** stock_file.c
** File description:
** stock file
*/

#include "nm.h"

void *stock_file(char *filename)
{
    struct stat statbuf;
    void *data = NULL;
    int fd = 0;

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "%s: '%s': No such file\n",
                program_invocation_short_name, filename);
        return (NULL);
    }
    if (stat(filename, &statbuf) == -1)
        return (NULL);
    if (check_file_stat(&statbuf, filename) == -1)
        return (NULL); 
    data = mmap(0, statbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    return (data);
}
