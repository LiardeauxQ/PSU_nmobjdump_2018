/*
** EPITECH PROJECT, 2018
** flags.c
** File description:
** description
*/

#include "flags.h"
#include "objdump.h"

static const flag_t flags_info[HANDLE_FLAGS] = {
    {"HAS_RELOC", HAS_RELOC},
    {"EXEC_P", EXEC_P},
    {"HAS_SYMS", HAS_SYMS},
    {"DYNAMIC", DYNAMIC},
    {"D_PAGED", D_PAGED}};

unsigned int compute_flags32(Elf32_Ehdr *hdr, void *data)
{
    unsigned int flags = 0;
    Elf32_Shdr *sect = NULL;
    size_t i = 0;

    while (i < hdr->e_shnum) {
        sect = data + (hdr->e_shoff + (hdr->e_shentsize * i++));
        flags |= HAS_RELOC * (hdr->e_type == ET_REL
                && (sect->sh_type == SHT_RELA || sect->sh_type == SHT_REL)) |
            EXEC_P * (hdr->e_type == ET_EXEC) |
            HAS_SYMS * (sect->sh_type == SHT_SYMTAB
                    || sect->sh_type == SHT_DYNSYM) |
            DYNAMIC * (hdr->e_type == ET_DYN) |
            D_PAGED * ((hdr->e_type == ET_EXEC || hdr->e_type == ET_DYN));
    }
    return (flags);
}

unsigned int compute_flags64(Elf64_Ehdr *hdr, void *data)
{
    unsigned int flags = 0;
    Elf64_Shdr *sect = NULL;
    size_t i = 0;

    while (i < hdr->e_shnum) {
        sect = data + (hdr->e_shoff + (hdr->e_shentsize * i++));
        flags |= HAS_RELOC * (hdr->e_type == ET_REL
                && (sect->sh_type == SHT_RELA || sect->sh_type == SHT_REL)) |
            EXEC_P * (hdr->e_type == ET_EXEC) |
            HAS_SYMS * (sect->sh_type == SHT_SYMTAB
                    || sect->sh_type == SHT_DYNSYM) |
            DYNAMIC * (hdr->e_type == ET_DYN) |
            D_PAGED * ((hdr->e_type == ET_EXEC || hdr->e_type == ET_DYN));
    }
    return (flags);
}

/*unsigned int compute_flags64(Elf64_Ehdr *header, void *data)
{
    Elf32_Shdr *secs = data + header->e_shoff;
    unsigned int flags = 0;

    if (header->e_type == ET_EXEC)
        flags |= EXEC_P;
    if (header->e_type == ET_DYN)
        flags |= DYNAMIC;
    if (header->e_type == ET_REL)
        flags |= HAS_RELOC;
    for (size_t i = 0 ; i < header->e_shnum ; i++) {
        if (secs[i].sh_type == SHT_DYNAMIC)
            flags |= D_PAGED;
        if (secs[i].sh_type == SHT_SYMTAB || secs[i].sh_type == SHT_DYNSYM)
            flags |= HAS_SYMS;
    }
    return (flags);
}*/

void print_flags(unsigned int flags)
{
    int first = 0;

    for (size_t i = 0 ; i < HANDLE_FLAGS ; i++)
        if (flags & flags_info[i].value)
            printf("%s%s", ((first++ == 0) ? "" : ", "), flags_info[i].name);
    printf("\n");
}
