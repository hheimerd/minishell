/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:16:52 by hheimerd          #+#    #+#             */
/*   Updated: 2020/10/28 18:22:20 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				**fill_g_env(char **env)
{
	char			**g_env;
	int				j;
	int				i;

	i = 0;
	while (env[i])
		i++;
	if (!(g_env = malloc((i + 1) * sizeof(*g_env))))
		exit(-1);
	g_env[i] = NULL;
	j = 0;
	while (j < i)
	{
		if (!(g_env[j] = ft_strdup(env[j])))
			exit(-1);
		j++;
	}
	return (g_env);
}

int					put_error_or_exit_by_status(int status, int pipe_exist)
{
	if (status == 0)
	{
		if (!pipe_exist)
			put_error("minishell", NULL, NULL,
			"unexpected EOF while looking for matching `\"'");
		put_error("minishell", "syntax error", NULL, \
				"unexpected end of file");
	}
	if (status == -1)
		exit(-1);
	return (pipe_exist);
}

void				broke_line_loop(char **line_pointer, int *status)
{
	char			*tmp;
	char			*line;

	line = *line_pointer;
	while (find_quotes(line) || find_pipe(line) || (*status == 0 && *line))
	{
		if (*status)
		{
			line = append_c(line, '\n');
			write(1, ">", 1);
		}
		tmp = line;
		if ((*status = get_next_line(0, &line)) == -1)
			break ;
		tmp = ft_strjoin_gnl(tmp, line);
		free(line);
		line = tmp;
		if (*status == 0 && (find_quotes(line) || find_pipe(line)))
			break ;
	}
	*line_pointer = *line ? line : tmp;
	if (!*line)
		free(line);
	put_error_or_exit_by_status(*status, find_pipe(*line_pointer));
}

void				init_globals_and_signals(int argc, char **argv, char **env)
{
	if (argc || argv)
		g_env = fill_g_env(env);
	if (!(g_my_home = ft_strdup(ft_getenv("HOME"))))
		exit(-1);
	g_ret = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigbreak_handler);
}

int					main(int argc, char **argv, char **env)
{
	char			*line;
	t_cmdlist		*cmdlist;
	int				status;

	init_globals_and_signals(argc, argv, env);
	ft_putstr_fd(RED "minishell>" RES, 1);
	while ((status = get_next_line(0, &line)) == 1 || (status == 0 && *line))
	{
		if (handle_null_line(line) || find_semicolons_doubles(line))
			continue ;
		broke_line_loop(&line, &status);
		if (!find_pipe(line) && !find_quotes(line))
		{
			cmdlist = split_line(line);
			status = parse_command_line(cmdlist);
			remove_struct(cmdlist);
		}
		free(line);
		if (status < 0)
			break ;
		ft_putstr_fd(RED "minishell>" RES, 1);
	}
	if (status == -1)
		exit(-1);
	return (g_ret);
}
