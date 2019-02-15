/*
** EPITECH PROJECT, 2018
** nm.c
** File description:
** nm
*/

#include "nm.h"

void print_symbols(sym_t *symbols, size_t sym_nb)
{
    for (size_t i = 0 ; i < sym_nb ; i++) {
        if (symbols[i].name == NULL || symbols[i].type == 0)
            continue;
        if (!symbols[i].value && (symbols[i].type == 'U'
                    || symbols[i].type == 'w' || symbols[i].type == 'W'))
            printf("%16c %c %s\n", ' ', symbols[i].type, symbols[i].name);
        else
            printf("%016llx %c %s\n", symbols[i].value, symbols[i].type,
                    symbols[i].name);
    }
}

int nm64(void *data)
{
    Elf64_Ehdr *header = data;
    sym_t *symbols = get_symbols64(header, data);
    Elf64_Shdr *symtab = get_section64(header, ".symtab", data);
    size_t sym_nb = 0;

    if (symtab == NULL)
        return (EXIT_ERROR);
    get_symbols_type64(header, &symbols, data);
    if (symtab->sh_entsize != 0)
        sym_nb = symtab->sh_size / symtab->sh_entsize;
    order_symbols(symbols, sym_nb);
    print_symbols(symbols, sym_nb);
    return (EXIT_SUCCESS);
}

int nm32(void *data)
{
    Elf32_Ehdr *header = data;
    sym_t *symbols = get_symbols32(header, data);
    Elf32_Shdr *symtab = get_section32(header, ".symtab", data);
    size_t sym_nb = 0;

    if (symtab == NULL)
        return (EXIT_ERROR);
    get_symbols_type32(header, &symbols, data);
    if (symtab->sh_entsize != 0)
        sym_nb = symtab->sh_size / symtab->sh_entsize;
    order_symbols(symbols, sym_nb);
    print_symbols(symbols, sym_nb);
    return (EXIT_SUCCESS);
}

int main(int ac, char **av)
{
    char *filename = (ac == 1) ? "a.out" : av[1];
    void *data = NULL;
    int arch = 0;

    data = stock_file(filename);
    if (data == NULL)
        return (EXIT_ERROR);
    arch = check_data_conformity(data, filename);
    if (arch <= 0)
        return (EXIT_ERROR);
    return ((arch == 64) ? nm64(data) : nm32(data));
}
