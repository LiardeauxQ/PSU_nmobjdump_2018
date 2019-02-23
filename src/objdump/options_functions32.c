/*
** EPITECH PROJECT, 2018
** options_functions.c
** File description:
** description
*/

#include "objdump.h"

int display_fill_header32(void *data, char *filename)
{
    Elf32_Ehdr *header = data;
    unsigned int flags = compute_flags32(header, data);

    printf("\n%s:\tfile format elf32-x86\n", filename);
    printf("architecture: %s flags 0x%08x:\n",
            (header->e_machine == EM_386) ? "i386:x86" : "Unknown",
            flags);
    print_flags(flags);
    printf("start address 0x%08x\n\n", header->e_entry);
    return (0);
}

static void print_byte_values(Elf32_Shdr *section, void *data, int pos)
{
    unsigned char *byte = NULL;

    for (size_t j = 0 ; j < 16 ; j++) {
        if (j % 4 == 0)
            printf(" ");
        if (j + pos >= section->sh_size) {
            printf("  ");
            continue;
        }
        byte = data + section->sh_offset + pos + j;
        printf("%02x", *byte);
    }
}

static void print_ascii_values(Elf32_Shdr *section, void *data, int pos)
{
    unsigned char *byte = NULL;

    for (size_t j = 0 ; j < 16 ; j++) {
        if (j + pos >= section->sh_size) {
            printf(" ");
            continue;
        }
        byte = data + section->sh_offset + pos + j;
        printf("%c", (*byte < 32 || *byte > 126) ? '.' : *byte);
    }
}

static void print_section(Elf32_Shdr *section, Elf32_Shdr *strtab, void *data)
{
    char *name = data + strtab->sh_offset + section->sh_name;

    if (strlen(name) == 0)
        return;
    printf("Contents of section %s:\n", name);
    for (size_t i = 0 ; i < section->sh_size ; i = i + 16) {
        printf(" %04lx", section->sh_addr + i);
        print_byte_values(section, data, i);
        printf(" ");
        print_ascii_values(section, data, i);
        printf("\n");
    }
}

int display_sections_content32(void *data, char *filename)
{
    Elf32_Ehdr *header = data;
    Elf32_Shdr *secs = data + header->e_shoff;
    char *shstrtab = data + secs[header->e_shstrndx].sh_offset;

    for (size_t i = 0 ; i < header->e_shnum ; i++) {
        if (secs[i].sh_type != SHT_NOBITS && secs[i].sh_type
                != SHT_SYMTAB && data + secs[i].sh_offset != (void *)shstrtab
                && strcmp(&shstrtab[secs[i].sh_name], ".strtab") != 0)
            print_section(&secs[i], &secs[header->e_shstrndx], data);
    }
    return (0);
}
