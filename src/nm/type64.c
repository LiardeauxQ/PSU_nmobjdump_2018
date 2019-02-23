/*
** EPITECH PROJECT, 2018
** type.c
** File description:
** description
*/

#include "nm.h"

static char get_common_type(sym_t *symbol)
{
    if (symbol->link == SHN_COMMON)
        return ('C');
    if (symbol->link == SHN_ABS)
        return ('A');
    if (symbol->bind == STB_WEAK) {
        if (!symbol->value)
            return (symbol->info_type == STT_OBJECT ? 'v' : 'w');
        else
            return (symbol->info_type == STT_OBJECT ? 'V' : 'W');
    }
    if (symbol->link == SHN_UNDEF)
        return ('U');
    if (symbol->bind == STB_GNU_UNIQUE)
        return ('u');
    return (0);
}

static char get_nobits_type(uint64_t flags)
{
    if (flags == (SHF_WRITE | SHF_ALLOC | SHF_TLS) 
            || flags == (SHF_ALLOC | SHF_WRITE))
        return ('b');
    else if (flags == (SHF_WRITE | SHF_ALLOC | SHF_IA_64_SHORT))
        return ('s');
    return (0);
}

static char get_progbits_type(uint64_t flags)
{
    switch (flags) {
    case (SHF_ALLOC):
        return ('r');
    case (SHF_ALLOC | SHF_WRITE):
        return ('d');
    case (SHF_ALLOC | SHF_EXECINSTR):
        return ('t');
    case (SHF_ALLOC | SHF_WRITE | SHF_IA_64_SHORT):
        return ('g');
    case (SHT_NULL):
        return ('n');
    default:
        return ('?');
    }
}

static char get_type(uint64_t flags, uint32_t type)
{
    if ((flags & SHF_WRITE) != SHF_WRITE) {
        if (type != SHT_GROUP)
            return ('n');
        else
            return ('r');
    }
    if (type != SHT_DYNAMIC)
        return ('n');
    return ('d');
}

char get_type64(Elf64_Shdr *section, Elf64_Shdr *strtab,
        sym_t *symbol, void *data)
{
    char type = 0;

    type = (type == 0) ? get_common_type(symbol) : type;
    if (section->sh_type == SHT_NOBITS)
        type = (type == 0) ? get_nobits_type(section->sh_flags) : type;
    if (section->sh_type == SHT_PROGBITS)
        type = (type == 0) ? get_progbits_type(section->sh_flags) : type;
    if (section->sh_type == SHT_FINI_ARRAY
            || section->sh_type == SHT_INIT_ARRAY)
        type = (type == 0) ? 't' : type;
    type = (type == 0) ? get_type(section->sh_flags, section->sh_type) : type;
    type = (symbol->bind == STB_GLOBAL &&
            (type >= 'a' && type < 'v')) ? (type - 32) : type;
    return (type == 0 ? '?' : type);
}
