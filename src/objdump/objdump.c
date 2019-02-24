/*
** EPITECH PROJECT, 2018
** objdump.c
** File description:
** description
*/

#include "nm.h"
#include "objdump.h"

static int objdump64(char *filename, void *data)
{
    if (display_fill_header64(data, filename))
        return (1);
    if (display_sections_content64(data))
        return (1);
    return (0);
}

static int objdump32(char *filename, void *data)
{
    if (display_fill_header32(data, filename))
        return (1);
    if (display_sections_content32(data))
        return (1);
    return (0);
}

int objdump_with_data(void *data, int file_size, char *filename)
{
    int arch = check_data_conformity(data, filename);

    file_size++;
    if (arch == 1)
        return (print_error(filename, "File format not recognized"));
    return ((arch == 64) ? objdump64(filename, data)
            : objdump32(filename, data));
}

int objdump(char *filename)
{
    void *data = stock_file(filename);

    if (data == NULL)
        return (1);
    if (is_archive_format(data))
        return (parse_archive_file(data + ARMAG_SIZE, filename,
                    &objdump_with_data));
    return (objdump_with_data(data, 0, filename));
}

int main(int ac, char **av)
{
    int tmp = 0;
    int ret = 0;

    if (ac == 1)
        return (objdump("a.out"));
    for (size_t i = 1 ; av[i] != NULL ; i++) {
        tmp = objdump(av[i]);
        ret = (tmp == 1) ? tmp : ret;
    }
    return (ret);
}
