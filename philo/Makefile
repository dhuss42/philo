# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhuss <dhuss@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/14 12:07:15 by dhuss             #+#    #+#              #
#    Updated: 2024/11/21 12:44:38 by dhuss            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Werror -Wextra -Wall
CFILES = main.c\
	parser.c\
	set_the_table.c\
	dinner.c\
	error_handling.c\

OBJ_DIR = obj
OFILES =$(CFILES:%.c=$(OBJ_DIR)/%.o)
NAME = philo

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OFILES)
	@$(CC) $(CFLAGS) $(OFILES) -o $(NAME)
	@echo "\033[32m building philo! \033[0m"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[33m cleaning philo files \033[0m"
	@rm -f $(OFILES)
	@rm -rf $(OBJ_DIR)

fclean:
	@echo "\033[33m fcleaning philo files \033[0m"
	@rm -f $(OFILES)
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)

re:
	@echo "\033[35m re making... \033[0m"
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re