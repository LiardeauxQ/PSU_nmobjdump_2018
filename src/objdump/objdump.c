/*
** EPITECH PROJECT, 2018
** objdump.c
** File description:
** objdump
*/

#include "objdump.h"

int objdump(char *filename)
{
    void *data = stock_file(filename);
    int ret = 0;
    int arch = 0;

    if (data == NULL)
        return (84);
    arch = check_data_conformity(data, filename);
    if (arch == 64) {
        ret = display_fill_header64(data, filename);
        ret = (display_sections_content64(data, filename) == 0) ? ret : 84;
        return (ret);
    } else if (arch == 32) {
        ret = display_fill_header32(data, filename);
        ret = (display_sections_content32(data, filename) == 0) ? ret : 84;
        return (ret);
    }
    return (84);
}

int main(int ac, char **av)
{
    int ret = 0;

    if (ac == 1)
        return (objdump("a.out"));
    for (size_t i = 1 ; av[i] != NULL ; i++)
        ret = (objdump(av[i]) == 0) ? ret : 84;
    return (ret);
}
