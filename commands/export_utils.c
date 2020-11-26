/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:00:36 by ksinistr          #+#    #+#             */
/*   Updated: 2020/10/28 15:48:36 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**init_arg_arr(char *arg)
{
	char	**arg_arr;

	if (!(arg_arr = ft_calloc(4, sizeof(char *))))
		exit(-1);
	if (!(arg_arr[0] = ft_calloc(ft_strlen(arg) + 1, sizeof(char))))
		exit(-1);
	if (!(arg_arr[1] = ft_calloc(2, sizeof(char))))
		exit(-1);
	if (!(arg_arr[2] = ft_calloc(ft_strlen(arg) + 1, sizeof(char))))
		exit(-1);
	return (arg_arr);
}

/*
** split each argument to [value], [=], [key]
*/

char		**split_arg_to_arr(char *arg)
{
	int		i;
	int		j;
	char	**arg_arr;

	arg_arr = init_arg_arr(arg);
	i = 0;
	while (arg[i] != '=' && arg[i] != '\0')
	{
		arg_arr[0][i] = arg[i];
		i++;
	}
	if (arg[i++] == '=')
	{
		arg_arr[1][0] = '=';
		j = 0;
		while (arg[i] != '\0')
			arg_arr[2][j++] = arg[i++];
	}
	return (arg_arr);
}

int			array_length(char **arr)
{
	int		i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int			is_equal_strings(char *s1, char *s2)
{
	if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0 && \
		ft_strlen(s1) == ft_strlen(s2))
	{
		return (1);
	}
	return (0);
}

int			is_string_alnum(char *string)
{
	while (*string)
	{
		if (!ft_isalnum(*string))
			return (0);
		string++;
	}
	return (1);
}
