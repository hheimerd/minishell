/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 15:46:50 by hheimerd          #+#    #+#             */
/*   Updated: 2020/10/25 17:12:23 by hheimerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 25
# endif

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct		s_listg
{
	int				fd;
	char			*left;
	struct s_listg	*prev;
	struct s_listg	*next;
}					t_listg;

t_listg				*ft_create_elemg(int fd, char *left, t_listg *prev);
char				*ft_strjoin_gnl(char *s1, char *s2);
int					ft_check_line(char **line, char **res, int mode);
int					ft_find_elem(int fd, t_listg **start, t_listg **res,
	char **line);
int					gnl(t_listg *node, char *buf, char **line);
int					clear_node(int res_code, t_listg **start, t_listg *node);
int					get_next_line(int fd, char **line);
#endif
