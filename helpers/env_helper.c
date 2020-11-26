/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:44:10 by hheimerd          #+#    #+#             */
/*   Updated: 2020/10/28 16:13:27 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char			*ft_getenv(char *name)
{
	int			counter;
	int			i;

	i = 0;
	if (!name || !g_env)
		return ("");
	if (!g_env[i])
		return ("");
	while (g_env[i])
	{
		counter = ft_strlen(name);
		if (ft_strncmp(g_env[i], name, counter) == 0 &&
			(g_env[i])[counter] == '=')
			return (g_env[i] + counter + 1);
		i++;
	}
	return ("");
}

static void		moove_arr(char **arr)
{
	int			i;

	i = 0;
	free(*arr);
	arr[i] = arr[i + 1];
	i++;
	while (arr[i])
	{
		arr[i] = arr[i + 1];
		i++;
	}
}

static void		replace_symb(char **arr, int *i)
{
	char		*tmp;
	char		*back_locate;
	int			diff;

	if (!(back_locate = ft_strchr((*arr) + *i + 1, '\a')))
		return ;
	(*arr)[*i] = 0;
	*back_locate = 0;
	tmp = (*arr)[*i + 1] == '?' ? ft_itoa(g_ret) : ft_getenv((*arr) + *i + 1);
	if (!tmp)
		exit(-1);
	diff = ft_strlen(tmp);
	back_locate = ft_strjoin(tmp, back_locate + 1);
	if ((*arr)[*i + 1] == '?')
		free(tmp);
	tmp = *arr;
	if (!(*arr = ft_strjoin(tmp, back_locate)))
		exit(-1);
	*i += diff;
	free(back_locate);
	free(tmp);
}

void			replace_env(char **arr)
{
	char		*tmp;
	int			i;
	int			is_empty;

	while (*arr)
	{
		is_empty = **arr ? 0 : 1;
		i = 0;
		if ((*arr)[0] == '~')
		{
			tmp = *arr;
			*arr = ft_strjoin(g_my_home, tmp + 1);
			free(tmp);
		}
		while ((*arr)[i])
		{
			(*arr)[i] == '\a' && ((ft_isalnum((*arr)[i + 1])) ||
													(*arr)[i + 1] == '?') ?
				replace_symb(arr, &i) : i++;
		}
		if (!is_empty && !**arr)
			moove_arr(arr);
		else
			arr++;
	}
}
