/*
** EPITECH PROJECT, 2023
** myls
** File description:
** The detect_flag.c
*/

#include "../include/my_ls.h"

static void flag_a_detected(command_infos_t *command_info)
{
    command_info->flag_a = 1;
}

static void flag_l_detected(command_infos_t *command_info)
{
    command_info->flag_l = 1;
}

static void flag_big_r_detected(command_infos_t *command_info)
{
    command_info->flag_big_r = 1;
}

static void flag_d_detected(command_infos_t *command_info)
{
    command_info->flag_d = 1;
}

static void flag_r_detected(command_infos_t *command_info)
{
    command_info->flag_r = 1;
}

static void flag_t_detected(command_infos_t *command_info)
{
    command_info->flag_t = 1;
}

int detect_flag(command_infos_t *command_info, char str_char, char flag_char,
    int *flag_index)
{
    void(*DETECT_FLAG_FUNCTIONS[])(command_infos_t *) = {
        &flag_a_detected, &flag_l_detected, &flag_big_r_detected,
        &flag_d_detected, &flag_r_detected, &flag_t_detected};

    if (str_char == flag_char) {
        DETECT_FLAG_FUNCTIONS[*flag_index](command_info);
        *flag_index = my_strlen(FLAGS) - 1;
        return 0;
    } else {
        return -1;
    }
}

int search_flag(command_infos_t *command_info, char *flag_string)
{
    int found = 0;

    for (int c = 1; flag_string[c] != '\0'; c++) {
        for (int flag_index = 0; FLAGS[flag_index] != '\0'; flag_index++) {
            found = detect_flag(command_info, flag_string[c],
                                FLAGS[flag_index], &flag_index);
        }
        if (found == -1) {
            my_putstr_error("ls: invalid option -- '");
            my_putchar(flag_string[c]);
            my_putstr_error("'\nTry 'ls --help' for more information.\n");
            exit(84);
        }
        found = 0;
    }
    return 0;
}
