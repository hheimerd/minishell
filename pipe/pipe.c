/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 14:13:48 by ksinistr          #+#    #+#             */
/*   Updated: 2020/10/25 17:12:23 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pipesfds		*init_pipesfds(int number_of_pipes)
{
	t_pipesfds	*pfds;
	int			i;
	int			*pfds_tmp;

	if (!(pfds_tmp = ft_calloc(2, sizeof(int))))
		exit(-1);
	if (!(pfds = ft_calloc(number_of_pipes, sizeof(t_pipesfds))))
		exit(-1);
	i = 0;
	while (i < number_of_pipes)
	{
		if (pipe(pfds_tmp) == -1)
			put_error("minishell", "pipe", NULL, NULL);
		pfds[i].in = pfds_tmp[0];
		pfds[i].out = pfds_tmp[1];
		i++;
	}
	free(pfds_tmp);
	return (pfds);
}

void			close_all_pipes(t_pipesfds *pfds, int pipelst_length)
{
	int			i;

	i = 0;
	while (i < pipelst_length - 1)
	{
		close(pfds[i].in);
		close(pfds[i].out);
		i++;
	}
}

int				ft_pipelst_size(t_pipe *pipelst)
{
	int			count;

	count = 0;
	while (pipelst)
	{
		pipelst = pipelst->next;
		count++;
	}
	return (count);
}

void			pipe_child(int i, t_pipesfds *pfds, int pipelst_length, \
		t_redirect *redirectlst)
{
	if (i != 0)
	{
		if (dup2(pfds[i - 1].in, 0) == -1)
			put_error("minishell", "dup2", NULL, NULL);
	}
	if (i != (pipelst_length - 1))
	{
		if (dup2(pfds[i].out, 1) == -1)
			put_error("minishell", "dup2", NULL, NULL);
	}
	close_all_pipes(pfds, pipelst_length);
	redirect_switch(redirectlst);
	exit(EXIT_SUCCESS);
}

void			pipe_iterations(t_pipe *pipelst)
{
	t_pipesfds	*pfds;
	int			i;
	int			pipelst_length;
	pid_t		child;

	pipelst_length = ft_pipelst_size(pipelst);
	pfds = init_pipesfds(pipelst_length - 1);
	i = 0;
	while (pipelst)
	{
		if ((child = fork()) < 0)
			put_error("minishell", "fork", NULL, NULL);
		if (child == 0)
		{
			pipe_child(i, pfds, pipelst_length, pipelst->redirect);
		}
		pipelst = pipelst->next;
		i++;
	}
	close_all_pipes(pfds, pipelst_length);
	free(pfds);
	while (waitpid(-1, 0, 0) != -1)
		;
}
