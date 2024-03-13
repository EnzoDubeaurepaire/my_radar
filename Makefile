##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SRC	=	include/utility/my_putnbr.c \
		include/utility/my_strcat.c \
		include/utility/my_strcpy.c \
		include/utility/my_strlen.c \
		include/utility/my_bzero.c \
		include/utility/my_getnbr.c \
		include/utility/my_str_islower.c \
		include/utility/my_str_isnum.c \
		include/utility/my_str_isupper.c \
		include/utility/my_str_to_word_array.c \
		include/utility/my_nb_to_str.c \
		src/events/event_manager.c \
		src/sprite/init_sprites.c \
		src/sprite/show_sprites.c \
		src/linked_list/add_in_list.c \
		src/linked_list/del_in_list.c \
		src/collisions/collisions.c \
		src/collisions/get_limits.c \
		src/parsing/parsing.c \
		src/main.c \
		src/window.c \
		src/move_planes.c \

OBJ	=	$(SRC:.c=.o)

FLAGS	=	-Werror -Wall -Wextra -lcsfml-system -lcsfml-window

FLAGS2  = -lcsfml-network -lcsfml-graphics -lcsfml-audio -lm -Wno-unused

NAME	=	my_radar

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(FLAGS) $(FLAGS2)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
