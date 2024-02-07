/*
** EPITECH PROJECT, 2023
** myls
** File description:
** The sort_all_files.c
*/

#include "../include/my_ls.h"

static void compare_by_name(char **files, int i, int j)
{
    char *temp_file;

    if (my_strcmp(files[j], files[i]) < 0) {
        temp_file = files[i];
        files[i] = files[j];
        files[j] = temp_file;
    }
}

static void sort_by_name(command_infos_t *command_infos)
{
    for (int i = 0; i <= command_infos->detected_file; i++) {
        for (int j = i + 1; j < command_infos->detected_file; j++) {
            compare_by_name(command_infos->files, i, j);
        }
    }
}

static void compare_by_name_reverse(char **files, int i, int j)
{
    char *temp_file;

    if (my_strcmp(files[j], files[i]) > 0) {
        temp_file = files[i];
        files[i] = files[j];
        files[j] = temp_file;
    }
}

static void sort_by_name_reverse(command_infos_t *command_infos)
{
    for (int i = 0; i <= command_infos->detected_file; i++) {
        for (int j = i + 1; j < command_infos->detected_file; j++) {
            compare_by_name_reverse(command_infos->files, i, j);
        }
    }
}

static void compare_by_time(char **files, int i, int j)
{
    char *temp_file;
    struct stat info_files1;
    struct stat info_files2;

    stat(files[j], &info_files1);
    stat(files[i], &info_files2);
    if (info_files1.st_mtim.tv_sec > info_files2.st_mtim.tv_sec) {
        temp_file = files[i];
        files[i] = files[j];
        files[j] = temp_file;
    }
}

static void sort_by_time(command_infos_t *command_infos)
{
    for (int i = 0; i <= command_infos->detected_file; i++) {
        for (int j = i + 1; j < command_infos->detected_file; j++) {
            compare_by_time(command_infos->files, i, j);
        }
    }
}

static void compare_by_time_reverse(char **files, int i, int j)
{
    char *temp_file;
    struct stat info_files1;
    struct stat info_files2;

    stat(files[j], &info_files1);
    stat(files[i], &info_files2);
    if (info_files1.st_mtim.tv_sec < info_files2.st_mtim.tv_sec) {
        temp_file = files[i];
        files[i] = files[j];
        files[j] = temp_file;
    }
}

static void sort_by_time_reverse(command_infos_t *command_infos)
{
    for (int i = 0; i <= command_infos->detected_file; i++) {
        for (int j = i + 1; j < command_infos->detected_file; j++) {
            compare_by_time_reverse(command_infos->files, i, j);
        }
    }
}

void sort_folder(command_infos_t *command_infos)
{
    if (command_infos->flag_t == 0 && command_infos->flag_r == 0) {
        sort_by_name(command_infos);
        return;
    }
    if (command_infos->flag_t == 0 && command_infos->flag_r == 1) {
        sort_by_name_reverse(command_infos);
        return;
    }
    if (command_infos->flag_t == 1 && command_infos->flag_r == 0) {
        sort_by_time(command_infos);
        return;
    }
    if (command_infos->flag_t == 1 && command_infos->flag_r == 1) {
        sort_by_time_reverse(command_infos);
        return;
    }
}
