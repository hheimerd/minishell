/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:00:55 by hheimerd          #+#    #+#             */
/*   Updated: 2020/10/28 18:10:11 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_strchr_s(char *s, char *c)
{
	while (*s)
		if (ft_strchr(c, *(s++)) == 0)
			return (1);
	return (0);
}

int			exit_shell(char **args)
{
	write(1, "exit\n", 5);
	if (!*args)
		exit(g_ret);
	if ((*args && *args[0] == '\0') || (ft_strchr_s(*args, "1234567890")))
	{
		put_error("minishell", "exit", *args, "numeric argument required");
		exit(255);
	}
	else if (*(args + 1))
	{
		put_error("minishell", "exit", NULL, "too many arguments");
		return (1);
	}
	exit(ft_atoi(*args));
}
