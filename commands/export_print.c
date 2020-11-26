/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 13:49:50 by ksinistr          #+#    #+#             */
/*   Updated: 2020/10/25 17:12:23 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		g_env_sort(char **g_env_new, int g_env_len)
{
	int		i;
	int		is_sorted;
	char	*tmp;

	is_sorted = 0;
	while (is_sorted == 0)
	{
		is_sorted = 1;
		i = -1;
		while (++i < g_env_len - 1)
		{
			if (ft_strncmp(g_env_new[i], g_env_new[i + 1], \
				ft_strlen(g_env_new[i])) > 0)
			{
				tmp = g_env_new[i];
				g_env_new[i] = g_env_new[i + 1];
				g_env_new[i + 1] = tmp;
				is_sorted = 0;
				break ;
			}
		}
	}
}

void		print_array(char **arr)
{
	int		i;
	char	**arg_arr;

	i = 0;
	while (arr[i])
	{
		arg_arr = split_arg_to_arr(arr[i]);
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(arg_arr[0], 1);
		if (arg_arr[1][0] != '\0')
		{
			ft_putstr_fd(arg_arr[1], 1);
			ft_putchar_fd('\"', 1);
			ft_putstr_fd(arg_arr[2], 1);
			ft_putchar_fd('\"', 1);
		}
		write(1, "\n", 1);
		del_arr(&arg_arr);
		i++;
	}
}

void		export_print(int g_env_len)
{
	char	**g_env_new;
	int		i;

	if (!(g_env_new = ft_calloc((g_env_len + 1), sizeof(*g_env))))
		exit(-1);
	i = 0;
	while (i < g_env_len)
	{
		g_env_new[i] = ft_strdup(g_env[i]);
		i++;
	}
	g_env_sort(g_env_new, g_env_len);
	print_array(g_env_new);
	del_arr(&g_env_new);
}
