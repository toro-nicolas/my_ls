/*
** EPITECH PROJECT, 2023
** myls
** File description:
** The print_file.c
*/

#include "../include/my_ls.h"

int is_hidden(char *file_path)
{
    int point_detected = 0;

    for (int c = my_strlen(file_path) - 1; c > -1; c--) {
        if (file_path[c] == '.') {
            point_detected = 1;
            continue;
        }
        if (c != my_strlen(file_path) - 1 && file_path[c] == '/' &&
            point_detected == 1) {
            return point_detected;
        }
        point_detected = 0;
    }
    return 0;
}

void print_all_infos(file_t *file)
{
    my_printf("%s %d %s %s ",
        file->permission, file->sub_dir, file->user, file->group);
    if (file->permission[0] == 'c' || file->permission[0] == 'b')
        my_printf("%zu, ", file->char_device);
    my_printf("%zu %s %s%s\n",
        file->size, file->date, file->filename, file->file_link);
}

void print_file_name(file_t *file, int last)
{
    my_printf(file->filename);
    if (last == 1)
        my_putchar('\n');
    else
        my_putstr("  ");
}

void print_file(command_infos_t *command_infos, file_t *file, int last)
{
    if (command_infos->flag_a == 0 &&
        (is_hidden(file->directory) == 1 || file->filename[0] == '.')) {
        if (last == 1)
            my_putchar('\n');
    } else {
        if (command_infos->flag_l == 1)
            print_all_infos(file);
        else
            print_file_name(file, last);
    }
}
