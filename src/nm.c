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

void print_symbols(sym_t *symbols, size_t sym_nb)
{
    for (size_t i = 0 ; i < sym_nb ; i++) {
        if (symbols[i].name == NULL || symbols[i].type == 0)
            continue;
        if (symbols[i].value)
            printf("%016llx %c %s\n", symbols[i].value, symbols[i].type,
                    symbols[i].name);
        else
            printf("%16c %c %s\n", ' ', symbols[i].type, symbols[i].name);
    }
}

int nm(char *filename)
{
    void *data = stock_file(filename);
    Elf64_Ehdr *header = NULL;
    sym_t *symbols = NULL;
    Elf64_Shdr *symtab = NULL;
    size_t sym_nb = 0;

    if (data == NULL)
        return (EXIT_ERROR);
    header = data;
    symbols = get_symbols(header, data);
    get_symbols_type(header, &symbols, data);
    symtab = get_section(header, ".symtab", data);
    if (symtab->sh_entsize != 0)
        sym_nb = symtab->sh_size / symtab->sh_entsize;
    order_symbols(symbols, sym_nb);
    print_symbols(symbols, sym_nb);
    return (EXIT_SUCCESS);
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
