/*
** EPITECH PROJECT, 2023
** B_MUL_100_LIL_1_1_myradar_enzo_dubeaurepaire
** File description:
** init_sprites.c
*/

#include "../../include/my.h"

sfRectangleShape *init_plane_hit_box(sfVector2f init, double angle)
{
    sfRectangleShape *hit_box = sfRectangleShape_create();

    sfRectangleShape_setSize(hit_box, (sfVector2f){P_LENGTH, P_WIDTH});
    sfRectangleShape_setOrigin(hit_box,
        (sfVector2f){P_LENGTH / 2.0f, P_WIDTH / 2.0f});
    sfRectangleShape_setRotation(hit_box, angle);
    sfRectangleShape_setPosition(hit_box, init);
    sfRectangleShape_setFillColor(hit_box, (sfColor){0, 0, 0, 0});
    sfRectangleShape_setOutlineColor(hit_box, sfWhite);
    sfRectangleShape_setOutlineThickness(hit_box, 1);
    return hit_box;
}

sfCircleShape *init_tower_hit_box(sfVector2f pos, int radius)
{
    sfCircleShape *hit_box = sfCircleShape_create();

    pos.x -= radius;
    pos.y -= radius;
    sfCircleShape_setPosition(hit_box, pos);
    sfCircleShape_setRadius(hit_box, radius);
    sfCircleShape_setFillColor(hit_box, (sfColor){0, 0, 0, 0});
    sfCircleShape_setOutlineColor(hit_box, sfWhite);
    sfCircleShape_setOutlineThickness(hit_box, 1);
    return hit_box;
}

sfSprite *get_tower_sprite(sfTexture *texture)
{
    sfSprite *tower_sprite = sfSprite_create();
    sfVector2u size = sfTexture_getSize(texture);

    sfSprite_setTexture(tower_sprite, texture, 0);
    sfSprite_setScale(tower_sprite, (sfVector2f){(float)T_LENGTH
        / (float)size.x, (float)T_WIDTH / (float)size.y});
    return tower_sprite;
}

sfSprite *get_plane_sprite(sfTexture *texture)
{
    sfSprite *plane_sprite = sfSprite_create();

    sfSprite_setTexture(plane_sprite, texture, 0);
    sfSprite_setTextureRect(plane_sprite, (sfIntRect){0, 0, 480, 480});
    sfSprite_setOrigin(plane_sprite,
        (sfVector2f){480.0f / 2.0f, 480.0f / 2.0f});
    sfSprite_setScale(plane_sprite, (sfVector2f){(float)P_LENGTH
        / 480.0f, (float)P_WIDTH / 480.0f});
    return plane_sprite;
}
