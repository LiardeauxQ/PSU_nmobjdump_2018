/*
** EPITECH PROJECT, 2018
** objdump.c
** File description:
** objdump
*/

#include "objdump.h"

void print_help(void)
{
    printf("Usage: objdump <option(s)> <file(s)>\n\
 Display information from object <file(s)>.\n\
 At least one of the following switches must be given:\n\
  -f, --file-headers       Display the contents of the overall file header\n\
  -s, --full-contents      Display the full contents of all sections\
requested\n\
  -H, --help               Display this information\n");
}

char **find_filenames(char **av, char *options[])
{
    char **filenames = NULL;
    size_t size = 1;
    char is_option = 0;

    for (size_t i = 1 ; av[i] != NULL ; i++) {
        for (size_t j = 0 ; options[j] != NULL ; j++) {
            if (!strcmp(av[i], options[j]))
                is_option = 1;
        }
        if (is_option == 0) {
            filenames = realloc(filenames, (size + 1) * sizeof(char*));
            filenames[size - 1] = av[i];
            filenames[size] = NULL;
            size = size + 1;
        }
        is_option = 0;
    }
    return (filenames);
}

int call_options(char **filenames, int index)
{
    int (*func[4])(void *, char *) = {&display_sections_content,
        &display_sections_content, &display_fill_header, &display_fill_header};
    void *data = NULL;

    if (index >= 4)
        return (-1);
    for (size_t i = 0 ; filenames[i] != NULL ; i++) {
        data = stock_file(filenames[i]);
        if (data == NULL)
            continue;
        func[index](data, filenames[i]);
    }
    return (0);
}

int main(int ac, char **av)
{
    char *options[] = {"-s", "--full-contents", "-f", "--file-headers", NULL};
    char **filenames = NULL;

    if (ac < 3) {
        print_help();
        return (-1);
    }
    filenames = find_filenames(av, options);
    for (size_t i = 1 ; av[i] != NULL ; i++) {
        for (size_t j = 0 ; options[j] != NULL ; j++) {
            if (!strcmp(av[i], options[j])) {
                call_options(filenames, j);
            }
        }
    }
    free(filenames);
    return (0);
}
