/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:32:08 by hheimerd          #+#    #+#             */
/*   Updated: 2020/10/28 16:22:46 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			get_env(char **args)
{
	int		i;

	i = 0;
	if (*args)
	{
		put_error("env", NULL, *args, "No such file or directory");
		return (127);
	}
	while (g_env[i])
	{
		if (ft_strchr(g_env[i], '=') != 0)
			ft_putendl_fd(g_env[i], 1);
		i++;
	}
	return (0);
}
