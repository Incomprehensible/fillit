# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crycherd <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/05 20:26:26 by crycherd          #+#    #+#              #
#    Updated: 2019/06/12 21:23:13 by crycherd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
FLAGS = -Wall -Wextra -Werror -I libft/includes
SOURCE = input twolist validity fill3

all: $(NAME)

$(NAME): $(addprefix ft_,$(SOURCE:=.o))
	gcc -g -o $@ $^ -I libft/includes -L libft/ -lft

ft_%.o: libft.a $(@:.o=.c)
	gcc  $(FLAGS) -c $(@:.o=.c)

libft.a: 
	make -C libft/

clean:
	rm -f $(addprefix ft_,$(SOURCE:=.o))
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all

