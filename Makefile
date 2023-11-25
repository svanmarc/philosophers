# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 14:09:42 by svanmarc          #+#    #+#              #
#    Updated: 2023/11/17 17:05:47 by svanmarc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

name = philo

SRC_DIR = srcs
SRCS = $(wildcard $(SRC_DIR)/*.c)

OBJS_DIR = objs
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

INCLUDES = -I./includes

LIBS = -lpthread

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g $(INCLUDES)

RM = rm -rf

DEP_FILE = .depend

all: $(name)

$(name): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)
	@echo "\033[32mCompilation done !\033[0m"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[32mCompilation of $< done !\033[0m"

clean:
	$(RM) $(OBJS_DIR) $(DEP_FILE)
	@echo "\033[31mObjects deleted !\033[0m"

fclean: clean
	$(RM) $(name)
	@echo "\033[31m$(name) deleted !\033[0m"

re: fclean all

$(DEP_FILE): $(SRCS) $(INCLUDES)
	@$(CC) -MM $(SRCS) > $(DEP_FILE)

-include $(DEP_FILE)