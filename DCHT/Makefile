# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ijang <flan101544@gmail.com>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/10 12:57:12 by ijang             #+#    #+#              #
#    Updated: 2021/12/10 22:18:06 by ijang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		DCHT.out

CC =		gcc

CFLAGS =	-Wall -Wextra -Werror -I includes/ -lwiringPi -lpthread

DOTMATRIX =	dotmatrix dotmatrix_add
DHT11 =		dht11_read
SW =		switch
UTILS =		util
DCHT =		dcht_struct make_matrix main

SRC =		$(addsuffix .c, $(addprefix srcs/dotmatrix/, $(DOTMATRIX))) \
			$(addsuffix .c, $(addprefix srcs/dht11/, $(DHT11))) 		\
			$(addsuffix .c, $(addprefix srcs/switch/, $(SW))) 		\
			$(addsuffix .c, $(addprefix srcs/utils/, $(UTILS)))			\
			$(addsuffix .c, $(addprefix srcs/, $(DCHT)))

OBJ = $(SRC:c=o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(RUNOBJ)

run: $(NAME)
	./$(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re run
