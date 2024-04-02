/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismael <ismael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:21:29 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/02 22:32:53 by ismael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libftc/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_env
{
	char			*name;
	char			*content;
	int				index;
	struct s_env	*next;
}	t_env;

typedef struct s_parser
{
	char	**full_cmd;
	char	*route;
	int		in;
	int		out;
}	t_parser;

typedef struct s_data
{
	char	*line;
	char	**path;
	t_env	*env;
	char	*tmp;
	int		path_flag;
	char	**cmds;
	char	***words;
	char	q;
	int		f;
	int		len;
	int		d;
	int		a;
	int		b;
	char	*str;
	int		f_hd;
	int		f_token;
	t_list	*nodes;
}	t_data;

int		main(int argc, char **argv, char **env);
int		prompt(t_data *data);
void	piti_shell(void);
void	cigarrette(void);
int		split_path(t_data *data);
void	get_env(t_data *data, char **env);
int		split_cmds(t_data *data);
int		parser(t_data *data, int i, int j);
int		ft_token_1(t_data *d, int *i, int *j, t_parser **n);
int		ft_token_2(t_data *d, int *i, int *j, t_parser **n);
char	**ft_split_words(t_data *data, char const *s, char c, int i);
void	free_nodes(t_list **lst);
void	pwd_exe(void);
void	env_exe(t_data *data);
void	cd_exe(t_data *d, char **s, int flag);
void	unset_exe(t_data *data, char *name);
void	check_path(t_data *data);
int		exit_exe(t_data *data, t_parser *nodes);
void	free_path(t_data *data);
int		env_size(t_env *lst);
void	set_index(t_data *data);
void	check_path(t_data *data);
void	free_path(t_data *data);
void	export_exe(t_data *data, char **s, int index);

#endif