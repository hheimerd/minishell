/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 15:46:03 by hheimerd          #+#    #+#             */
/*   Updated: 2020/11/26 13:59:35 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int			parse_delimetr(t_split_vars *sv, char **s, int *res_c, \
		char *state)
{
	int				ret;

	if (sv->tmp && *(sv->tmp) && **s)
		space_split(sv, res_c, s);
	if (!*(sv->res_arr) && *state)
		if (!(*(sv->res_arr) = ft_strdup("")))
			exit(-1);
	*res_c = 0;
	if (**s == '>' && (*s)[1] == '>')
	{
		ret = 2;
		sv->cmdlist = add_elem(state, sv->cmdlist, sv->res_arr, 'a');
	}
	else
	{
		ret = 1;
		sv->cmdlist = add_elem(state, sv->cmdlist, sv->res_arr, **s);
	}
	if (!(sv->res_arr = (char**)ft_calloc(2, sizeof(char*))))
		exit(-1);
	return (ret);
}

void				parse_variable(t_split_vars *sv, char **s)
{
	sv->tmp = append_c((sv->tmp), '\a');
	(*s)++;
	if (**s == '?')
		sv->tmp = append_c((sv->tmp), *((*s)++));
	else
	{
		while ((ft_isalnum(**s) || **s == '_') && **s)
		{
			sv->tmp = append_c(sv->tmp, **s);
			(*s)++;
		}
	}
	sv->tmp = append_c(sv->tmp, '\a');
}

int					handle_quotes(int *i, char *s, t_split_vars *sv, \
		char *tmblr)
{
	int				j;

	j = 0;
	if (s == sv->quote_list[*i] && \
		(ft_strchr(" \n;|<>", *(s - 2)) || *(s - 2) == 0) &&
		(ft_strchr(" \n;|<>", *(s + 1)) || *(s + 1) == 0))
	{
		(*i)++;
		if (!((sv->res_arr)[(sv->res_c)++] = ft_strdup("")))
			exit(-1);
		if (!((sv->res_arr) = ft_realloc((sv->res_arr), sv->res_c + 2)))
			exit(-1);
		while (s[j++])
			if (s[j] != ' ' && s[j] != '\n' && s[j] != '\0')
				break ;
		return (j);
	}
	else
		*tmblr = *tmblr == 1 ? 0 : 1;
	return (0);
}

void				parse_input(char *s, t_split_vars *sv, char tmblr, \
		char state)
{
	int				i;

	i = 0;
	sv->res_c = 0;
	while (*s)
	{
		if (s == sv->quote_list[i] && ++i && s++)
			s += handle_quotes(&i, s, sv, &tmblr);
		else if (*s == '\\' && !tmblr && s++)
			sv->tmp = append_c(sv->tmp, *(s++));
		else if ((*s == ' ' || *s == '\n') && !tmblr)
			space_split(sv, &(sv->res_c), &s);
		else if (*s == '$' && (ft_isalnum(s[1]) || s[1] == '_' || s[1] == '?') \
				&& ((tmblr && sv->quote_list[i][0] == '"') || !tmblr))
			parse_variable(sv, &s);
		else if (!tmblr && ft_strchr("<>;|", *s))
			s += parse_delimetr(sv, &s, &(sv->res_c), &state);
		else
			sv->tmp = append_c(sv->tmp, *(s++));
		if (!*s && sv->tmp && *(sv->tmp))
			if (!((sv->res_arr)[sv->res_c] = ft_strdup(sv->tmp)))
				exit(-1);
	}
	parse_delimetr(sv, &s, &(sv->res_c), &state);
}

t_cmdlist			*split_line(char *s)
{
	t_split_vars	split_vars;

	split_vars.cmdlist = 0;
	split_vars.quote_list = get_quote_list(s);
	if (!(split_vars.tmp = (char*)ft_calloc(1, 1)) ||
		!(split_vars.res_arr = (char**)ft_calloc(2, sizeof(char*))))
		exit(0);
	parse_input(s, &split_vars, 0, 0);
	if (split_vars.res_arr)
		del_arr(&(split_vars.res_arr));
	if (split_vars.tmp)
		free(split_vars.tmp);
	free(split_vars.quote_list);
	return (split_vars.cmdlist);
}
