/*
** EPITECH PROJECT, 2018
** archive_utils.c
** File description:
** archive utils functions
*/

#include "nm.h"

int atoni(const char *nptr, size_t n)
{
    char *tmp = strndup(nptr, n);
    int nbr = 0;

    if (tmp != NULL)
        nbr = atoi(tmp);
    free(tmp);
    return (nbr);
}

long atonl(const char *nptr, size_t n)
{
    char *tmp = strndup(nptr, n);
    long nbr = 0;

    if (tmp != NULL)
        nbr = atol(tmp);
    free(tmp);
    return (nbr);
}

void fetch_archive_header_name(void *data, ar_hdr_t *cvt)
{
    cvt->name = strndup(data, 16);
    if (cvt->name[0] == 47) {
        cvt->str_off = atoi(cvt->name + 1);
        free(cvt->name);
        cvt->name = NULL;
        return;
    }
    for (size_t i = 0 ; cvt->name[i] != '\0' ; i++) {
        if (cvt->name[i] == '\n' || cvt->name[i] == 47) {
            cvt->name[i] = '\0';
            break;
        }
    }
}

void update_name(char *strtab, ar_hdr_t *cvt)
{
    size_t pos = 0;

    if (cvt->name == NULL) {
        while (strtab[pos] != 0 && strtab[pos] != 47)
            pos++;
        cvt->name = strndup(strtab, pos);
    }
}
