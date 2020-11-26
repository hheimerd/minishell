/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hheimerd <hheimerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:48:11 by hheimerd          #+#    #+#             */
/*   Updated: 2020/10/28 16:15:37 by ksinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_exist_env(char *key)
{
	int		i;

	i = 0;
	while (g_env[i])
	{
		if (ft_strncmp(g_env[i], key, ft_strlen(key)) == 0 && \
			(g_env[i][ft_strlen(key)] == '=' || \
			g_env[i][ft_strlen(key)] == '\0'))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

static char	*get_env_value_by_key(char *key)
{
	int		i;
	char	**g_env_arr;
	char	*ret;

	i = 0;
	while (g_env[i])
	{
		if (ft_strncmp(g_env[i], key, ft_strlen(key)) == 0 && \
			(g_env[i][ft_strlen(key)] == '=' || \
			g_env[i][ft_strlen(key)] == '\0'))
		{
			g_env_arr = split_arg_to_arr(g_env[i]);
			ret = ft_strdup(g_env_arr[2]);
			del_arr(&g_env_arr);
			return (ret);
		}
		i++;
	}
	return (NULL);
}

static void	copy_env_value(char *source_key, char *dest_key)
{
	char	*source_value;
	char	*arg_tmp;
	char	*arg_to_set;

	source_value = get_env_value_by_key(source_key);
	if (source_value)
	{
		if (!(arg_tmp = ft_strjoin(dest_key, "=")))
			exit(-1);
		if (!(arg_to_set = ft_strjoin(arg_tmp, source_value)))
			exit(-1);
		set_or_add_value(arg_to_set);
		free(arg_tmp);
		arg_tmp = NULL;
		free(arg_to_set);
		arg_to_set = NULL;
		free(source_value);
		source_value = NULL;
	}
}

static int	change_pwd_env(void)
{
	char	**export_args;
	char	*current_path;
	char	buf[1024];

	if (is_exist_env("PWD"))
	{
		copy_env_value("PWD", "OLDPWD");
		if (!(export_args = ft_calloc(2, sizeof(char *))))
			exit(-1);
		if (!(current_path = getcwd(buf, sizeof(buf))))
			return (0);
		export_args[0] = ft_strjoin("PWD=", current_path);
		ft_export(export_args);
		del_arr(&export_args);
	}
	return (1);
}

int			cd(char **args)
{
	char	*pth;

	if (*args && *args[0] == '\0')
		return (0);
	if (!args[0])
	{
		if (!*(pth = ft_getenv("HOME")))
		{
			put_error("minishell", "cd", NULL, "HOME not set");
			return (1);
		}
	}
	else
		pth = args[0];
	if (chdir(pth) != 0)
	{
		put_error("minishell", "cd", pth, NULL);
		return (1);
	}
	if (!change_pwd_env())
		return (1);
	return (0);
}
