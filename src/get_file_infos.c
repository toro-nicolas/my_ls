/*
** EPITECH PROJECT, 2023
** myls
** File description:
** The get_file_infos.c
*/

#include "../include/my_ls.h"

char get_file_type(mode_t mode, char *file_path)
{
    char *link_name = malloc(sizeof(char) * 256);
    int link_status = readlink(file_path, link_name, 256);

    free(link_name);
    if (S_ISDIR(mode) == 1)
        return 'd';
    if (S_ISCHR(mode) == 1)
        return 'c';
    if (S_ISBLK(mode) == 1)
        return 'b';
    if (S_ISFIFO(mode) == 1)
        return 'p';
    if (link_status > -1)
        return 'l';
    if (S_ISSOCK(mode) == 1)
        return 's';
    return '-';
}

char *get_permission(mode_t mode, char *file_path)
{
    char *permission = malloc(sizeof(char) * 11);

    permission[0] = get_file_type(mode, file_path);
    permission[1] = ((mode & S_IRUSR) ? 'r' : '-');
    permission[2] = ((mode & S_IWUSR) ? 'w' : '-');
    permission[3] = ((mode & S_IXUSR) ? 'x' : '-');
    permission[4] = ((mode & S_IRGRP) ? 'r' : '-');
    permission[5] = ((mode & S_IWGRP) ? 'w' : '-');
    permission[6] = ((mode & S_IXGRP) ? 'x' : '-');
    permission[7] = ((mode & S_IROTH) ? 'r' : '-');
    permission[8] = ((mode & S_IWOTH) ? 'w' : '-');
    permission[9] = ((mode & S_IXOTH) ? 'x' : '-');
    if ((mode & S_ISVTX) == 512 && permission[9] == 'x')
        permission[9] = 't';
    if ((mode & S_ISVTX) == 512 && permission[9] == '-')
        permission[9] = 'T';
    permission[10] = '.';
    permission[11] = '\0';
    return permission;
}

char *get_date(struct timespec *time)
{
    char *date = malloc(sizeof(char) * 12);
    char *temp_date = ctime(&time->tv_sec);

    for (int c = 4; c < 16; c++) {
        date[c - 4] = temp_date[c];
    }
    date[12] = '\0';
    return date;
}

char *get_file_link(char *file_path)
{
    char *link_name = malloc(sizeof(char) * 256);
    int link_status = readlink(file_path, link_name, 256);
    char *file_link;

    if (link_status > -1) {
        link_name[link_status] = '\0';
        file_link = malloc(sizeof(char) * (link_status + 9));
        file_link[0] = '\0';
        my_strcat(file_link, " -> ");
        if (contain_space(link_name) == 1)
            my_strcat(file_link, "'");
        my_strcat(file_link, link_name);
        if (contain_space(link_name) == 1)
            my_strcat(file_link, "'");
    } else {
        file_link = "\0";
    }
    free(link_name);
    return file_link;
}

int get_total(char *dir)
{
    DIR *directory;
    struct dirent *file;
    int total = 0;
    struct stat file_infos;
    char *file_name;

    directory = opendir(dir);
    file = readdir(directory);
    while (file != NULL) {
        file_name = get_file_name(dir, file, &file_infos);
        total = total + file_infos.st_blocks;
        file = readdir(directory);
    }
    closedir(directory);
    return total / 2;
}
