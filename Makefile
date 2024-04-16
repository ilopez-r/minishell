# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/12 17:53:46 by ilopez-r          #+#    #+#              #
#    Updated: 2024/04/12 18:21:59 by ilopez-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Werror -Wextra

FILES = src/minishell.c\
		src/minishell_utils/builtins/cd.c\
		src/minishell_utils/builtins/echo.c\
		src/minishell_utils/builtins/env.c\
		src/minishell_utils/builtins/pwd.c\
		src/minishell_utils/builtins/exit.c\
		src/minishell_utils/builtins/export.c\
		src/minishell_utils/builtins/unset.c\
		src/minishell_utils/checks/checks.c\
		src/minishell_utils/design/design.c\
		src/minishell_utils/executer/exec_route_pipes.c\
		src/minishell_utils/executer/exec_route.c\
		src/minishell_utils/executer/executer.c\
		src/minishell_utils/executer/msg_error.c\
		src/minishell_utils/expand/expand.c\
		src/minishell_utils/frees/free_all.c\
		src/minishell_utils/frees/free_cd_error.c\
		src/minishell_utils/frees/free_dptr.c\
		src/minishell_utils/frees/free_nodes.c\
		src/minishell_utils/frees/free_t_parser.c\
		src/minishell_utils/parser/here_doc.c\
		src/minishell_utils/parser/parser_utils.c\
		src/minishell_utils/parser/parser.c\
		src/minishell_utils/route/get_route.c\
		src/minishell_utils/signals/signals.c\
		src/minishell_utils/splits/split_cmds.c\
		src/minishell_utils/splits/split_path.c\
		src/minishell_utils/splits/split_words.c\
		src/minishell_utils/tests/tests.c\
		
OBJS = $(FILES:.c=.o)

LIBFT_PATH = ./libftc

LIBFT = $(LIBFT_PATH)/libft.a

INC_SYS = -I ./include -I /Users/ilopez-r/.brew/opt/readline/include

LIB_SYS = -L /Users/ilopez-r/.brew/opt/readline/lib -lreadline

all : $(NAME) $(LIBFT)

$(LIBFT) :
	@make -s -C $(LIBFT_PATH)

$(NAME) : $(OBJS) $(LIBFT)
	@gcc $(FLAGS) $(FILES) $(LIBFT) $(INC_SYS) $(LIB_SYS)  -o $(NAME)

$(OBJS) : $(FILES)
	@gcc $(FLAGS) -c $< -o $@

clean:
	@rm -fr $(OBJS) $(OBJS_BONUS)
	@make clean -s -C $(LIBFT_PATH)

fclean: clean
	@rm -fr $(NAME)
	@make fclean -s -C $(LIBFT_PATH)

re: fclean all

.PHONY : all clean fclean re
