/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksinistr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 17:40:07 by ksinistr          #+#    #+#             */
/*   Updated: 2020/10/24 17:40:38 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int					parse_command_line(t_cmdlist *cmdlist)
{
	t_pipe			*pipelst;

	while (cmdlist)
	{
		pipelst = cmdlist->pipe;
		if (pipelst->next)
			pipe_iterations(pipelst);
		else
			redirect_switch(pipelst->redirect);
		cmdlist = cmdlist->next;
	}
	return (1);
}
