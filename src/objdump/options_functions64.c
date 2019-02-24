/*
** EPITECH PROJECT, 2018
** options_functions.c
** File description:
** description
*/

#include "objdump.h"

int display_fill_header64(void *data, char *filename)
{
    Elf64_Ehdr *header = data;
    unsigned int flags = compute_flags64(header, data);

    printf("\n%s:     file format elf64-x86_64\n", filename);
    printf("architecture: %s, flags 0x%08x:\n",
            (header->e_machine == EM_X86_64) ? "i386:x86_64" : "Unknown",
            flags);
    print_flags(flags);
    printf("start address 0x%016lx\n\n", header->e_entry);
    return (0);
}

static void print_byte_values(Elf64_Shdr *section, void *data, int pos)
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

static void print_ascii_values(Elf64_Shdr *section, void *data, int pos)
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

static void print_section(Elf64_Shdr *section, Elf64_Shdr *strtab, void *data)
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

int display_sections_content64(void *data)
{
    Elf64_Ehdr *hdr = data;
    Elf64_Shdr *secs = data + hdr->e_shoff;
    char *shstrtab = data + secs[hdr->e_shstrndx].sh_offset;
    char *name = NULL;

    if (hdr->e_shoff == 0)
        return (1);
    for (size_t i = 0 ; i < hdr->e_shnum ; i++) {
        name = shstrtab + secs[i].sh_name;
        if (secs[i].sh_size && secs[i].sh_type != SHT_NOBITS
                && secs[i].sh_type != SHT_SYMTAB
                && (secs[i].sh_type != SHT_STRTAB
                    || !strcmp(name, ".dynstr"))
                && ((secs[i].sh_flags & SHF_ALLOC)
                    || (secs[i].sh_type != SHT_RELA
                        && secs[i].sh_type != SHT_REL)))
            print_section(&secs[i], &secs[hdr->e_shstrndx], data);
     }
    return (0);
}
