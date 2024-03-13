/*
** EPITECH PROJECT, 2023
** B-MUL-100-LIL-1-1-myradar-enzo.dubeaurepaire
** File description:
** parsing.c
*/

#include "../../include/my.h"

int parse_plane(char *line, struct l_list **planes, sfTexture *texture)
{
    char **array = my_str_to_word_array(line + 1);
    int i = 0;

    for (; array[i]; i++)
        if (!my_str_isnum(array[i]))
            return 84;
    if (i != 6)
        return 84;
    add_plane(planes, array, texture);
    for (int j = 0; array[j]; j++)
        free(array[j]);
    free(array);
    return 0;
}

int parse_tower(char *line, struct l_list **towers, sfTexture *texture)
{
    char **array = my_str_to_word_array(line + 1);
    int i = 0;

    for (; array[i]; i++)
        if (!my_str_isnum(array[i]))
            return 84;
    if (i != 3)
        return 84;
    add_tower(towers, array, texture);
    for (int j = 0; array[j]; j++)
        free(array[j]);
    free(array);
    return 0;
}

int parse_line(char *line, struct l_list **planes, struct l_list **towers,
    struct textures *textures)
{
    if (line[0] == 'A')
        return parse_plane(line, planes, textures->plane);
    if (line[0] == 'T')
        return parse_tower(line, towers, textures->tower);
    return 84;
}

int parsing(const char *file_name, struct l_list **planes,
    struct l_list **towers, struct textures *textures)
{
    FILE *file = fopen(file_name, "r");
    size_t len = 0;
    ssize_t b_read;
    char *line = 0;

    if (!file) {
        write(2, "File not found\n", 15);
        return 84;
    }
    for (b_read = getline(&line, &len, file); b_read != -1;
        b_read = getline(&line, &len, file)) {
        if (b_read < 2)
            return 48;
        if (parse_line(line, planes, towers, textures))
            return 48;
    }
    free(line);
    fclose(file);
    return 0;
}
