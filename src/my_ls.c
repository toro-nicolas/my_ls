/*
** EPITECH PROJECT, 2023
** myls
** File description:
** The my_ls.c
*/

#include "../include/my_ls.h"

int contain_space(char *str)
{
    for (int c = 0; str[c] != '\0'; c++) {
        if (str[c] == ' ')
            return 1;
    }
    return 0;
}

command_infos_t analyse_command(int argc, char **argv)
{
    command_infos_t command_info = {0};

    command_info.files = malloc(sizeof(char *) * argc);
    for (int index = 1; index < argc; index++) {
        if (argv[index][0] == '-') {
            search_flag(&command_info, argv[index]);
        } else {
            command_info.files[command_info.detected_file] = argv[index];
            command_info.detected_file += 1;
        }
    }
    return command_info;
}

void print_all_files(command_infos_t *command_infos)
{
    all_files_t *all_files;

    if (command_infos->flag_d) {
        print_flag_d(command_infos);
    } else {
        all_files = get_all_files(command_infos);
        sort_all_files(command_infos, all_files);
        if (command_infos->flag_big_r == 0)
            print_basic(command_infos, all_files);
        else
            print_recursive(command_infos, all_files);
        free(all_files->files);
    }
}
