/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:21:29 by ilopez-r          #+#    #+#             */
/*   Updated: 2024/04/16 11:37:23 by ilopez-r         ###   ########.fr       */
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
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>

int			g_status;

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
	char		q;
	char		*line;
	char		*in;
	char		*out;
	char		*tmp;
	char		*str;
	char		*cd_error;
	char		*aux;
	char		**path;
	char		**cmds;
	char		**ctnt;
	int			path_flag;
	int			f;
	int			len;
	int			d;
	int			a;
	int			b;
	int			i;
	int			j;
	int			f_hd;
	int			f_append;
	int			f_token;
	int			dup_stdin;
	int			f_pipe;
	int			fd[2];
	t_env		*env;
	t_env		*x;
	t_list		*nodes;
	t_parser	*n;
}	t_data;

/*--- <BUILTINS> ---*/
void	cd_exe(t_data *d, char **s, int flag);
void	echo_exe(char **s, int option, int fd);
void	env_exe(t_data *data, int fd);
void	get_env(t_data *data, char **env, int i);
int		env_size(t_env *lst);
int		exit_exe(t_data *data, t_parser *nodes, int fd, int i);
void	export_exe(t_data *data, char **s, int index, int fd);
void	set_index(t_data *data);
void	pwd_exe(int fd);
void	unset_exe(t_data *data, char *name);

/*--- <CHECKS> ---*/
int		check_builtins(t_parser *n);
int		check_node(t_data *data, char **s);
void	check_path(t_data *data);
int		check_quotes(char *s);

/*--- <DESIGN> ---*/
void	cigarrette(void);
void	piti_shell(void);

/*--- <EXECUTER> ---*/
void	exec_route_pipes(t_data *data, t_parser *node, char **env, t_list *aux);
void	exec_route(t_data *data, t_parser *node, char **env);
void	check_f_d(t_parser *node);
int		executer(t_data *data, char **env, t_parser *node, t_list *a);
int		builtins_executer(t_parser *node, t_data *d);
void	msg_error_pipes(char *str);
void	msg_error(char *str);

/*--- <EXPAND> ---*/
void	expand(t_data *data);

/*--- <FREES> ---*/
void	free_all(t_data *data);
void	free_cd_error(t_data *data);
void	free_dptr(char **tmp);
void	free_nodes(t_list **lst);
void	free_t_parser(t_parser *n);

/*--- <PARSER> ---*/
void	here_doc(t_data *data, t_parser **n, char *line);
int		ft_token_infile(t_data *d, int *i, int *j, t_parser **n);
int		ft_token_outfile(t_data *d, int *i, int *j, t_parser **n);
int		parser(t_data *data, int i, int j);

/*--- <ROUTE> ---*/
int		route(t_data *data, int i);

/*--- <SIGNALS> ---*/
void	cat_ctrlc(int sig);
void	cat_ctrlbackslash(int sig);
void	signals(int sig);

/*--- <SPLITS> ---*/
int		split_cmds(t_data *data);
int		split_path(t_data *data);
char	**ft_split_words(t_data *data, char const *s, char c, int i);

/*--- <TESTS> ---*/
void	ft_print_nodes(t_data *d);
void	ft_print_cmds(t_data *d);
void	ft_leaks(void);

#endif