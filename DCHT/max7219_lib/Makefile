# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ijang <flan101544@gmail.com>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 19:11:25 by ijang             #+#    #+#              #
#    Updated: 2021/12/09 00:07:33 by ijang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		libmax7219.a

CC =		gcc

CFLAGS =	-I includes/ -lwiringPi

AR =		ar rc

DOTMATRIX =	dotmatrix dotmatrix_add

UTILS =		util

SRC =		$(addsuffix .c, $(addprefix srcs/dotmatrix/, $(DOTMATRIX))) \
			$(addsuffix .c, $(addprefix srcs/utils/, $(UTILS)))

RUNSRC =	$(SRC) test2.c
TESTSRC =	$(SRC) test3.c

OBJ = $(SRC:c=o)
RUNOBJ = $(RUNSRC:c=o)
TESTOBJ = $(TESTSRC:c=o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJS)
	ranlib $@

run: $(RUNOBJ)
	$(CC) $(CFLAGS) -o run.out $(RUNOBJ)

test: $(TESTOBJ)
	$(CC) $(CFLAGS) -o test.out $(TESTOBJ)

clean:
	rm -f $(RUNOBJ)

fclean: clean
	rm -f $(NAME)
	rm -f run.out
	rm -f test.out

re: fclean all

.PHONY: clean fclean re run
