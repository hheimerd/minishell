/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 16:14:39 by hheimerd          #+#    #+#             */
/*   Updated: 2020/10/28 18:50:03 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int					find_semicolons_doubles(char *s)
{
	int				i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ';' && s[i + 1] == ';')
		{
			put_error("minishell", NULL, NULL,
				"syntax error near unexpected token `;;'");
			ft_putstr_fd(RED "minishell>" RES, 1);
			return (1);
		}
		i++;
	}
	i--;
	while (s[i])
	{
		if (s[i] == ' ')
			i--;
		else if (s[i] == ';')
			s[i] = 0;
		else
			break ;
	}
	return (check_unexpected(s));
}

char				find_quotes(char *s)
{
	int				bs_c;
	char			find;

	find = 0;
	while (*s)
	{
		if (*s == '\\')
		{
			bs_c = 0;
			while (*(s) == '\\')
				s += ++bs_c ? 1 : 1;
			if (*s == '"' && bs_c % 2 == 0 && find != '\'')
				find = find == 0 ? '"' : 0;
			if (*s == '\'' && (bs_c % 2 == 0 || find == '\'') && find != '"')
				find = find == 0 ? '\'' : 0;
		}
		else if (*s == '"' && find != '\'')
			find = find == 0 ? '"' : 0;
		else if (*s == '\'' && find != '"')
			find = find == 0 ? '\'' : 0;
		s++;
	}
	return (find);
}

int					find_pipe(char *s)
{
	if (!(s = ft_strrchr(s, '|')))
		return (0);
	while (*(++s))
	{
		if (*s != ' ' && *s != '\n')
			return (0);
	}
	return (1);
}

char				*find_quote(char *s, char find)
{
	int				bs_c;

	while (*s)
	{
		if (*s == '\\')
		{
			bs_c = 0;
			while (*(s) == '\\')
			{
				s++;
				bs_c++;
			}
			if (*s == '"' && bs_c % 2 == 0 && find != '\'')
				return (s);
			if (*s == '\'' && (bs_c % 2 == 0 || find == '\'') && find != '"')
				return (s);
		}
		else if ((*s == '"' && find != '\'') || (*s == '\'' && find != '"'))
			return (s);
		s++;
	}
	return (0);
}

char				**get_quote_list(char *s)
{
	char			**res;
	int				i;
	int				size;
	char			tmp;

	tmp = 0;
	i = 0;
	size = 100;
	if (!(res = (char**)ft_calloc(size + 1, 1)))
		exit(-1);
	while (*s)
	{
		if (i >= size - 1)
			res = ft_realloc(res, size * 2);
		s = find_quote(s, tmp);
		if (!s)
		{
			break ;
			i++;
		}
		tmp = tmp == 0 ? *s : 0;
		res[i++] = s++;
	}
	res = ft_realloc(res, i + 1);
	return (res);
}
