/*
** EPITECH PROJECT, 2018
** flags.h
** File description:
** flags
*/

#ifndef __BFD_H_SEEN__
#define __BFD_H_SEEN__

#define BFD_NO_FLAGS    0x00
#define HAS_RELOC       0x01
#define EXEC_P          0x02
#define HAS_LINENO      0x04
#define HAS_DEBUG       0x08
#define HAS_SYMS        0x10
#define HAS_LOCALS      0x20
#define DYNAMIC         0x40
#define WP_TEXT         0x80
#define D_PAGED         0x100

#define HANDLE_FLAGS	5

typedef struct flag_s {
    char *name;
    unsigned int value;
} flag_t;

#endif
