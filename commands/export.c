/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 17:06:02 by ksinistr          #+#    #+#             */
/*   Updated: 2020/10/28 17:48:32 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_value(char **val_ptr, char *arg)
{
	char	*tmp;

	tmp = *val_ptr;
	if (!(*val_ptr = ft_strdup(arg)))
		exit(-1);
	free(tmp);
}

static void	add_value(char *arg, int g_env_len)
{
	char	**g_env_new;
	char	**tmp;
	int		i;

	if (!(g_env_new = ft_calloc((g_env_len + 2), sizeof(*g_env))))
		exit(-1);
	i = 0;
	while (i < g_env_len)
	{
		g_env_new[i] = g_env[i];
		i++;
	}
	g_env_new[i] = ft_strdup(arg);
	tmp = g_env;
	g_env = g_env_new;
	free(tmp);
}

void		set_or_add_value(char *args)
{
	int		i;
	int		found;
	char	**arg_arr;
	char	**g_env_arr;

	found = 0;
	arg_arr = split_arg_to_arr(args);
	i = 0;
	while (i < array_length(g_env))
	{
		g_env_arr = split_arg_to_arr(g_env[i]);
		if (is_equal_strings(arg_arr[0], g_env_arr[0]))
		{
			found = 1;
			if (arg_arr[1][0] == '=')
				set_value(&(g_env[i]), args);
		}
		del_arr(&g_env_arr);
		i++;
	}
	if (found == 0)
		add_value(args, array_length(g_env));
	del_arr(&arg_arr);
}

static int	is_valid_identifier(char *env)
{
	char	**env_arr;

	env_arr = split_arg_to_arr(env);
	if (!is_string_alnum(env_arr[0]) || !ft_isalpha(env_arr[0][0]))
	{
		return (0);
	}
	return (1);
}

int			ft_export(char **args)
{
	int		i;

	i = -1;
	while (args[++i])
	{
		if (!is_valid_identifier(args[i]))
		{
			put_error("minishell", "export", args[i], \
				"not a valid identifier");
			return (1);
		}
	}
	if (!(*args))
		export_print(array_length(g_env));
	while (*args)
	{
		set_or_add_value(*args);
		args++;
	}
	return (0);
}
