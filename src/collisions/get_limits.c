/*
** EPITECH PROJECT, 2024
** B_MUL_100_LIL_1_1_myradar_enzo_dubeaurepaire
** File description:
** get_limits.c
*/

#include "../../include/my.h"

double get_max_time(struct l_list **planes)
{
    struct l_list *head = *planes;
    struct plane_data *plane;
    double max = 0;

    for (; head; head = head->next) {
        plane = head->data;
        if (plane->travel_time + plane->delay > max)
            max = plane->travel_time + plane->delay;
    }
    return max;
}

double get_y_max(struct plane_data *p, double time)
{
    double cy = p->init.y + (time - (double)p->delay) * p->speed *
        sin(p->angle);
    double y1 = cy - sin(p->angle) * P_WIDTH / 2.0 + cos(p->angle) *
        P_WIDTH / 2.0;
    double y2 = cy + sin(p->angle) * P_WIDTH / 2.0 + cos(p->angle) *
        P_WIDTH / 2.0;
    double y3 = cy + sin(p->angle) * P_WIDTH / 2.0 - cos(p->angle) *
        P_WIDTH / 2.0;
    double y4 = cy - sin(p->angle) * P_WIDTH / 2.0 - cos(p->angle) *
        P_WIDTH / 2.0;

    if (y1 >= y2 && y1 >= y3 && y1 >= y4)
        return y1;
    if (y2 >= y3 && y2 >= y4)
        return y2;
    if (y3 >= y4)
        return y3;
    return y4;
}

double get_y_min(struct plane_data *p, double time)
{
    double cy = p->init.y + (time - (double)p->delay) * p->speed *
        sin(p->angle);
    double y1 = cy - sin(p->angle) * P_WIDTH / 2.0 + cos(p->angle) *
        P_WIDTH / 2.0;
    double y2 = cy + sin(p->angle) * P_WIDTH / 2.0 + cos(p->angle) *
        P_WIDTH / 2.0;
    double y3 = cy + sin(p->angle) * P_WIDTH / 2.0 - cos(p->angle) *
        P_WIDTH / 2.0;
    double y4 = cy - sin(p->angle) * P_WIDTH / 2.0 - cos(p->angle) *
        P_WIDTH / 2.0;

    if (y1 <= y2 && y1 <= y3 && y1 <= y4)
        return y1;
    if (y2 <= y3 && y2 <= y4)
        return y2;
    if (y3 <= y4)
        return y3;
    return y4;
}

double get_x_max(struct plane_data *p, double time)
{
    double cx = p->init.x + (time - (double)p->delay) * p->speed *
        cos(p->angle);
    double x1 = cx - cos(p->angle) * P_WIDTH / 2.0 - sin(p->angle) *
        P_WIDTH / 2.0;
    double x2 = cx + cos(p->angle) * P_WIDTH / 2.0 - sin(p->angle) *
        P_WIDTH / 2.0;
    double x3 = cx + cos(p->angle) * P_WIDTH / 2.0 + sin(p->angle) *
        P_WIDTH / 2.0;
    double x4 = cx - cos(p->angle) * P_WIDTH / 2.0 + sin(p->angle) *
        P_WIDTH / 2.0;

    if (x1 >= x2 && x1 >= x3 && x1 >= x4)
        return x1;
    if (x2 >= x3 && x2 >= x4)
        return x2;
    if (x3 >= x4)
        return x3;
    return x4;
}

double get_x_min(struct plane_data *p, double time)
{
    double cx = p->init.x + (time - (double)p->delay) * p->speed *
        cos(p->angle);
    double x1 = cx - cos(p->angle) * P_WIDTH / 2.0 - sin(p->angle) *
        P_WIDTH / 2.0;
    double x2 = cx + cos(p->angle) * P_WIDTH / 2.0 - sin(p->angle) *
        P_WIDTH / 2.0;
    double x3 = cx + cos(p->angle) * P_WIDTH / 2.0 + sin(p->angle) *
        P_WIDTH / 2.0;
    double x4 = cx - cos(p->angle) * P_WIDTH / 2.0 + sin(p->angle) *
        P_WIDTH / 2.0;

    if (x1 <= x2 && x1 <= x3 && x1 <= x4)
        return x1;
    if (x2 <= x3 && x2 <= x4)
        return x2;
    if (x3 <= x4)
        return x3;
    return x4;
}
