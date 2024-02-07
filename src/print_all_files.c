/*
** EPITECH PROJECT, 2023
** myls
** File description:
** The print_all_files.c
*/

#include "../include/my_ls.h"

void print_flag_d(command_infos_t *command_infos)
{
    all_files_t *all_files = malloc(sizeof(all_files_t));
    int last = 0;

    command_infos->flag_a = 1;
    all_files->nb_files = command_infos->detected_file;
    all_files->files = malloc(sizeof(file_t *) * all_files->nb_files);
    for (int file = 0; file < all_files->nb_files; file++)
        all_files->files[file] = get_file_struct
            (command_infos->files[file], "", command_infos->files[file]);
    sort_all_files(command_infos, all_files);
    for (int file = 0; file < all_files->nb_files; file++) {
        if (file == all_files->nb_files - 1)
            last = 1;
        print_file(command_infos, all_files->files[file], last);
    }
}

static void print_file_in_dir(command_infos_t *command_infos,
    char *folder, file_t *file, int *counter)
{
    int last = 0;

    if (my_strcmp(folder, file->directory) == 0) {
        counter[0] = counter[0] + 1;
        if (counter[0] == counter[1])
            last = 1;
        print_file(command_infos, file, last);
    }
}

static void print_directory_name(command_infos_t *command_infos, int *first,
    int folder)
{
    if (command_infos->detected_file > 1 && *first == 1)
        my_putchar('\n');
    if (command_infos->detected_file > 1)
        my_printf("%s:\n", command_infos->files[folder]);
    if (command_infos->flag_l == 1)
        my_printf("total %zu\n", get_total(command_infos->files[folder]));
}

static void print_folder(command_infos_t *command_infos,
    all_files_t *all_files, int *first)
{
    struct stat file_infos;
    int counter[2];

    sort_folder(command_infos);
    for (int folder = 0; folder < command_infos->detected_file; folder++) {
        stat(command_infos->files[folder], &file_infos);
        if (S_ISDIR(file_infos.st_mode) == 0)
            continue;
        print_directory_name(command_infos, first, folder);
        *first = 1;
        counter[0] = 0;
        counter[1] = count_files_in_a_directory(command_infos->files[folder]);
        for (int file = 0; file < all_files->nb_files; file++)
            print_file_in_dir(command_infos, command_infos->files[folder],
                all_files->files[file], counter);
    }
}

void print_basic(command_infos_t *command_infos, all_files_t *all_files)
{
    struct stat file_infos;
    int last = 0;
    int file_counter = 0;
    int file_counter_temp = 0;

    for (int file = 0; file < command_infos->detected_file; file++) {
        stat(command_infos->files[file], &file_infos);
        if (S_ISDIR(file_infos.st_mode) == 0)
            file_counter++;
    }
    for (int file = 0; file < all_files->nb_files && last != 1; file++) {
        if (my_strcmp(all_files->files[file]->directory, "") == 0 &&
        my_strcmp(all_files->files[file]->filename, "") != 0) {
            file_counter_temp++;
            last = (file_counter_temp == file_counter) ? 1 : 0;
            print_file(command_infos, all_files->files[file], last);
            all_files->files[file]->filename[0] = '\0';
        }
    }
    print_folder(command_infos, all_files, &last);
}

static int is_in_list(char **list, char *str, int list_size)
{
    for (int string = 0; string < list_size; string++) {
        if (my_strcmp(list[string], str) == 0) {
            return 1;
        }
    }
    return 0;
}

void print_recursive(command_infos_t *command_infos, all_files_t *all_files)
{
    char **new_files = malloc(sizeof(char *) * (command_infos->detected_file
        + all_files->nb_files));
    int folder = 0;

    for (int file = 0; file < command_infos->detected_file; file++)
        new_files[file] = command_infos->files[file];
    for (int file = 0; file < all_files->nb_files; file++) {
        if (command_infos->flag_a == 0 &&
        is_hidden(all_files->files[file]->directory) == 1)
            continue;
        if (is_in_list(new_files, all_files->files[file]->directory,
            command_infos->detected_file + folder) == 0) {
            new_files[command_infos->detected_file + folder] =
                all_files->files[file]->directory;
            folder = folder + 1;
        }
    }
    command_infos->detected_file = command_infos->detected_file + folder;
    command_infos->files = new_files;
    print_basic(command_infos, all_files);
}
