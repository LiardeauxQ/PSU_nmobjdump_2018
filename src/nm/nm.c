/*
** EPITECH PROJECT, 2018
** nm.c
** File description:
** description
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

int nm64(char *filename, int file_size, void *data)
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
    print_symbols(symbols, sym_nb);
    free(symbols);
    return (EXIT_SUCCESS);
}

int nm32(char *filename, int file_size, void *data)
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
    print_symbols(symbols, sym_nb);
    free(symbols);
    return (EXIT_SUCCESS);
}

static int nm(char *filename)
{
    struct stat statbuf;
    void *data = stock_file(filename);
    int arch = 0;

    if (data == NULL)
        return (1);
    if (stat(filename, &statbuf) == -1)
        return (print_error(filename, "File not found"));
    if (is_archive_format(data))
        return (parse_archive_file(data + ARMAG_SIZE, filename));
    arch = check_data_conformity(data, filename);
    if (arch == 1)
        return (1);
    return (arch == 64 ? nm64(filename, statbuf.st_size, data)
            : nm32(filename, statbuf.st_size, data));
}

int main(int ac, char **av)
{
    if (ac == 1)
        return (nm("a.out"));
    for (size_t i = 1 ; i < ac ; i++) {
        if (ac > 2)
            printf("\n%s:\n", av[i]);
        if (nm(av[i]))
            return (1);
    }
    return (0);
}
