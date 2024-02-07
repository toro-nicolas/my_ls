/*
** EPITECH PROJECT, 2023
** myls
** File description:
** The main.c
*/

#include "../include/my_ls.h"

void display_command_info(command_infos_t *command_infos)
{
    my_printf("File detected: %d\n", command_infos->detected_file);
    for (int file = 0; file < command_infos->detected_file; file++) {
        my_printf("%s\n", command_infos->files[file]);
    }
    my_printf("Flag a: %d\n", command_infos->flag_a);
    my_printf("Flag l: %d\n", command_infos->flag_l);
    my_printf("Flag R: %d\n", command_infos->flag_big_r);
    my_printf("Flag d: %d\n", command_infos->flag_d);
    my_printf("Flag r: %d\n", command_infos->flag_r);
    my_printf("Flag t: %d\n", command_infos->flag_t);
    my_printf("Error detected: %d\n", command_infos->error_detected);
}

void display_all_files(all_files_t *all_files)
{
    for (int file = 0; file < all_files->nb_files; file++) {
        my_printf("\nDirectory: %s\n", all_files->files[file]->directory);
        print_all_infos(all_files->files[file]);
    }
}

int main(int argc, char **argv)
{
    command_infos_t command_infos = analyse_command(argc, argv);

    if (command_infos.detected_file == 0) {
        command_infos.detected_file = 1;
        command_infos.files[0] = ".";
    }
    print_all_files(&command_infos);
    return command_infos.error_detected;
}
