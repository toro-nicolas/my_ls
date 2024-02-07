/*
** EPITECH PROJECT, 2023
** myls
** File description:
** The get_all_files.c
*/

#include "../include/my_ls.h"

static void set_directory(file_t *file, char *directory_name)
{
    int char_index = 0;

    for (; directory_name[char_index] != '\0'; char_index++)
        file->directory[char_index] = directory_name[char_index];
    file->directory[char_index] = '\0';
}

static void set_filename(file_t *file, char *file_name)
{
    int char_index = 0;

    for (; file_name[char_index] != '\0'; char_index++)
        file->filename[char_index] = file_name[char_index];
    file->filename[char_index] = '\0';
}

file_t *get_file_struct(char *file_path, char *directory_name,
    char *file_name)
{
    file_t *file = malloc(sizeof(file_t));
    struct stat info_file;

    stat(file_path, &info_file);
    set_directory(file, directory_name);
    set_filename(file, file_name);
    file->permission = get_permission(info_file.st_mode, file_path);
    file->sub_dir = info_file.st_nlink;
    file->user = getpwuid(info_file.st_uid)->pw_name;
    file->group = getgrgid(info_file.st_gid)->gr_name;
    file->char_device = major(info_file.st_rdev);
    file->size = info_file.st_size;
    file->second = info_file.st_mtim.tv_sec;
    file->date = get_date(&info_file.st_mtim);
    file->file_link = get_file_link(file_path);
    return file;
}

int is_dir(struct dirent *file, struct stat *info_file)
{
    if (my_strcmp(file->d_name, ".") != 0 &&
        my_strcmp(file->d_name, "..") != 0 &&
        S_ISDIR(info_file->st_mode) == 1)
        return 1;
    return 0;
}

void fill_files_struct(all_files_t *all_files, char *directory_name,
    int *file_index)
{
    DIR *directory;
    struct dirent *file;
    struct stat info_file;
    char *file_name;

    directory = opendir(directory_name);
    if (directory == NULL)
        return;
    file = readdir(directory);
    while (file != NULL) {
        file_name = get_file_name(directory_name, file, &info_file);
        all_files->files[*file_index] = get_file_struct(file_name,
            directory_name, file->d_name);
        *file_index = *file_index + 1;
        if (is_dir(file, &info_file) == 1)
            fill_files_struct(all_files, file_name, file_index);
        file = readdir(directory);
    }
    free(file_name);
    closedir(directory);
}

all_files_t *get_all_files(command_infos_t *command_infos)
{
    int total_files = get_files_number(command_infos);
    all_files_t *all_files = malloc(sizeof(all_files_t));
    struct stat info_file;
    int file_index = 0;

    all_files->nb_files = total_files;
    all_files->files = malloc(sizeof(file_t *) * total_files);
    for (int file = 0; file != command_infos->detected_file; file++) {
        stat(command_infos->files[file], &info_file);
        if (S_ISDIR(info_file.st_mode) == 1) {
            fill_files_struct(all_files,
                command_infos->files[file], &file_index);
        } else {
            all_files->files[file_index] = get_file_struct
                (command_infos->files[file], "", command_infos->files[file]);
            file_index = file_index + 1;
        }
    }
    return all_files;
}
