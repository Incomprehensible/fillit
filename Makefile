# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crycherd <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/05 20:26:26 by crycherd          #+#    #+#              #
#    Updated: 2019/06/13 15:26:34 by crycherd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
FLAGS = -Wall -Wextra -Werror -I libft/includes
SOURCE = input.c twolist.c validity.c fill2.c fill3.c fill4.c fill5.c main.c
OBJ = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): libft.a
	gcc $(FLAGS) -c $(OBJ:.o=.c)
	gcc -o $@ $(OBJ) -I libft/includes -L libft/ -lft

libft.a:
	make -C libft/

clean:
	rm -f $(OBJ)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all

