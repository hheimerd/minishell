/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:53:00 by hheimerd          #+#    #+#             */
/*   Updated: 2020/10/25 15:22:09 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "../minishell.h"

static int			local_programm(char **args)
{
	char			**bash;
	char			**cmd;
	struct stat		buf;

	if (stat(*args, &buf) == -1)
		put_error("minishell", *args, NULL, NULL);
	else if (!(buf.st_mode & S_IXGRP))
		put_error("minishell", *args, NULL, "permission denied");
	else if (buf.st_mode & S_IFDIR)
		put_error("minishell", *args, NULL, "is a directory");
	else
	{
		if (!(bash = (char**)ft_calloc(sizeof(char*), 2)) ||
			!(bash[0] = strdup("/bin/bash")))
			exit(-1);
		cmd = array_concat(bash, args);
		if (execve(*(cmd + 1), cmd + 1, g_env) == -1)
			execve(*cmd, cmd, g_env);
		del_arr(&cmd);
		free(bash);
	}
	exit(127);
}

void				other(char **args)
{
	char			**path;
	char			*tmp;
	int				i;

	if (!(path = ft_split(ft_getenv("PATH"), ':')))
		exit(-1);
	replace_env(path);
	if (!path[0] || ft_match(args[0], "*./*") || ft_strnstr(args[0], "/", 2)
		|| ft_strnstr(args[0], ".", 2))
		local_programm(args);
	i = 0;
	while (path[i])
	{
		path[i] = append_c(path[i], '/');
		tmp = ft_strjoin(path[i], *args);
		execve(tmp, args, g_env);
		i++;
	}
	put_error("minishell", *args, NULL, "command not found");
	del_arr(&path);
	exit(127);
}
