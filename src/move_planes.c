/*
** EPITECH PROJECT, 2023
** B_MUL_100_LIL_1_1_myradar_enzo_dubeaurepaire
** File description:
** move_planes.c
*/

#include "../include/my.h"

void are_landed(struct l_list **planes, struct window_param *window,
    sfTime time)
{
    struct l_list *head = *planes;
    struct plane_data *plane;
    double seconds;
    struct l_list *tmp;

    while (head) {
        plane = head->data;
        if (plane->launched)
            seconds = (double)time.microseconds / 1000000.0 - plane->delay;
        if (!plane->launched)
            seconds = -1;
        tmp = head;
        head = head->next;
        if (plane->travel_time <= seconds)
            del_in_list(planes, tmp);
    }
}

void move_planes(struct l_list **planes, struct window_param *window,
    sfTime time)
{
    struct l_list *head = *planes;
    double seconds;
    struct plane_data *plane;
    sfVector2f new_pos;

    for (; head; head = head->next) {
        plane = head->data;
        seconds = (double)time.microseconds / 1000000.0 - plane->delay;
        if (plane->launched) {
            new_pos.x = (float)((double)plane->speed * seconds *
                cos(plane->angle) + plane->init.x);
            new_pos.y = (float)((double)plane->speed * seconds *
                sin(plane->angle) + plane->init.y);
            sfSprite_setPosition(plane->sprite, new_pos);
            sfRectangleShape_setPosition(plane->hit_box, new_pos);
        }
        if (window->rainbow)
            sfSprite_setTextureRect(plane->sprite,
                (sfIntRect){((int) (seconds * 6.0) % 6) * 480, 0, 480, 480});
    }
}

void launch_planes(struct l_list **planes, sfClock *main_clock)
{
    struct l_list *head = *planes;
    sfTime time = sfClock_getElapsedTime(main_clock);
    long seconds = time.microseconds / 1000000;
    struct plane_data *plane;

    for (; head; head = head->next) {
        plane = head->data;
        if (plane->delay <= seconds && !plane->launched)
            plane->launched = 1;
    }
}
