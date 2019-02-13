/*
** EPITECH PROJECT, 2018
** section_utils.c
** File description:
** section_utils
*/

#include "nm.h"

static void init_symbol(Elf64_Sym *sym, sym_t *data)
{
    if (sym->st_shndx > 100)
        printf("%d %d\n", sym->st_shndx, sym->st_name);
    data->info_type = ELF64_ST_TYPE(sym->st_info);
    data->bind = ELF64_ST_BIND(sym->st_info);
    data->type = 0;
    data->link = sym->st_shndx;
    data->value = sym->st_value;
    if (sym->st_name == 0)
        data->name = NULL;
}

sym_t *get_symbols(Elf64_Ehdr *header, void *data)
{
    Elf64_Shdr *symtab = get_section(header, ".symtab", data);
    Elf64_Shdr *strtab = get_section(header, ".strtab", data);
    Elf64_Sym *symbols = NULL;
    sym_t *symbols_data = NULL;
    size_t ent_nb = 0;

    if (!symtab->sh_entsize)
        return (NULL);
    ent_nb = symtab->sh_size / symtab->sh_entsize;
    symbols = malloc(ent_nb * sizeof(Elf64_Sym));
    symbols_data = malloc(ent_nb * sizeof(sym_t));
    symbols = data + symtab->sh_offset;
    for (size_t i = 0 ; i < ent_nb ; i++) {
        symbols_data[i].name = (char *)(data + strtab->sh_offset
                + symbols[i].st_name);
        symbols_data[i].index = i;
        init_symbol(&symbols[i], &symbols_data[i]);
    }
    return (symbols_data);
}

Elf64_Shdr *get_section(Elf64_Ehdr *header, char *name, void *data)
{
    Elf64_Shdr *sections = data + header->e_shoff;
 
    for (size_t i = 0 ; i < header->e_shnum ; i++) {
        if (!strcmp(data + sections[header->e_shstrndx].sh_offset 
                    + sections[i].sh_name, name))
        return (&sections[i]);
    }
    return (NULL);
}

static char get_common_type(sym_t *symbol)
{
    if (symbol->index == SHN_COMMON)
        return ('C');
    if (symbol->index == SHN_ABS)
        return ('A');
    if (symbol->index == SHN_UNDEF)
        return ('U');
    if (symbol->bind == STB_WEAK) {
        if (!symbol->value)
            return (symbol->info_type == STT_OBJECT ? 'v' : 'w');
        else
            return (symbol->info_type == STT_OBJECT ? 'V' : 'W');
    }
    if (symbol->bind == STB_GNU_UNIQUE)
        return ('u');
    return ('?');
}

static char get_nobits_type(Elf64_Shdr *section)
{
    if (section->sh_type == SHT_NOBITS) {
        if (section->sh_flags == (SHF_WRITE | SHF_ALLOC | SHF_TLS)
                || section->sh_flags == (SHF_ALLOC | SHF_WRITE))
            return ('b');
        else if (section->sh_flags == (SHF_WRITE | SHF_ALLOC | SHF_IA_64_SHORT))
            return ('s');
    }
    return ('?');
}

static char get_progbits_type(Elf64_Shdr *section)
{
    if (section->sh_type == SHT_PROGBITS) {
        switch (section->sh_flags) {
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
        }
    }
    return ('?');
}

static char get_type(Elf64_Shdr *section, Elf64_Shdr *strtab,
        sym_t *symbol, void *data)
{
    char type = '?';

    type = (type == '?') ? get_common_type(symbol) : type;
    type = (type == '?') ? get_nobits_type(section) : type;
    type = (type == '?') ? get_progbits_type(section) : type;
    return (type);
}

void get_symbols_type(Elf64_Ehdr *header, sym_t **symbols, void *data)
{
    Elf64_Shdr *symtab = get_section(header, ".symtab", data);
    Elf64_Shdr *sections = data + header->e_shoff;
    size_t nb = 0;

    if (!symtab->sh_entsize)
        return;
    nb = symtab->sh_size / symtab->sh_entsize;
    for (size_t i = 0 ; i < nb ; i++) {
        if ((*symbols)[i].name == NULL)
            continue;
        if ((*symbols)[i].link > header->e_shnum)
            continue;
        (*symbols)[i].type = get_type(&sections[(*symbols)[i].link],
                &sections[header->e_shstrndx],
                &((*symbols)[i]), data);
    }
}
