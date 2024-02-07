/*
** EPITECH PROJECT, 2023
** myls
** File description:
** The count_files.c
*/

#include "../include/my_ls.h"

static void clear_string(char *str, int size)
{
    for (int c = 0; c < size; c++)
        str[c] = '\0';
}

char *get_file_name(char *directory_name, struct dirent *file,
    struct stat *info_file)
{
    char *file_name = malloc(sizeof(char) *
        (my_strlen(directory_name) + my_strlen(file->d_name) + 4));

    clear_string(file_name, my_strlen(directory_name)
        + my_strlen(file->d_name) + 2);
    my_strcat(file_name, directory_name);
    if (directory_name[my_strlen(directory_name) - 1] != '/')
        my_strcat(file_name, "/");
    my_strcat(file_name, file->d_name);
    file_name[my_strlen(directory_name) + my_strlen(file->d_name) + 2] = '\0';
    stat(file_name, info_file);
    return file_name;
}

int count_files_in_a_folder(char *directory_name)
{
    DIR *directory;
    struct dirent *file;
    struct stat info_file;
    int counter = 0;
    char *file_name;

    directory = opendir(directory_name);
    if (directory == NULL)
        return 0;
    file = readdir(directory);
    while (file != NULL) {
        file_name = get_file_name(directory_name, file, &info_file);
        if (is_dir(file, &info_file) == 1)
            counter = counter + count_files_in_a_folder(file_name);
        counter++;
        file = readdir(directory);
    }
    free(file_name);
    closedir(directory);
    return counter;
}

int delete_file_in_list(command_infos_t *command_infos, int file)
{
    command_infos->error_detected = 84;
    my_putstr_error("ls: cannot access '");
    my_putstr_error(command_infos->files[file]);
    my_putstr_error("': ");
    my_putstr_error(strerror(errno));
    my_putstr_error("\n");
    for (int f = file; f < command_infos->detected_file; f++) {
        command_infos->files[f] = command_infos->files[f + 1];
    }
    command_infos->files[command_infos->detected_file] = NULL;
    command_infos->detected_file = command_infos->detected_file - 1;
    return 0;
}

static int try_open(command_infos_t *command_infos, int *file)
{
    DIR *dir = opendir(command_infos->files[*file]);
    struct stat file_info;
    int file_status = stat(command_infos->files[*file], &file_info);

    if (file_status < 0 || (S_ISDIR(file_info.st_mode) == 1 && dir == NULL)) {
        command_infos->error_detected = 84;
        my_putstr_error("ls: cannot open '");
        my_putstr_error(command_infos->files[*file]);
        my_putstr_error("': ");
        my_putstr_error(strerror(errno));
        my_putstr_error("\n");
        for (int f = *file; f < command_infos->detected_file; f++)
            command_infos->files[f] = command_infos->files[f + 1];
        command_infos->files[command_infos->detected_file] = NULL;
        command_infos->detected_file = command_infos->detected_file - 1;
        *file = *file - 1;
        return 1;
    }
    closedir(dir);
    return 0;
}

int get_files_number(command_infos_t *command_infos)
{
    int total_files = 0;
    struct stat info_file;
    int file_status;

    for (int file = 0; file != command_infos->detected_file; file++) {
        if (try_open(command_infos, &file) == 1)
            continue;
        file_status = stat(command_infos->files[file], &info_file);
        if (file_status < 0) {
            delete_file_in_list(command_infos, file);
            file = file - 1;
            continue;
        }
        if (S_ISDIR(info_file.st_mode) == 1)
            total_files = total_files +
                count_files_in_a_folder(command_infos->files[file]);
        else
            total_files = total_files + 1;
    }
    return total_files;
}

int count_files_in_a_directory(char *dir)
{
    DIR *directory;
    struct dirent *file;
    int counter = 0;

    directory = opendir(dir);
    file = readdir(directory);
    while (file != NULL) {
        counter++;
        file = readdir(directory);
    }
    closedir(directory);
    return counter;
}
