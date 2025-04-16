# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hceviz <hceviz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 10:53:09 by hceviz            #+#    #+#              #
#    Updated: 2025/04/16 18:48:37 by hceviz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = clang
CFLAGS = -g -fsanitize=thread -fno-omit-frame-pointer -O0
SRCS = dinner.c init.c main.c ops.c \
	utils.c
OBJS = $(SRCS:.c=.o) #double check

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

re: fclean all

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)