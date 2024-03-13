/*
** EPITECH PROJECT, 2023
** B_MUL_100_LIL_1_1_myradar_enzo_dubeaurepaire
** File description:
** add_in_list.c
*/

#include "../../include/my.h"

void get_tower_subtree(struct tower_data *tower, sfVector2f center,
    double radius)
{
    double x = center.x - radius;
    double y = center.y - radius;
    double x_max = center.x + radius;
    double y_max = center.y + radius;

    tower->subtree = 0;
    if (x < WIN_WIDTH / 2.0 && y < WIN_LENGTH / 2.0)
        tower->subtree += 1;
    if (x < WIN_WIDTH / 2.0 && y_max > WIN_LENGTH / 2.0)
        tower->subtree += 2;
    if (x_max > WIN_WIDTH / 2.0 && y < WIN_LENGTH / 2.0)
        tower->subtree += 4;
    if (x_max > WIN_WIDTH / 2.0 && y_max > WIN_LENGTH / 2.0)
        tower->subtree += 8;
}

void add_node(struct l_list **list, void *data)
{
    struct l_list *new = malloc(sizeof(struct l_list));

    new->data = data;
    new->next = *list;
    *list = new;
}

void add_tower(struct l_list **towers, char **array, sfTexture *texture)
{
    struct tower_data *new = malloc(sizeof(struct tower_data));

    new->position.x = my_getnbr(array[0]);
    new->position.y = my_getnbr(array[1]);
    new->radius = (my_getnbr(array[2]) / 100.0) * WIN_LENGTH;
    new->sprite = get_tower_sprite(texture);
    get_tower_subtree(new, new->position, new->radius);
    new->hit_box = init_tower_hit_box(new->position, (int)(new->radius));
    sfSprite_setPosition(new->sprite, (sfVector2f){new->position.x -
        T_LENGTH / 2, new->position.y - T_WIDTH / 2});
    add_node(towers, new);
}

void add_plane(struct l_list **planes, char **array, sfTexture *texture)
{
    struct plane_data *new = malloc(sizeof(struct plane_data));

    new->launched = 0;
    new->init.x = my_getnbr(array[0]);
    new->init.y = my_getnbr(array[1]);
    new->arrival.x = my_getnbr(array[2]);
    new->arrival.y = my_getnbr(array[3]);
    new->speed = my_getnbr(array[4]);
    new->delay = my_getnbr(array[5]);
    new->sprite = get_plane_sprite(texture);
    new->subtree = 0;
    sfSprite_setPosition(new->sprite, (sfVector2f){new->init.x, new->init.y});
    new->travel_time = sqrt(pow(new->init.x - new->arrival.x, 2) +
        pow(new->init.y - new->arrival.y, 2)) / (double)new->speed;
    new->angle = atan2(new->arrival.y - new->init.y, new->arrival.x -
        new->init.x);
    sfSprite_setRotation(new->sprite, 180 + new->angle * 180 / M_PI);
    new->hit_box = init_plane_hit_box(new->init, 180 + new->angle *
        180 / M_PI);
    add_node(planes, new);
}
