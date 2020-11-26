/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:16:25 by hheimerd          #+#    #+#             */
/*   Updated: 2020/10/28 18:15:22 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void				sigint_handler(int z)
{
	(void)(z);
	if (g_pid == 0)
	{
		g_ret = 1;
		ft_putstr_fd(RED "\nminishell>" RES, 1);
	}
}

void				sigbreak_handler(int z)
{
	(void)(z);
}
