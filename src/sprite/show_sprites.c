/*
** EPITECH PROJECT, 2023
** B_MUL_100_LIL_1_1_myradar_enzo_dubeaurepaire
** File description:
** show_sprites.c
*/

#include "../../include/my.h"

void show_planes(struct window_param *window, struct l_list **planes)
{
    struct l_list *head = *planes;
    struct plane_data *plane;

    for (; head; head = head->next) {
        plane = (struct plane_data *)(head->data);
        if (plane->launched && window->show_sprites)
            sfRenderWindow_drawSprite(window->window, plane->sprite, NULL);
        if (plane->launched && window->hit_box)
            sfRenderWindow_drawRectangleShape(window->window,
                plane->hit_box, NULL);
    }
}

void show_towers(struct window_param *window, struct l_list **towers)
{
    struct l_list *head = *towers;
    struct tower_data *tower;

    for (; head; head = head->next) {
        tower = head->data;
        if (window->show_sprites)
            sfRenderWindow_drawSprite(window->window, tower->sprite, NULL);
        if (window->hit_box)
            sfRenderWindow_drawCircleShape(window->window, tower->hit_box,
                NULL);
    }
}
