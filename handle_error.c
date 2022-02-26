/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:00:30 by yismaili          #+#    #+#             */
/*   Updated: 2022/02/26 21:03:35 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**git_path(char **a_env)
{
	int		i;
	char	**path;

	i = 0;
	while (a_env[i])
	{
		if (ft_strncmp(a_env[i], "PATH=", 5) == 0)
		{
			path = ft_split(a_env[i] + 5, ':');
			return (path);
		}
		i++;
	}
	return (0);
}

void	ft_die(char *s)
{
	perror(s);
	exit(1);
}

char	*exec_cmd(char *cmd, char **a_env)
{
	char	*bin;
	int		i;
	char	**args;
	char	*arg;
	char	*temp;
	char	**path;

	i = 0;
	path = git_path(a_env);
	args = ft_split(cmd, ' ');
	bin = ft_strdup(args[0]);
	while (path[i] != NULL)
	{
		arg = ft_strjoin(path[i], "/");
		temp = ft_strjoin(arg, bin);
		free(arg);
		free(args[0]);
		args[0] = temp;
		if (access(args[0], F_OK) == 0)
		{
			execve(args[0], args, a_env);
		}
		i++;
	}
	return (NULL);
}
