/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 16:16:16 by hheimerd          #+#    #+#             */
/*   Updated: 2020/10/25 14:16:16 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmdlist			*add_redirect(t_cmdlist *start, char **cmd,
															char redirect)
{
	t_pipe			*pipe_tmp;
	t_redirect		*redirect_tmp;
	t_cmdlist		*cmd_tmp;

	if (!(cmd_tmp = start))
		return (create_cmdlist(create_pipe(create_redirect(cmd, redirect))));
	while (cmd_tmp->next)
		cmd_tmp = cmd_tmp->next;
	pipe_tmp = cmd_tmp->pipe;
	while (pipe_tmp->next)
		pipe_tmp = pipe_tmp->next;
	redirect_tmp = pipe_tmp->redirect;
	while (redirect_tmp->next)
		redirect_tmp = redirect_tmp->next;
	redirect_tmp->next = create_redirect(cmd, redirect);
	return (start);
}

t_cmdlist			*add_pipe(t_cmdlist *start, char **cmd,
														char redirect)
{
	t_cmdlist		*cmd_tmp;
	t_pipe			*pipe_tmp;

	if (!start)
		return (create_cmdlist(create_pipe(create_redirect(cmd, redirect))));
	cmd_tmp = start;
	while (cmd_tmp->next)
		cmd_tmp = cmd_tmp->next;
	pipe_tmp = cmd_tmp->pipe;
	while (pipe_tmp->next)
		pipe_tmp = pipe_tmp->next;
	pipe_tmp->next = create_pipe(create_redirect(cmd, redirect));
	return (start);
}

t_cmdlist			*add_elem(char *state, t_cmdlist *start,
									char **args, char redirect)
{
	t_cmdlist		*tmp;

	if (*state == '|' || !start || !*state)
	{
		*state = redirect;
		return (add_pipe(start, args, redirect));
	}
	tmp = start;
	if (*state == ';')
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = add_pipe(NULL, args, redirect);
	}
	else if (*state == '<' || *state == '>' || *state == 'a')
		add_redirect(start, args, redirect);
	else
		add_redirect(start, args, redirect);
	*state = redirect;
	return (start);
}
