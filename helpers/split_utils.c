/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:17:39 by ksinistr          #+#    #+#             */
/*   Updated: 2020/10/28 16:17:54 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void				space_split(t_split_vars *sv, int *res_c, char **s)
{
	if (sv->tmp && *(sv->tmp))
	{
		(sv->res_arr)[(*res_c)++] = (sv->tmp);
		if (!((sv->res_arr) = ft_realloc((sv->res_arr), *res_c + 2)))
			exit(-1);
		sv->tmp = NULL;
	}
	while (**s == ' ' || **s == '\n')
		(*s)++;
}
