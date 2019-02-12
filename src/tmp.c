/*
** EPITECH PROJECT, 2018
** nm.c
** File description:
** nm
*/

#include "nm.h"

void read_section(int fd, Elf64_Shdr *section)
{
    Elf64_Sym *sym;
    
    if (section->sh_entsize == 0)
        return;
    lseek(fd, section->sh_offset, SEEK_SET);
    sym = malloc(section->sh_size);
    read(fd, sym, section->sh_size);
    for (size_t i = 0 ;  i < (section->sh_size / section->sh_entsize) ; i++)
        printf("\t -> %ld %d %d\n", sym[i].st_size, sym[i].st_name, sym[i].st_shndx);
}

void nm(int fd)
{
    Elf64_Ehdr header = {0};
    Elf64_Shdr *section;
    size_t section_table_size = 0;
    size_t byte = read(fd, &header, sizeof(Elf64_Ehdr));

    printf("-> %ld %ld %d %d %d %d\n", header.e_shoff, header.e_phoff,
                                 header.e_shstrndx, header.e_shnum,
                                 header.e_shentsize, SHN_LORESERVE);

    section_table_size = header.e_shentsize * header.e_shnum;
    section = calloc(1, section_table_size);

    lseek(fd, header.e_shoff, SEEK_SET);
    
    size_t start = (SHN_HIRESERVE - SHN_LORESERVE) / header.e_shentsize;
    byte = read(fd, section, section_table_size);
    for (size_t i = 0 ; i < header.e_shnum ; i++) {
        printf("i %ld => %ld %d %ld %ld\n", i, section[i].sh_offset, section[i].sh_name,
                section[i].sh_size, section[i].sh_entsize);
    }

    char *names = malloc(section[header.e_shstrndx].sh_size * sizeof(char));

    lseek(fd, section[header.e_shstrndx].sh_offset, SEEK_SET);
    read(fd, names, section[header.e_shstrndx].sh_size);
    for (size_t i = start ; i < header.e_shnum ; i++)
        printf("i %d --> %s\n", i, names + section[i].sh_name);

    Elf64_Sym *syms;

    size_t sym_nb = section[29].sh_size / section[29].sh_entsize;

    syms = malloc((sym_nb) * sizeof(Elf64_Sym));

    lseek(fd, section[29].sh_offset, SEEK_SET);
    read(fd, syms, section[29].sh_size);

    char *test = malloc(section[30].sh_size * sizeof(char));
    lseek(fd, section[30].sh_offset, SEEK_SET);
    read(fd, test, section[30].sh_size);
    for (size_t i = 0 ; i < sym_nb ; i++) {
        printf("sym %s\n", test + syms[i].st_name);
    }
}

int main(int ac, char **av)
{
    int fd = open(av[1], O_RDONLY);

    if (fd != -1)
        nm(fd);
    close(fd);
}
