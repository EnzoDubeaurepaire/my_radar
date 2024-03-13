/*
** EPITECH PROJECT, 2023
** B-MUL-100-LIL-1-1-myradar-enzo.dubeaurepaire
** File description:
** my.h
*/

#ifndef MY_H_
    #define MY_H_
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <SFML/Config.h>
    #include <SFML/Network.h>
    #include <SFML/Window.h>
    #include <SFML/System.h>
    #include <stddef.h>
    #include <math.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <time.h>
    #include <fcntl.h>
    #include <sys/types.h>
    #include <stdio.h>
    #define WIN_LENGTH 1920
    #define WIN_WIDTH 1080
    #define P_LENGTH 20
    #define P_WIDTH 20
    #define T_LENGTH 50
    #define T_WIDTH 50

struct plane_data {
    sfSprite *sprite;
    sfVector2f init;
    sfVector2f arrival;
    sfRectangleShape *hit_box;
    double speed;
    int delay;
    double travel_time;
    double angle;
    int launched;
    int subtree;
    int is_in_tower;
};
struct tower_data {
    sfSprite *sprite;
    sfVector2f position;
    sfCircleShape *hit_box;
    double radius;
    int subtree;
};
struct l_list {
    void *data;
    struct l_list *next;
};
struct game_options {
    sfRenderWindow *window;
    sfEvent event;

};
struct window_param {
    sfRenderWindow *window;
    sfEvent *event;
    sfClock *clock;
    sfText *timer;
    int hit_box;
    int show_sprites;
    int time_min;
    int rainbow;
};
struct textures {
    sfTexture *plane;
    sfTexture *tower;
};
void launch_planes(struct l_list **planes, sfClock *main_clock);
void del_in_list(struct l_list **planes, struct l_list *node);
void are_landed(struct l_list **planes, struct window_param *window, sfTime);
void move_planes(struct l_list **planes, struct window_param *window, sfTime);
void my_bzero(char *str, long size);
void my_putnbr(long nb);
char *my_strcat(char *dest, char const *src);
char *my_strcpy(char *dest, char const *src);
int my_strlen(char const *str);
int parsing(const char *file_name, struct l_list **planes,
    struct l_list **towers, struct textures *textures);
int is_num(char c);
int my_str_isnum(char const *str);
int is_lower(char c);
int is_upper(char c);
char **my_str_to_word_array(char const *str);
int my_getnbr(char const *str);
void add_tower(struct l_list **towers, char **array, sfTexture *texture);
void add_plane(struct l_list **planes, char **array, sfTexture *texture);
sfSprite *get_plane_sprite(sfTexture *texture);
sfSprite *get_tower_sprite(sfTexture *texture);
void create_window(struct l_list **planes, struct l_list **towers);
void show_planes(struct window_param *window, struct l_list **planes);
void show_towers(struct window_param *window, struct l_list **towers);
void analyse_event(struct window_param *window);
sfRectangleShape *init_plane_hit_box(sfVector2f init, double angle);
sfCircleShape *init_tower_hit_box(sfVector2f pos, int radius);
void check_collisions(struct l_list **planes);
void collisions(struct l_list **planes, struct l_list **towers,
    struct window_param *window);
double get_x_min(struct plane_data *p, double time);
double get_y_min(struct plane_data *p, double time);
double get_x_max(struct plane_data *p, double time);
double get_y_max(struct plane_data *p, double time);
double get_max_time(struct l_list **planes);
char *my_nb_to_str(int nb);
#endif
