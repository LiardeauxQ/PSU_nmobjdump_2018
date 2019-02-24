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

int nm_with_data(void *data, int file_size, char *filename)
{
    int arch = check_data_conformity(data, filename);

    if (arch == 1)
        return (1);
    return (arch == 64 ? nm64(filename, file_size, data, 3)
            : nm32(filename, file_size, data, 3));
}

static int nm(char *filename, int argc)
{
    struct stat statbuf;
    void *data = stock_file(filename);
    int arch = 0;

    if (data == NULL)
        return (1);
    if (stat(filename, &statbuf) == -1)
        return (print_error(filename, "File not found"));
    if (is_archive_format(data))
        return (parse_archive_file(data + ARMAG_SIZE,
                    filename, &nm_with_data));
    arch = check_data_conformity(data, filename);
    if (arch == 1)
        return (1);
    return (arch == 64 ? nm64(filename, statbuf.st_size, data, argc)
            : nm32(filename, statbuf.st_size, data, argc));
}

int main(int ac, char **av)
{
    int ret = 0;
    int tmp = 0;

    if (ac == 1)
        return (nm("a.out", ac));
    for (int i = 1 ; i < ac ; i++) {
        tmp = nm(av[i], ac);
        ret = (tmp == 1) ? tmp : ret;
    }
    return (ret);
}
