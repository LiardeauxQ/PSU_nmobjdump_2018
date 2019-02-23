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
    if (fd == -1)
        return (print_error(filename, "No such file") == 1 ? NULL : NULL);
    if (stat(filename, &statbuf) == -1)
        return (NULL);
    if (check_file_stat(&statbuf, filename) == 1)
        return (NULL); 
    data = mmap(0, statbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (statbuf.st_size < sizeof(Elf32_Ehdr))
        return (NULL);
    close(fd);
    return (data);
}

int check_sections_values64(Elf64_Ehdr *header, char *filename, void *data)
{
    struct stat statbuf;
    Elf64_Shdr *sections = data + header->e_shoff;
    uint16_t shnum = (header->e_shnum == 0)
        ? sections[0].sh_size : header->e_shnum;

    if (header->e_shnum >= SHN_LORESERVE)
        return (print_error(filename, "File truncated")); 
    if (stat(filename, &statbuf) == -1 || header->e_shoff == 0)
        return (print_error(filename, "File format not recognized")); 
    if (header->e_shoff > statbuf.st_size)
        return (print_error(filename, "No symbols"));
    for (size_t i = 0 ; i < shnum ; i++) {
        if (sections[i].sh_offset > statbuf.st_size)
            return (print_error(filename, "File format not recognized"));
    }
    return (0);
}

int check_sections_values32(Elf32_Ehdr *header, char *filename, void *data)
{
    struct stat statbuf;
    Elf32_Shdr *sections = data + header->e_shoff;
    uint16_t shnum = (header->e_shnum == 0)
        ? sections[0].sh_size : header->e_shnum;

    if (header->e_shnum >= SHN_LORESERVE)
        return (print_error(filename, "File truncated")); 
    if (stat(filename, &statbuf) == -1 || header->e_shoff == 0)
        return (print_error(filename, "File format not recognized"));
    if (header->e_shoff > statbuf.st_size)
        return (print_error(filename, "File truncated"));
    for (size_t i = 0 ; i < shnum ; i++) {
        if (sections[i].sh_offset > statbuf.st_size)
            return (print_error(filename, "File format not recognized"));
    }
    return (0);
}
