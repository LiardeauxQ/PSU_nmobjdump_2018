/*
** EPITECH PROJECT, 2018
** archive_manager.c
** File description:
** archive manager
*/

#include "nm.h"

ar_hdr_t create_archive_header(void *data)
{
    ar_hdr_t cvt = {0};

    fetch_archive_header_name(data, &cvt);
    cvt.date = atonl(data + 16, 12);
    cvt.uid = atoni(data + 28, 6);
    cvt.gid = atoni(data + 34, 6);
    cvt.mode = atoni(data + 40, 8);
    cvt.size = atoni(data + 48, 10);
    cvt.fmag = strndup(data + 58, 2);
    return (cvt);
}

int is_archive_format(void *data)
{
    return (strncmp(data, ARMAG, ARMAG_SIZE) == 0 ? 1 : 0);
}

int nm_with_data(void *data, int file_size, char *filename)
{
    int arch = check_data_conformity(data, filename);

    if (arch == 1)
        return (1);
    printf("\n%s:\n", filename);
    return (arch == 64 ? nm64(filename, file_size, data) : nm32(filename,
                file_size, data));
}

int parse_archive_file(void *data, char *filename)
{
    struct stat statbuf;
    ar_hdr_t *array = NULL;
    size_t size = 0;
    size_t current_size = 0;

    if (stat(filename, &statbuf) == -1)
        return (1);
    while (current_size < statbuf.st_size - ARMAG_SIZE) {
        array = realloc(array, ++size * sizeof(ar_hdr_t));
        array[size - 1] = create_archive_header(data + current_size);
        array[size - 1].start_off = current_size + AR_HEADER_SIZE;
        current_size += AR_HEADER_SIZE + array[size - 1].size;
        if (size > 2) {
            update_name(data + array[1].start_off + array[size - 1].str_off,
                    &array[size - 1]);
            nm_with_data(data + array[size - 1].start_off,
                    array[size - 1].size, array[size - 1].name);
        }
    }
    free(array);
    return (0);
}
