/*
** EPITECH PROJECT, 2023
** B_MUL_100_LIL_1_1_myradar_enzo_dubeaurepaire
** File description:
** window.c
*/

#include "../include/my.h"

void is_end(struct window_param *window, struct l_list **planes)
{
    if (*planes)
        return;
    sfRenderWindow_close(window->window);
}

void destroy(sfSprite *sprite, sfTexture *texture)
{
    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
}

static void display_timer(struct window_param *window)
{
    sfTime time = sfClock_getElapsedTime(window->clock);
    int seconds = time.microseconds / 1000000;
    char *min_s = my_nb_to_str(seconds / 60);
    char *sec_s = my_nb_to_str(seconds);
    char *sec_min_s = my_nb_to_str(seconds - (seconds / 60) * 60);
    char *min_sec = malloc(my_strlen(min_s) + my_strlen(sec_min_s) + 2);

    if (!window->time_min) {
        sfText_setString(window->timer, sec_s);
    } else {
        min_sec[0] = 0;
        my_strcat(min_sec, min_s);
        my_strcat(min_sec, ":");
        my_strcat(min_sec, sec_min_s);
        sfText_setString(window->timer, min_sec);
    }
    free(min_s);
    free(min_sec);
    free(sec_s);
    free(sec_min_s);
}

static void actions(struct l_list **planes, struct window_param *window)
{
    sfTime time = sfClock_getElapsedTime(window->clock);

    display_timer(window);
    move_planes(planes, window, time);
    are_landed(planes, window, time);
}

static void draw(struct window_param *window, sfSprite *background)
{
    sfRenderWindow_drawSprite(window->window, background, 0);
    sfRenderWindow_drawText(window->window, window->timer, NULL);
}

void game_loop(struct window_param *window,
    struct l_list **planes, struct l_list **towers)
{
    sfTexture *background_texture =
        sfTexture_createFromFile("assets/map.png", NULL);
    sfSprite *background = sfSprite_create();

    sfSprite_setTexture(background, background_texture, 1);
    sfClock_restart(window->clock);
    while (sfRenderWindow_isOpen(window->window)) {
        while (sfRenderWindow_pollEvent(window->window, window->event))
            analyse_event(window);
        launch_planes(planes, window->clock);
        sfRenderWindow_clear(window->window, sfBlack);
        actions(planes, window);
        draw(window, background);
        collisions(planes, towers, window);
        show_towers(window, towers);
        show_planes(window, planes);
        sfRenderWindow_display(window->window);
        is_end(window, planes);
    }
    destroy(background, background_texture);
}

sfText *create_text(sfFont *font)
{
    sfText *text = sfText_create();

    sfText_setFont(text, font);
    sfText_setColor(text, sfWhite);
    sfText_setCharacterSize(text, 60);
    sfText_setPosition(text, (sfVector2f){1800, 0});
    return text;
}

static void destroy_win(sfText *text, sfFont *font, sfClock *clock)
{
    sfText_destroy(text);
    sfFont_destroy(font);
    sfClock_destroy(clock);
}

static void init_window(struct window_param *window_param)
{
    window_param->time_min = 0;
    window_param->hit_box = 1;
    window_param->show_sprites = 1;
    window_param->rainbow = 0;
}

void create_window(struct l_list **planes, struct l_list **towers)
{
    struct window_param window_param;
    sfFont *font = sfFont_createFromFile("assets/digital-7.ttf");
    sfEvent event;
    sfClock *clock = sfClock_create();
    sfRenderWindow *window;
    sfVideoMode mode = {WIN_LENGTH, WIN_WIDTH, 32};

    window = sfRenderWindow_create(mode, "my_radar", sfClose | sfResize,
        NULL);
    sfRenderWindow_setFramerateLimit(window, 60);
    window_param.clock = clock;
    init_window(&window_param);
    window_param.timer = create_text(font);
    window_param.window = window;
    window_param.event = &event;
    game_loop(&window_param, planes, towers);
    destroy_win(window_param.timer, font, clock);
    sfRenderWindow_destroy(window);
}
