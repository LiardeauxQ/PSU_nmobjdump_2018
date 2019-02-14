/*
** EPITECH PROJECT, 2018
** objdump.c
** File description:
** objdump
*/

#include "objdump.h"

int objdump()
{
}

void print_help(void)
{
    printf("Usage: objdump <option(s)> <file(s)>\n\
 Display information from object <file(s)>.\n\
 At least one of the following switches must be given:\n\
  -f, --file-headers       Display the contents of the overall file header\n\
  -s, --full-contents      Display the full contents of all sections requested\n\
  -H, --help               Display this information\n");
}

int main(int ac, char **av)
{
    if (ac == 1) {
        print_help();
        return (0);
    }
    return (0);
}
