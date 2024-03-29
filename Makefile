# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/12 17:53:46 by ilopez-r          #+#    #+#              #
#    Updated: 2024/03/15 13:28:40 by ilopez-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Werror -Wextra

FILES = src/minishell.c\
		src/prompt.c\
		src/split_path.c\
		src/builtins/env.c\
		src/split_cmds.c\

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