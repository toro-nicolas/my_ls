/*
** EPITECH PROJECT, 2023
** myls
** File description:
** The sort_all_files.c
*/

#include "../include/my_ls.h"

static void compare_by_name(file_t **files, int i, int j)
{
    file_t *temp_file;

    if (my_strcmp(files[j]->filename, files[i]->filename) < 0) {
        temp_file = files[i];
        files[i] = files[j];
        files[j] = temp_file;
    }
}

static void sort_by_name(all_files_t *all_files)
{
    for (int i = 0; i <= all_files->nb_files; i++) {
        for (int j = i + 1; j < all_files->nb_files; j++) {
            compare_by_name(all_files->files, i, j);
        }
    }
}

static void compare_by_name_reverse(file_t **files, int i, int j)
{
    file_t *temp_file;

    if (my_strcmp(files[j]->filename, files[i]->filename) > 0) {
        temp_file = files[i];
        files[i] = files[j];
        files[j] = temp_file;
    }
}

static void sort_by_name_reverse(all_files_t *all_files)
{
    for (int i = 0; i <= all_files->nb_files; i++) {
        for (int j = i + 1; j < all_files->nb_files; j++) {
            compare_by_name_reverse(all_files->files, i, j);
        }
    }
}

static void compare_by_time(file_t **files, int i, int j)
{
    file_t *temp_file;

    if (files[j]->second > files[i]->second) {
        temp_file = files[i];
        files[i] = files[j];
        files[j] = temp_file;
    }
}

static void sort_by_time(all_files_t *all_files)
{
    for (int i = 0; i <= all_files->nb_files; i++) {
        for (int j = i + 1; j < all_files->nb_files; j++) {
            compare_by_time(all_files->files, i, j);
        }
    }
}

static void compare_by_time_reverse(file_t **files, int i, int j)
{
    file_t *temp_file;

    if (files[j]->second < files[i]->second) {
        temp_file = files[i];
        files[i] = files[j];
        files[j] = temp_file;
    }
}

static void sort_by_time_reverse(all_files_t *all_files)
{
    for (int i = 0; i <= all_files->nb_files; i++) {
        for (int j = i + 1; j < all_files->nb_files; j++) {
            compare_by_time_reverse(all_files->files, i, j);
        }
    }
}

void sort_all_files(command_infos_t *command_infos, all_files_t *all_files)
{
    if (command_infos->flag_t == 0 && command_infos->flag_r == 0) {
        sort_by_name(all_files);
        return;
    }
    if (command_infos->flag_t == 0 && command_infos->flag_r == 1) {
        sort_by_name_reverse(all_files);
        return;
    }
    if (command_infos->flag_t == 1 && command_infos->flag_r == 0) {
        sort_by_time(all_files);
        return;
    }
    if (command_infos->flag_t == 1 && command_infos->flag_r == 1) {
        sort_by_time_reverse(all_files);
        return;
    }
}
