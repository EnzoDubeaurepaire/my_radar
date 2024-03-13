/*
** EPITECH PROJECT, 2023
** B_MUL_100_LIL_1_1_myradar_enzo_dubeaurepaire
** File description:
** del_in_list.c
*/

#include "../../include/my.h"

void free_node(void *plane)
{
    struct plane_data *plane_data = plane;

    sfRectangleShape_destroy(plane_data->hit_box);
    sfSprite_destroy(plane_data->sprite);
    free(plane_data);
}

void del_in_list(struct l_list **planes, struct l_list *node)
{
    struct l_list *head = *planes;

    if (*planes == node) {
        *planes = node->next;
        free_node(node->data);
        free(node);
        return;
    }
    for (; head && head->next != node; head = head->next);
    if (head->next)
        head->next = node->next;
    free_node(node->data);
    free(node);
}
