/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 14:27:20 by hheimerd          #+#    #+#             */
/*   Updated: 2020/10/28 18:46:15 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int					check_unexpected(char *s)
{
	while (*s)
	{
		if (*s == ';' || *s == '|')
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			if ((*(s + 1) == ';' && *s == ';') ||
				(*(s + 1) == '|' && *s == '|'))
				write(2, s, 2);
			else
				write(2, s, 1);
			write(2, "'", 1);
			ft_putstr_fd(RED "\nminishell>" RES, 1);
			return (1);
		}
		else if (*s == ' ')
			s++;
		else
			return (0);
	}
	return (0);
}

void				remove_struct(t_cmdlist *start)
{
	t_cmdlist		*cmd_tmp;
	t_pipe			*pipe_tmp;
	t_redirect		*redirect_tmp;

	while (start)
	{
		pipe_tmp = start->pipe;
		while (pipe_tmp)
		{
			redirect_tmp = pipe_tmp->redirect;
			while (redirect_tmp)
			{
				del_arr(&redirect_tmp->cmd);
				redirect_tmp = redirect_tmp->next;
				free(pipe_tmp->redirect);
				pipe_tmp->redirect = redirect_tmp;
			}
			pipe_tmp = pipe_tmp->next;
			free(start->pipe);
			start->pipe = pipe_tmp;
		}
		cmd_tmp = start->next;
		free(start);
		start = cmd_tmp;
	}
}

t_redirect			*create_redirect(char **cmd, char redirect)
{
	t_redirect		*res;

	if (!(res = (t_redirect*)malloc(sizeof(t_redirect))))
		exit(-1);
	res->next = NULL;
	res->cmd = cmd;
	res->redirect = redirect;
	return (res);
}

t_pipe				*create_pipe(t_redirect *redirect)
{
	t_pipe			*res;

	if (!(res = (t_pipe*)malloc(sizeof(t_pipe))))
		exit(-1);
	res->next = NULL;
	res->redirect = redirect;
	return (res);
}

t_cmdlist			*create_cmdlist(t_pipe *pipe)
{
	t_cmdlist		*res;

	if (!(res = (t_cmdlist*)malloc(sizeof(t_cmdlist))))
		exit(-1);
	res->next = NULL;
	res->pipe = pipe;
	return (res);
}
