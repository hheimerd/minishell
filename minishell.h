/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:16:31 by hheimerd          #+#    #+#             */
/*   Updated: 2020/10/28 18:41:04 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define RED "\x1B[0;31m"
# define RES "\x1B[0m"
# define CLOSE_STDIN 0
# define CLOSE_STDOUT 1

# include <signal.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# include "GNL/get_next_line.h"
# include <fcntl.h>

typedef struct			s_pipesfds
{
	int					in;
	int					out;
}						t_pipesfds;

typedef struct			s_redirect
{
	char				**cmd;
	char				redirect;
	struct s_redirect	*next;
}						t_redirect;

typedef struct			s_pipe
{
	t_redirect			*redirect;
	struct s_pipe		*next;
}						t_pipe;

typedef struct			s_cmdlist
{
	t_pipe				*pipe;
	struct s_cmdlist	*next;
}						t_cmdlist;

typedef struct			s_split_vars
{
	char				**quote_list;
	t_cmdlist			*cmdlist;
	char				**res_arr;
	char				*tmp;
	int					res_c;
}						t_split_vars;

pid_t					g_pid;
char					**g_env;
int						g_ret;
char					*g_my_home;

t_redirect				*create_redirect(char **cmd, char redirect);
t_pipe					*create_pipe(t_redirect *redirect);
t_cmdlist				*create_cmdlist(t_pipe *pipe);
char					*find_quote(char *s, char find);
char					**get_quote_list(char *s);
t_cmdlist				*add_elem(char *state, t_cmdlist *start,
									char **args, char redirect);
int						find_pipe(char *s);
void					remove_struct(t_cmdlist *start);
t_cmdlist				*split_line(char *s);
void					space_split(t_split_vars *sv, int *res_c, char **s);
char					**ft_realloc(char **src, int size);
char					**array_concat(char **arr1, char **arr2);
int						find_semicolons_doubles(char *s);
char					find_quotes(char *s);
void					sigbreak_handler(int	z);
void					sigint_handler(int	z);
void					other(char **args);
char					*append_c(char *s, char c);
void					replace_env(char **arr);
int						check_unexpected(char *s);
char					*ft_getenv(char *name);
int						get_env(char **args);
int						exit_shell();
int						put_error(char *prog, char *cmd, char *arg, \
						char *error_s);
int						cd(char **args);
int						echo(char **args);
int						get_next_line(int fd, char **line);
int						pwd(void);

/*
** parse_command.c
*/

void					parse_command(char **args, t_redirect *next);

/*
** parse_command_line.c
*/

int						parse_command_line(t_cmdlist *cmdlist);

/*
** handlers.c
*/

int						handle_null_line(char *line);

/*
** export.c
*/

int						ft_export(char **args);
void					set_or_add_value(char *arg);

/*
** export_print.c
*/

void					export_print(int g_env_len);

/*
** export_utils.c
*/

char					**split_arg_to_arr(char *arg);
int						array_length(char **arr);
int						is_equal_strings(char *s1, char *s2);
int						is_string_alnum(char *string);

/*
** unset.c
*/

int						unset(char **args);

/*
** pipe.c
*/

void					pipe_iterations(t_pipe *pipelst);

/*
** redirect.c
*/

void					redirect_switch(t_redirect *redirectlst);

#endif
