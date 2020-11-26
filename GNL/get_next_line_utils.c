/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 16:29:20 by charodei          #+#    #+#             */
/*   Updated: 2020/10/07 13:04:46 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_listg			*ft_create_elemg(int fd, char *left, t_listg *prev)
{
	t_listg				*res;

	if (!(res = (t_listg *)malloc(sizeof(t_listg))))
		return (NULL);
	res->fd = fd;
	res->left = left;
	res->prev = prev;
	res->next = NULL;
	return (res);
}

char			*ft_strjoin_gnl(char *s1, char *s2)
{
	char		*result;
	size_t		i;
	size_t		j;

	if (!s1 && s2)
		return (ft_strdup((const char*)s2));
	if (s1 && !s2)
		return (s1);
	i = -1;
	if (!(result = (char *)malloc((ft_strlen(s1) +
		ft_strlen(s2) + 1) * (sizeof(char)))))
	{
		free(s1);
		return (NULL);
	}
	while (s1[++i])
		result[i] = s1[i];
	free(s1);
	j = -1;
	while (s2[++j])
		result[i + j] = s2[j];
	result[i + j] = '\0';
	return (result);
}
