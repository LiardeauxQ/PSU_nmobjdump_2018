/*
** EPITECH PROJECT, 2018
** options_functions.c
** File description:
** options functions
*/

#include "objdump.h"
#include "flags.h"

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

int display_sections_content(void *data, char *filename)
{
    return (0);
}
