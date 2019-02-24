/*
** EPITECH PROJECT, 2018
** nm_architecture.c
** File description:
** nm architecture function
*/

#include "nm.h"

int nm64(char *filename, int file_size, void *data, int argc)
{
    Elf64_Ehdr *header = data;
    sym_t *symbols = NULL;
    Elf64_Shdr *symtab = NULL;
    size_t sym_nb = 0;

    if (check_sections_values64(header, filename, file_size, data))
        return (1);
    symbols = get_symbols64(header, data);
    symtab = get_section64(header, ".symtab", data);
    if (symtab == NULL)
        return (print_error(filename, "File format not recognized"));
    get_symbols_type64(header, &symbols, data);
    if (symtab->sh_entsize != 0)
        sym_nb = symtab->sh_size / symtab->sh_entsize;
    order_symbols(symbols, sym_nb);
    if (argc > 2)
        printf("\n%s:\n", filename);
    print_symbols(symbols, sym_nb);
    free(symbols);
    return (EXIT_SUCCESS);
}

int nm32(char *filename, int file_size, void *data, int argc)
{
    Elf32_Ehdr *header = data;
    sym_t *symbols = NULL;
    Elf32_Shdr *symtab = NULL;
    size_t sym_nb = 0;

    if (check_sections_values32(header, filename, file_size, data))
        return (1);
    symbols = get_symbols32(header, data);
    symtab = get_section32(header, ".symtab", data);
    if (symtab == NULL)
        return (print_error(filename, "File format not recognized"));
    get_symbols_type32(header, &symbols, data);
    if (symtab->sh_entsize != 0)
        sym_nb = symtab->sh_size / symtab->sh_entsize;
    order_symbols(symbols, sym_nb);
    if (argc > 2)
        printf("\n%s:\n", filename);
    print_symbols(symbols, sym_nb);
    free(symbols);
    return (EXIT_SUCCESS);
}
