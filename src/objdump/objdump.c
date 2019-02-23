/*
** EPITECH PROJECT, 2018
** objdump.c
** File description:
** description
*/
#include "nm.h"
#include "objdump.h"

int objdump(char *filename)
{
    void *data = stock_file(filename);
    int ret = 0;
    int arch = 0;

    if (data == NULL)
        return (1);
    arch = check_data_conformity(data, filename);
    if (arch == 64) {
        ret = display_fill_header64(data, filename);
        ret = (display_sections_content64(data, filename) == 0) ? ret : 1;
        return (ret);
    } else if (arch == 32) {
        ret = display_fill_header32(data, filename);
        ret = (display_sections_content32(data, filename) == 0) ? ret : 1;
        return (ret);
    }
    return (print_error(filename, "File format not recognized"));
}

int main(int ac, char **av)
{
    if (ac == 1)
        return (objdump("a.out"));
    for (size_t i = 1 ; av[i] != NULL ; i++)
        if (objdump(av[i]) == 1)
            return (1);
    return (0);
}
