/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:53:38 by ksinistr          #+#    #+#             */
/*   Updated: 2020/10/28 15:59:35 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		pwd(void)
{
	char	buf[1024];
	char	*path;

	if (!(path = getcwd(buf, sizeof(buf))))
		return (1);
	ft_putstr_fd(path, 1);
	write(1, "\n", 1);
	return (0);
}
