/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 17:26:54 by ksinistr          #+#    #+#             */
/*   Updated: 2020/10/28 17:01:16 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void				other_commands(char **args)
{
	if ((g_pid = fork()) == 0)
		other(args);
	if (g_pid == -1)
		put_error("minishell", *args, NULL, NULL);
	else
	{
		wait(&g_ret);
		if (g_ret == 32512)
			g_ret = 127;
		else if (g_ret == 2)
		{
			g_ret = 130;
			write(1, "\n", 1);
		}
		else if (g_ret == 3)
		{
			g_ret = 131;
			write(1, "Quit: 3\n", 8);
		}
		else if (g_ret != 0)
			g_ret = 1;
		g_pid = 0;
	}
}

void				parse_command(char **args, t_redirect *next)
{
	replace_env(args);
	if (*args == 0)
	{
		g_ret = 127;
		if (!next)
			put_error("minishell", "", NULL, "command not found");
		return ;
	}
	if (!ft_strncmp(*args, "cd", 3))
		g_ret = cd(args + 1);
	else if (!ft_strncmp(*args, "exit", 5))
		g_ret = exit_shell(args + 1);
	else if (!ft_strncmp(*args, "pwd", 4))
		g_ret = pwd();
	else if (!ft_strncmp(*args, "env", 4))
		g_ret = get_env(args + 1);
	else if (!ft_strncmp(*args, "export", 7))
		g_ret = ft_export(args + 1);
	else if (!ft_strncmp(*args, "echo", 5))
		g_ret = echo(args + 1);
	else if (!ft_strncmp(*args, "unset", 6))
		g_ret = unset(args + 1);
	else
		other_commands(args);
}
