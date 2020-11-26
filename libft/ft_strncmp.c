/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 20:00:51 by hheimerd          #+#    #+#             */
/*   Updated: 2020/10/25 15:38:48 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 && --n)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s2++;
		s1++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int		ft_strncmp_ci(const char *s1, const char *s2, size_t n)
{
	while (*s1 && --n)
	{
		if (ft_tolower(*s1) != ft_tolower(*s2))
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s2++;
		s1++;
	}
	if (ft_tolower(*s1) == ft_tolower(*s2))
		return (0);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
