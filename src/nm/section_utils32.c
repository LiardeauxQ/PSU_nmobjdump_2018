/*
** EPITECH PROJECT, 2018
** section_utils.c
** File description:
** description
*/
#include "nm.h"

static void init_symbol(sym_t *sym_data, Elf32_Sym *sym, Elf32_Shdr *strtab,
        void *data)
{
    sym_data->info_type = ELF32_ST_TYPE(sym->st_info);
    sym_data->bind = ELF32_ST_BIND(sym->st_info);
    sym_data->type = 0;
    sym_data->link = sym->st_shndx;
    sym_data->value = sym->st_value;
    if (sym->st_name == 0)
        sym_data->name = NULL;
    else
        sym_data->name = (char *)(data + strtab->sh_offset
            + sym->st_name);
}

sym_t *get_symbols32(Elf32_Ehdr *header, void *data)
{
    Elf32_Shdr *symtab = get_section32(header, ".symtab", data);
    Elf32_Shdr *strtab = get_section32(header, ".strtab", data);
    Elf32_Sym *symbols = NULL;
    sym_t *symbols_data = NULL;
    size_t ent_nb = 0;

    if (symtab == NULL || strtab == NULL || !symtab->sh_entsize)
        return (NULL);
    ent_nb = symtab->sh_size / symtab->sh_entsize;
    symbols_data = malloc(ent_nb * sizeof(sym_t));
    symbols = data + symtab->sh_offset;
    for (size_t i = 0 ; i < ent_nb ; i++) {
        symbols_data[i].index = i;
        init_symbol(&symbols_data[i], &symbols[i], strtab, data);
    }
    return (symbols_data);
}

Elf32_Shdr *get_section32(Elf32_Ehdr *header, char *name, void *data)
{
    Elf32_Shdr *sections = data + header->e_shoff;

    if (header->e_shstrndx > header->e_shnum || header->e_shoff == 0)
        return (NULL);
    for (size_t i = 0 ; i < header->e_shnum ; i++) {
        if (!strcmp(data + sections[header->e_shstrndx].sh_offset
                + sections[i].sh_name, name))
            return (&sections[i]);
    }
    return (NULL);
}

void get_symbols_type32(Elf32_Ehdr *header, sym_t **symbols, void *data)
{
    Elf32_Shdr *symtab = get_section32(header, ".symtab", data);
    Elf32_Shdr *sections = data + header->e_shoff;
    size_t nb = 0;
    uint16_t shnum = (header->e_shnum >= SHN_LORESERVE)
        ? sections[0].sh_size : header->e_shnum;

    if (symtab == NULL || !symtab->sh_entsize || header->e_shoff == 0)
        return;
    nb = symtab->sh_size / symtab->sh_entsize;
    for (size_t i = 0 ; i < nb ; i++) {
        if ((*symbols)[i].name == NULL)
            continue;
        if ((*symbols)[i].link > shnum)
            continue;
        (*symbols)[i].type = get_type32(&sections[(*symbols)[i].link],
            &sections[header->e_shstrndx],
            &((*symbols)[i]), data);
    }
}
