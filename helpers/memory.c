/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 15:37:08 by hheimerd          #+#    #+#             */
/*   Updated: 2020/10/28 14:08:26 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		**array_concat(char **arr1, char **arr2)
{
	int		len1;
	int		len2;
	char	**res;

	len1 = array_length(arr1);
	len2 = array_length(arr2);
	if (!(res = (char**)ft_calloc(sizeof(char**), len1 + len2 + 1)))
		return (NULL);
	while (arr1 && *arr1)
		*(res++) = *(arr1++);
	while (arr2 && *arr2)
		*(res++) = *(arr2++);
	return (res - len1 - len2);
}

char		*append_c(char *s, char c)
{
	char	*res;
	size_t	len;

	if (!s)
	{
		res = (char*)ft_calloc(2, sizeof(char));
		res[0] = c;
		return (res);
	}
	len = ft_strlen(s);
	if (!(res = ft_calloc(len + 2, sizeof(char))))
		exit(-1);
	res[len] = c;
	while (len-- > 0)
		res[len] = s[len];
	if (s)
		free(s);
	return (res);
}

char		**ft_realloc(char **src, int size)
{
	char	**res;
	int		i;

	i = 0;
	if (!src)
		return (ft_calloc(size, sizeof(char*)));
	if (!(res = ft_calloc(size, sizeof(char*))))
		return (0);
	while (i < size && src[i])
	{
		res[i] = src[i];
		i++;
	}
	free(src);
	return (res);
}
