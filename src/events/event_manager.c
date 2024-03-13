/*
** EPITECH PROJECT, 2023
** B_MUL_100_LIL_1_1_myradar_enzo_dubeaurepaire
** File description:
** event_manager.c
*/

#include "../../include/my.h"

void analyse_event(struct window_param *window)
{
    if (window->event->type == sfEvtKeyPressed && window->event->key.code
        == sfKeyEscape)
        sfRenderWindow_close(window->window);
    if (window->event->type == sfEvtClosed)
        sfRenderWindow_close(window->window);
    if (window->event->type == sfEvtKeyPressed && window->event->key.code
        == sfKeyL)
        window->hit_box = !(window->hit_box);
    if (window->event->type == sfEvtKeyPressed && window->event->key.code
        == sfKeyS)
        window->show_sprites = !(window->show_sprites);
    if (window->event->type == sfEvtKeyPressed && window->event->key.code
        == sfKeyT)
        window->time_min = !(window->time_min);
    if (window->event->type == sfEvtKeyPressed && window->event->key.code
        == sfKeyR)
        window->rainbow = !(window->rainbow);
}
