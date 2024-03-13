/*
** EPITECH PROJECT, 2023
** B_MUL_100_LIL_1_1_myradar_enzo_dubeaurepaire
** File description:
** collisions.c
*/

#include "../../include/my.h"

int do_collide(struct plane_data *p1, struct plane_data *p2, double time)
{
    double x1 = get_x_min(p1, time);
    double y1 = get_y_min(p1, time);
    double x2 = get_x_min(p2, time);
    double y2 = get_y_min(p2, time);
    double x1_max = get_x_max(p1, time);
    double y1_max = get_y_max(p1, time);
    double x2_max = get_x_max(p2, time);
    double y2_max = get_y_max(p2, time);

    if (x1 > x2_max || x1_max < x2 || y1 > y2_max || y1_max < y2)
        return 0;
    p1->travel_time = time - p1->delay;
    p2->travel_time = time - p2->delay;
    return 1;
}

static void get_subtree(struct plane_data *p, double time)
{
    double x = get_x_min(p, time);
    double y = get_y_min(p, time);
    double x_max = get_x_max(p, time);
    double y_max = get_y_max(p, time);

    p->subtree = 0;
    if (x < WIN_WIDTH / 2.0 && y < WIN_LENGTH / 2.0)
        p->subtree += 1;
    if (x < WIN_WIDTH / 2.0 && y_max > WIN_LENGTH / 2.0)
        p->subtree += 2;
    if (x_max > WIN_WIDTH / 2.0 && y < WIN_LENGTH / 2.0)
        p->subtree += 4;
    if (x_max > WIN_WIDTH / 2.0 && y_max > WIN_LENGTH / 2.0)
        p->subtree += 8;
}

void check_plane_collision(struct plane_data *actual,
    struct l_list **planes, double time)
{
    struct l_list *head = *planes;
    struct plane_data *plane;

    if (time < actual->delay || time > actual->travel_time + actual->delay ||
        actual->is_in_tower)
        return;
    for (; head; head = head->next) {
        plane = head->data;
        if (actual != plane && ((actual->subtree & plane->subtree) != 0) &&
            time >= plane->delay && !plane->is_in_tower &&
            time <= plane->travel_time + plane->delay)
            do_collide(actual, plane, time);
    }
}

static sfVector2f get_rectangle_center(struct plane_data *p, double time)
{
    sfVector2f rc = {p->init.x + (time - (double)p->delay) * p->speed *
        cos(p->angle), p->init.y + (time - (double)p->delay) * p->speed *
        sin(p->angle)};

    return rc;
}

static sfVector2f get_rotated_circle(struct tower_data *t, sfVector2f rc,
    struct plane_data *p)
{
    sfVector2f cc = {cos(p->angle) * (t->position.x - rc.x) - sin(p->angle) *
        (t->position.y - rc.y) + rc.x, sin(p->angle) * (t->position.x - rc.x) +
        cos(p->angle) * (t->position.y - rc.y) + rc.y};

    return cc;
}

static int tower_plane_collide(struct plane_data *p, double time,
    struct tower_data *t)
{
    sfVector2f rc = get_rectangle_center(p, time);
    sfVector2f cc = get_rotated_circle(t, rc, p);
    sfVector2f cl;

    if (cc.x < rc.x - P_LENGTH / 2.0)
        cl.x = rc.x;
    if (cc.x > rc.x + P_LENGTH / 2.0)
        cl.x = rc.x + P_LENGTH / 2.0;
    if (cc.x >= rc.x - P_LENGTH / 2.0 && cc.x <= rc.x + P_LENGTH / 2.0)
        cl.x = cc.x;
    if (cc.y < rc.y - P_LENGTH / 2.0)
        cl.y = rc.y;
    if (cc.y > rc.y + P_LENGTH / 2.0)
        cl.y = rc.y + P_LENGTH / 2.0;
    if (cc.y >= rc.y - P_LENGTH / 2.0 && cc.y <= rc.y + P_LENGTH / 2.0)
        cl.y = cc.y;
    return sqrt((cc.x - cl.x) * (cc.x - cl.x) + (cc.y - cl.y) *
        (cc.y - cl.y)) <= t->radius;
}

static void is_in_tower_range(struct plane_data *p, double time,
    struct l_list **towers)
{
    struct l_list *head = *towers;
    struct tower_data *tower;

    for (; head; head = head->next) {
        tower = head->data;
        if (tower_plane_collide(p, time, tower)) {
            p->is_in_tower = 1;
            return;
        }
    }
    p->is_in_tower = 0;
}

void collisions(struct l_list **planes, struct l_list **towers,
    struct window_param *window)
{
    sfTime time = sfClock_getElapsedTime(window->clock);
    double seconds = (double)time.microseconds / 1000000.0;
    struct l_list *head = *planes;
    struct plane_data *plane;

    for (; head; head = head->next) {
        plane = head->data;
        get_subtree(plane, seconds);
        is_in_tower_range(plane, seconds, towers);
    }
    head = *planes;
    for (; head; head = head->next) {
        plane = head->data;
        check_plane_collision(plane, planes, seconds);
    }
}
