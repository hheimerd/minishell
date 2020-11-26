/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:53:05 by hheimerd          #+#    #+#             */
/*   Updated: 2020/10/28 17:54:54 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			echo(char **args)
{
	int		n;
	int		i;
	int		key;

	n = 0;
	key = 1;
	i = -1;
	while (args[++i] != 0)
	{
		if (!(ft_strncmp(args[i], "-n", 3)) && key)
		{
			n = 1;
			continue ;
		}
		key = 0;
		if (i > 0 && ft_strncmp(args[i - 1], "-n", 3))
			write(1, " ", 1);
		ft_putstr_fd(args[i], 1);
	}
	if (!n)
		write(1, "\n", 1);
	return (0);
}
