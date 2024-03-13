/*
** EPITECH PROJECT, 2023
** B_MUL_100_LIL_1_1_myradar_enzo_dubeaurepaire
** File description:
** main.c
*/

#include "../include/my.h"

void free_tower(void *tower)
{
    struct tower_data *tower_data = tower;

    sfCircleShape_destroy(tower_data->hit_box);
    sfSprite_destroy(tower_data->sprite);
    free(tower_data);
}

void del_tower(struct l_list **towers, struct l_list *node)
{
    struct l_list *head = *towers;

    if (*towers == node) {
        *towers = node->next;
        free_tower(node->data);
        free(node);
        return;
    }
    for (; head && head->next != node; head = head->next);
    if (head->next)
        head->next = node->next;
    free_tower(node->data);
    free(node);
}

void free_list(struct l_list **planes, struct l_list **towers)
{
    struct l_list *head = *planes;
    struct l_list *tmp;

    for (; head; head = tmp) {
        tmp = head->next;
        del_in_list(planes, head);
    }
    head = *towers;
    for (; head; head = tmp) {
        tmp = head->next;
        del_tower(towers, head);
    }
}

int header(void)
{
    write(1, "Air traffic simulation panel\n\n", 30);
    write(1, "USAGE\n", 6);
    write(1, "   ./my_radar [OPTIONS] path_to_script\n", 39);
    write(1, "    path_to_script    The path to the script file.\n", 51);
    write(1, "\nOPTIONS\n  -h         print the usage and quit.\n\n", 49);
    write(1, "USER INTERACTIONS\n  ", 20);
    write(1, "'L' key    enable/disable hitboxes and areas.\n", 46);
    write(1, "  'S' key    enable/disable sprites.\n", 37);
    write(1, "  'R' key    enable/disable rainbow mode (EPILEPSY", 50);
    write(1, " WARNING).\n", 11);
    write(1, "  'T' key    switch time display from seconds", 45);
    write(1, " to minutes:seconds.\n", 21);
    write(1, "  'ESCAPE' key    close the game.\n", 34);
    return 0;
}

static int assets_error(void)
{
    sfTexture *plane = sfTexture_createFromFile("assets/plane.png", NULL);
    sfTexture *tower = sfTexture_createFromFile("assets/tower.png", NULL);
    sfTexture *back = sfTexture_createFromFile("assets/map.png", NULL);
    sfFont *font = sfFont_createFromFile("assets/digital-7.ttf");

    if (!plane)
        write(2, "Asset plane.png is missing\n", 27);
    if (!tower)
        write(2, "Asset tower.png is missing\n", 27);
    if (!back)
        write(2, "Asset map.png is missing\n", 25);
    if (!font)
        write(2, "Asset digital-7.ttf is missing\n", 31);
    if (!font || !plane || !tower || !back)
        return 84;
    sfTexture_destroy(plane);
    sfTexture_destroy(tower);
    sfTexture_destroy(back);
    sfFont_destroy(font);
    return 0;
}

static void launch_game(struct l_list **planes, struct l_list **towers,
    struct textures *textures)
{
    create_window(planes, towers);
    sfTexture_destroy(textures->tower);
    sfTexture_destroy(textures->plane);
    free(textures);
    free_list(planes, towers);
    free(*planes);
    free(*towers);
}

static void get_textures(struct textures *textures)
{
    textures->tower = sfTexture_createFromFile("assets/tower.png", NULL);
    textures->plane = sfTexture_createFromFile("assets/plane.png", NULL);
}

int main(int ac, char **av, char **env)
{
    struct l_list *planes = NULL;
    struct l_list *towers = NULL;
    struct textures *textures = malloc(sizeof(struct textures));
    int err;

    if (!env || assets_error())
        return 84;
    if (ac != 2) {
        write(2, "Incorrect number of arguments\n", 30);
        return 84;
    }
    get_textures(textures);
    if (my_strlen(av[1]) == 2 && av[1][0] == '-' && av[1][1] == 'h')
        return header();
    err = parsing(av[1], &planes, &towers, textures);
    if (err == 48)
        write(2, "Incorrect arguments, try using -h for help\n", 43);
    if (err == 48 || err == 84)
        return 84;
    launch_game(&planes, &towers, textures);
}
