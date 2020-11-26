/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 16:25:11 by ksinistr          #+#    #+#             */
/*   Updated: 2020/10/28 16:22:46 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			handle_null_line(char *line_pointer)
{
	if (!*line_pointer)
	{
		free(line_pointer);
		ft_putstr_fd(RED "minishell>" RES, 1);
		return (1);
	}
	return (0);
}
