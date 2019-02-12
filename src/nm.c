/*
** EPITECH PROJECT, 2018
** nm.c
** File description:
** nm
*/

#include "nm.h"

static void *stock_file(char *filename)
{
    struct stat statbuf;
    void *data = NULL;
    int fd = open(filename, O_RDONLY);

    if (stat(filename, &statbuf) == -1)
        return (NULL);
    data = mmap(0, statbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    return (data);
}

static void get_symbols(Elf64_Shdr *symtab, Elf64_Shdr *strtab, void *data)
{
    Elf64_Sym *symbols;
    sym_t *symbols_data;
    size_t ent_nb = 0;

    if (!symtab->sh_entsize)
        return;
    ent_nb = symtab->sh_size / symtab->sh_entsize;
    symbols = malloc(ent_nb * sizeof(Elf64_Sym));
    symbols_data = malloc(ent_nb * sizeof(sym_t));
    symbols = data + symtab->sh_offset;
    for (size_t i = 0 ; i < ent_nb ; i++) {
        symbols_data[i].name = (char *)(data + strtab->sh_offset
                + symbols[i].st_name);
        printf("elf symbol: %s\n", symbols_data[i].name);
    }
}

int nm(char *filename)
{
    void *data = stock_file(filename);
    Elf64_Ehdr *header = NULL;
    Elf64_Shdr *secs = NULL;
    Elf64_Shdr *symtab = NULL;
    Elf64_Shdr *strtab = NULL;
    Elf64_Shdr *shstrtab = NULL;

    if (data == NULL)
        return (EXIT_ERROR);
    header = data;
    secs = calloc(1, header->e_shnum * sizeof(Elf64_Shdr));
    secs = data + header->e_shoff;
    shstrtab = &secs[header->e_shstrndx];
    for (size_t i = 0 ; i < header->e_shnum ; i++) {
        if (!strcmp(data + shstrtab->sh_offset + secs[i].sh_name, ".symtab"))
            symtab = &secs[i];
        if (!strcmp(data + shstrtab->sh_offset + secs[i].sh_name, ".strtab"))
            strtab = &secs[i];
    }
    get_symbols(symtab, strtab, data);
    return (0);
}

int main(int ac, char **av)
{
    int rt = 0;
    
    if (ac == 1)
        rt = nm("a.out");
    else
        rt = nm(av[1]);
    return (rt);
}
