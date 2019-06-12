# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crycherd <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/05 20:26:26 by crycherd          #+#    #+#              #
#    Updated: 2019/06/12 17:03:54 by crycherd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
FLAGS = -Wall -Wextra -Werror -I.
SOURCE = input twolist validity get_next_line fill3

all: $(NAME)

$(NAME): $(addprefix ft_,$(SOURCE:=.o))
	gcc $(FLAGS) $^ libft.a -o $(NAME)

ft_%.o: $(@:.o=.c)
	gcc  $(FLAGS) -c $(@:.o=.c)

clean:
	rm -f $(addprefix ft_,$(SOURCE:=.o))

fclean: clean
	rm -f $(NAME)

re: fclean all

