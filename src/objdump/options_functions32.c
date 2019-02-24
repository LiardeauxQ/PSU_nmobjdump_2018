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

int display_sections_content32(void *data)
{
    Elf32_Ehdr *hdr = data;
    Elf32_Shdr *secs = data + hdr->e_shoff;
    char *shstrtab = data + secs[hdr->e_shstrndx].sh_offset;
    char *name = NULL;

    if (hdr->e_shoff == 0)
        return (1);
    for (size_t i = 0 ; i < hdr->e_shnum ; i++) {
        name = shstrtab + secs[i].sh_name;
        if ((hdr->e_type == ET_REL && secs[i].sh_type == SHT_RELA)
                || secs[i].sh_size == 0 || secs[i].sh_type == SHT_NOBITS
                || !strcmp(name, ".bss") || !strcmp(name, ".strtab")
                || !strcmp(name, ".symtab") || !strcmp(name, ".shstrtab"))
            continue;
                print_section(&secs[i], &secs[hdr->e_shstrndx], data);
    }
    return (0);
}
