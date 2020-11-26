/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 14:20:16 by hheimerd          #+#    #+#             */
/*   Updated: 2020/10/28 16:22:46 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			put_error(char *prog, char *cmd, char *arg, char *error_s)
{
	ft_putstr_fd(prog, 2);
	write(2, ": ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		write(2, ": ", 2);
	}
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		write(2, ": ", 2);
	}
	if (error_s)
		ft_putstr_fd(error_s, 2);
	else if (errno)
		ft_putstr_fd(strerror(errno), 2);
	errno = 0;
	write(2, "\n", 1);
	return (-1);
}
