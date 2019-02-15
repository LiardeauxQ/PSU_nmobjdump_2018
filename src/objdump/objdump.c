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

    if (data == NULL)
        return (84);
    ret = display_fill_header(data, filename);
    ret = (display_sections_content(data, filename) == 0) ? ret : 84;
    return (ret);
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
