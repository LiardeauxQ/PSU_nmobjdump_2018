/*
** EPITECH PROJECT, 2018
** section_utils.c
** File description:
** section_utils
*/

#include "nm.h"

static void init_symbol(Elf64_Sym *sym, sym_t *data)
{
    data->info_type = ELF64_ST_TYPE(sym->st_info);
    data->bind = ELF64_ST_BIND(sym->st_info);
    data->type = 0;
    data->link = sym->st_shndx;
    data->value = sym->st_value;
    if (sym->st_name == 0)
        data->name = NULL;
}

sym_t *get_symbols64(Elf64_Ehdr *header, void *data)
{
    Elf64_Shdr *symtab = get_section64(header, ".symtab", data);
    Elf64_Shdr *strtab = get_section64(header, ".strtab", data);
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

Elf64_Shdr *get_section64(Elf64_Ehdr *header, char *name, void *data)
{
    Elf64_Shdr *sections = data + header->e_shoff;
 
    for (size_t i = 0 ; i < header->e_shnum ; i++) {
        if (!strcmp(data + sections[header->e_shstrndx].sh_offset 
                    + sections[i].sh_name, name))
        return (&sections[i]);
    }
    return (NULL);
}

void get_symbols_type64(Elf64_Ehdr *header, sym_t **symbols, void *data)
{
    Elf64_Shdr *symtab = get_section64(header, ".symtab", data);
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
        (*symbols)[i].type = get_type64(&sections[(*symbols)[i].link],
                &sections[header->e_shstrndx],
                &((*symbols)[i]), data);
    }
}
