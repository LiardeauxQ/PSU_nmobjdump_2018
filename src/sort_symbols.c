/*
** EPITECH PROJECT, 2018
** sort_symbols.c
** File description:
** sort symbols
*/

#include "nm.h"

static int is_useless_char(char c)
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
    char c1 = 0;
    char c2 = 0;

    for (; i < strlen(s1) && j < strlen(s2) ; i++, j++) {
        while (s1[i] != '\0' && is_useless_char(s1[i])) {
            i++;
        }
        while (s2[j] != '\0' && is_useless_char(s2[j])) {
            j++;
        }
        c1 = (s1[i] >= 'A' && s1[i] <= 'Z') ? s1[i] + 32 : s1[i];
        c2 = (s2[i] >= 'A' && s2[j] <= 'Z') ? s2[j] + 32 : s2[j];
        if (c1 == c2)
            continue;
        return ((c1 < c2) ? -1 : 1);
    }
    if (i == j)
        return (0);
    return ((i < j) ? -1 : 1);
}

static void switch_symbol(sym_t *s1, sym_t *s2)
{
    sym_t tmp = *s2;

    s2->info_type = s1->info_type;
    s2->bind = s1->bind;
    s2->type = s1->type;
    s2->link = s1->link;
    s2->index = s1->index;
    s2->value = s1->value;
    s2->name = s1->name;
    s1->info_type = tmp.info_type;
    s1->bind = tmp.bind;
    s1->type = tmp.type;
    s1->link = tmp.link;
    s1->index = tmp.index;
    s1->value = tmp.value;
    s1->name = tmp.name;
}

void order_symbols(sym_t *symbols, size_t sym_nb)
{
    for (size_t i = 0 ; i < sym_nb ; i++) {
        if (symbols[i].name == NULL)
                continue;
        for (size_t j = 0 ; j < sym_nb ; j++) {
            if (symbols[j].name == NULL)
                continue;
            if (ascii_cmp(symbols[i].name, symbols[j].name) == -1)
                switch_symbol(&symbols[i], &symbols[j]);
        }
    }
}
