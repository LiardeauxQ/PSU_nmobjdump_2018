/*
** EPITECH PROJECT, 2018
** options_functions.c
** File description:
** options functions
*/

#include "objdump.h"

static char const *format[] = {"x86", "x86-64"};

int display_fill_header(void *data, char *filename)
{
    Elf64_Ehdr *header = data;
    unsigned char arch = (header->e_ident[EI_CLASS] == ELFCLASS32) ? 32 : 64;
    unsigned int flags = compute_flags(header, data);

    printf("\n%s:\tfile format elf%d-%s\n", filename, arch, format[arch / 64]);
    printf("architecture: %s flags 0x%08x:\n",
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

void print_section(Elf64_Shdr *section, Elf64_Shdr *strtab, void *data)
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

int display_sections_content(void *data, char *filename)
{
    Elf64_Ehdr *header = data;
    Elf64_Shdr *secs = data + header->e_shoff;
    char *shstrtab = data + secs[header->e_shstrndx].sh_offset;

    for (size_t i = 0 ; i < header->e_shnum ; i++) {
        if (secs[i].sh_type != SHT_NOBITS && secs[i].sh_type
                != SHT_SYMTAB && data + secs[i].sh_offset != (void*)shstrtab
                && strcmp(&shstrtab[secs[i].sh_name], ".strtab") != 0)
            print_section(&secs[i], &secs[header->e_shstrndx], data);
    }
    return (0);
}
