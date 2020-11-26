
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/07 12:26:13 by hheimerd          #+#    #+#              #
#    Updated: 2020/10/28 17:08:46 by ksinistr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS 		= -Wall -Wextra -Werror -O0 -ggdb3 
CC 			= gcc
NAME 		= minishell
LIB_DIR		= libft
LIB			= $(LIB_DIR)/libft.a
SRC			= main.c \
			  GNL/get_next_line.c \
			  GNL/get_next_line_utils.c \
			  commands/pwd.c \
			  commands/cd.c \
			  commands/exit_shell.c \
			  commands/get_env.c \
			  commands/export.c \
			  commands/export_print.c \
			  commands/export_utils.c \
			  commands/unset.c \
			  commands/echo.c \
			  commands/other.c \
 			  pipe/pipe.c \
 			  pipe/redirect.c \
 			  pipe/parse_command.c \
 			  pipe/parse_command_line.c \
			  helpers/put_error.c \
			  helpers/split.c \
			  helpers/split_utils.c \
			  helpers/list_helper.c \
			  helpers/memory.c \
			  helpers/parse_signal.c \
			  helpers/multiple_lines.c \
			  helpers/struct_helper.c \
			  helpers/handlers.c \
			  helpers/env_helper.c

SRC_OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(SRC_OBJ) minishell.h
	$(CC) $(FLAGS) $(SRC_OBJ) $(LIB) -o $(NAME)

$(LIB):
	make -C $(LIB_DIR);

clean:
	rm -f $(SRC_OBJ)
	make clean -C $(LIB_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIB_DIR)

re: fclean all

.c.o:
	$(CC) $(FLAGS) -c $< -o $@
