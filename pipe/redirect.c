/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 14:09:33 by ksinistr          #+#    #+#             */
/*   Updated: 2020/10/28 18:34:17 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int				file_open(t_redirect *redirectlst, int oflag)
{
	int			fd;

	if (redirectlst->next->cmd[0][0] == '\0')
	{
		put_error("minishell", NULL, NULL,
			"syntax error near unexpected token `newline'");
		exit(EXIT_FAILURE);
	}
	if ((fd = open(redirectlst->next->cmd[0], oflag, 0666)) < 0)
	{
		put_error("minishell", redirectlst->next->cmd[0], NULL, NULL);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void			swap_fd(t_redirect *redirectlst)
{
	int			fd;

	if (redirectlst->redirect == 'a')
	{
		fd = file_open(redirectlst, O_CREAT | O_WRONLY | O_APPEND);
		if (dup2(fd, CLOSE_STDOUT) == -1)
			put_error("minishell", "dup2", NULL, NULL);
		close(fd);
	}
	else if (redirectlst->redirect == '>')
	{
		fd = file_open(redirectlst, O_CREAT | O_TRUNC | O_WRONLY);
		if (dup2(fd, CLOSE_STDOUT) == -1)
			put_error("minishell", "dup2", NULL, NULL);
		close(fd);
	}
	else if (redirectlst->redirect == '<')
	{
		fd = file_open(redirectlst, O_RDONLY);
		if (dup2(fd, CLOSE_STDIN) == -1)
			put_error("minishell", "dup2", NULL, NULL);
		close(fd);
	}
}

void			mov_args_to_first_elem(char ***first_cmd, char **current_cmd)
{
	int			first_cmd_len;
	int			current_cmd_len;
	int			i;
	int			j;

	first_cmd_len = array_length(*first_cmd);
	current_cmd_len = array_length(current_cmd);
	*first_cmd = ft_realloc(*first_cmd, \
		first_cmd_len + 1 + current_cmd_len - 1);
	i = 1;
	j = first_cmd_len;
	while (i < current_cmd_len)
	{
		(*first_cmd)[j] = current_cmd[i];
		current_cmd[i] = NULL;
		j++;
		i++;
	}
}

void			redirectlst_format(t_redirect *redirectlst)
{
	int			current_cmd_len;
	t_redirect	*redirectlst_tmp;

	redirectlst_tmp = redirectlst->next;
	while (redirectlst_tmp)
	{
		current_cmd_len = array_length(redirectlst_tmp->cmd);
		if (current_cmd_len > 1)
			mov_args_to_first_elem(&redirectlst->cmd, redirectlst_tmp->cmd);
		redirectlst_tmp = redirectlst_tmp->next;
	}
}

void			redirect_switch(t_redirect *redirectlst)
{
	pid_t		child;
	t_redirect	*redirectlst_tmp;

	redirectlst_format(redirectlst);
	if (redirectlst->redirect == 'a' || redirectlst->redirect == '>' || \
			redirectlst->redirect == '<')
	{
		redirectlst_tmp = redirectlst;
		if ((child = fork()) < 0)
			put_error("minishell", "fork", NULL, NULL);
		if (child == 0)
		{
			while (redirectlst_tmp->next)
			{
				swap_fd(redirectlst_tmp);
				redirectlst_tmp = redirectlst_tmp->next;
			}
			parse_command(redirectlst->cmd, redirectlst->next);
			exit(EXIT_SUCCESS);
		}
		else
			waitpid(child, 0, 0);
	}
	else
		parse_command(redirectlst->cmd, redirectlst->next);
}
