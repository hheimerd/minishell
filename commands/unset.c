/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:51:24 by hheimerd          #+#    #+#             */
/*   Updated: 2020/10/28 17:51:30 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid(char *string)
{
	if (ft_strchr(string, '/') \
			|| ft_strchr(string, '=') \
			|| ft_strchr(string, '@') \
			|| ft_strchr(string, ',') \
			|| ft_strchr(string, '.') \
			|| ft_strchr(string, '*'))
	{
		return (0);
	}
	return (1);
}

static void	remove_value(char *arg, int g_env_len)
{
	char	**g_env_new;
	char	**g_env_arr;
	char	**tmp;
	int		i;
	int		j;

	if (!(g_env_new = ft_calloc(g_env_len, sizeof(char *))))
		exit(-1);
	i = -1;
	j = 0;
	while (++i < g_env_len)
	{
		g_env_arr = split_arg_to_arr(g_env[i]);
		if (!is_equal_strings(arg, g_env_arr[0]))
		{
			g_env_new[j] = g_env[i];
			j++;
		}
		else
			free(g_env[i]);
		del_arr(&g_env_arr);
	}
	tmp = g_env;
	g_env = g_env_new;
	free(tmp);
}

int			unset_put_error(char **args)
{
	put_error("minishell", "unset", *args, "not a valid identifier");
	return (1);
}

int			unset(char **args)
{
	int		i;
	int		found;
	char	**g_env_arr;

	if (*args && (*args[0] == '\0' || !ft_isalpha(*args[0]) || \
		!is_string_alnum(&(*args)[1])))
		return (unset_put_error(args));
	while (*args)
	{
		if (!is_valid(*args))
			return (unset_put_error(args));
		found = 0;
		i = -1;
		while (++i < array_length(g_env))
		{
			g_env_arr = split_arg_to_arr(g_env[i]);
			if (is_equal_strings(*args, g_env_arr[0]))
				found = 1;
			del_arr(&g_env_arr);
		}
		if (found == 1)
			remove_value(*args, array_length(g_env));
		args++;
	}
	return (0);
}
