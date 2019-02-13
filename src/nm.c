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

int is_useless_char(char c)
{
    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') 
            || (c >= 'A' && c <= 'Z'))
        return (0);
    return (1);
}

int ascii_cmp(char *s1, char *s2)
{
    size_t i = 0;
    size_t j = 0;

    for (; i < strlen(s1) && j < strlen(s2) ; i++, j++) {
        if (s1[i] == s2[j])
            continue;
        while (s1[i++] != '\0' && is_useless_char(s1[i]))
            j++;
        while (s2[j++] != '\0' && is_useless_char(s2[j]))
            i++;
        return ((s1[i] < s2[j]) ? -1 : 1);
    }
    if (i == j)
        return (0);
    return ((i < j) ? -1 : 1);
}

int check_order(sym_t *symbols, size_t sym_nb)
{
    for (size_t i = 0 ; i < sym_nb ; i++) {
        if (symbols[i].name == NULL)
                continue;
        for (size_t j = 0 ; j < sym_nb ; j++) {
            if (symbols[j].name == NULL)
                continue;
            if (ascii_cmp(symbols[i].name, symbols[j].name) == -1) {
                printf("%s %s %d %d\n", symbols[i].name, symbols[j].name, i, j);
                return (1);
            }
        }
    }
    return (0);
}

void order_symbols(sym_t *symbols, size_t sym_nb)
{
    char *tmp = NULL;

    for (size_t i = 0 ; i < sym_nb ; i++) {
        if (symbols[i].name == NULL)
                continue;
        for (size_t j = 0 ; j < sym_nb ; j++) {
            if (symbols[j].name == NULL || i == j)
                continue;
            int val = ascii_cmp(symbols[i].name, symbols[j].name);
            if (val == 1) {
                tmp = symbols[j].name;
                symbols[j].name = symbols[i].name;
                symbols[i].name = tmp;
            }
        }
    }
    if (check_order(symbols, sym_nb))
        order_symbols(symbols, sym_nb);
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
    for (size_t i = 0 ; i < sym_nb ; i++) {
        if (symbols[i].name == NULL)
            continue;
        printf("%c %s\n", symbols[i].type, symbols[i].name);
    }
    order_symbols(symbols, sym_nb);
    printf("\n\n AFTER \n\n");
    for (size_t i = 0 ; i < sym_nb ; i++) {
        if (symbols[i].name == NULL)
            continue;
        printf("%c %s\n", symbols[i].type, symbols[i].name);
    }
    return (EXIT_SUCCESS);
}

int main(int ac, char **av)
{
    int rt = 0;
    char **test = malloc(10 * sizeof(char*));

    /*if (ac == 1)
        rt = nm("a.out");
    else
        rt = nm(av[1]);*/
    test[0] = strdup("main");
    test[1] = strdup("start");
    test[2] = strdup("boby");
    test[3] = strdup("main");
    test[4] = strdup("arthur");
    test[5] = NULL;
    for (size_t i = 0 ; i < 5 ; i++) {
        for (size_t j = 0 ; j < 5 ; j++) {
            if (ascii_cmp(test[i], test[j]) == 1) {
                char *tmp = test[j];
                test[j] = test[i];
                test[i] = tmp;
            }
        }
    }
    for (size_t i = 0 ; i < 5 ; i++) {
        for (size_t j = 0 ; j < 5 ; j++) {
            if (ascii_cmp(test[i], test[j]) == 1) {
                char *tmp = test[j];
                test[j] = test[i];
                test[i] = tmp;
            }
        }
    }
    for (size_t i = 0 ; i < 5 ; i++)
        printf("%s\n", test[i]);
    return (rt);
}
