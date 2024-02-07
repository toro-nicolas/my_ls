/*
** EPITECH PROJECT, 2023
** myls
** File description:
** The my_ls.h
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/sysmacros.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include "my.h"

#ifndef MY_LS_H
    #define MY_LS_H

    #define FLAGS "alRdrt"

typedef struct command_info_s {
    int detected_file;
    char **files;
    int flag_a;
    int flag_l;
    int flag_big_r;
    int flag_d;
    int flag_r;
    int flag_t;
    int error_detected;
} command_infos_t;

typedef struct file_s {
    char directory[1024];
    char filename[256];
    char *permission;
    int sub_dir;
    char *user;
    char *group;
    size_t char_device;
    size_t size;
    time_t second;
    char *date;
    char *file_link;
} file_t;

typedef struct all_files_s {
    int nb_files;
    file_t **files;
} all_files_t;

void display_command_info(command_infos_t *command_infos);
void display_all_files(all_files_t *all_files);
int search_flag(command_infos_t *command_info, char *flag_string);
command_infos_t analyse_command(int argc, char **argv);

int contain_space(char *str);

char get_file_type(mode_t mode, char *file_path);
char *get_permission(mode_t mode, char *file_path);
char *get_date(struct timespec *time);
char *get_file_link(char *file_path);
int get_total(char *dir);

char *get_file_name(char *directory_name, struct dirent *file,
    struct stat *info_file);
int count_files_in_a_folder(char *directory_name);
int get_files_number(command_infos_t *command_infos);
int count_files_in_a_directory(char *dir);

file_t *get_file_struct(char *file_path, char *directory_name,
    char *file_name);
int is_dir(struct dirent *file, struct stat *info_file);
void fill_files_struct(all_files_t *all_files, char *directory_name,
    int *file_index);
all_files_t *get_all_files(command_infos_t *command_infos);

void sort_all_files(command_infos_t *command_infos, all_files_t *all_files);
void sort_folder(command_infos_t *command_infos);

int is_hidden(char *file_path);
void print_all_infos(file_t *file);
void print_file_name(file_t *file, int last);
void print_file(command_infos_t *command_infos, file_t *file, int last);

void print_flag_d(command_infos_t *command_infos);
static void print_file_in_dir(command_infos_t *command_infos,
    char *folder, file_t *file, int *counter);
static void print_folder(command_infos_t *command_infos,
    all_files_t *all_files, int *first);
void print_basic(command_infos_t *command_infos, all_files_t *all_files);
void print_recursive(command_infos_t *command_infos, all_files_t *all_files);

void print_all_files(command_infos_t *command_infos);

#endif /* MY_LS_H */
