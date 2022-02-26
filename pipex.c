/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:33:55 by yismaili          #+#    #+#             */
/*   Updated: 2022/02/26 20:23:05 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int f1, int end[2], char **av, char **a_env)
{
	close(end[0]);
	dup2(f1, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	exec_cmd(av[2], a_env);
	if (!&exec_cmd)
		ft_die("command not found");
}

void	parent_process(int f2, int end[2], char **av, char **a_env)
{
	close(end[1]);
	dup2(end[0], STDIN_FILENO);
	dup2(f2, STDOUT_FILENO);
	exec_cmd(av[3], a_env);
	printf("pareint\n");
	if (!&exec_cmd)
		ft_die("command not found");
}

void	ft_pipex(int f1, int f2, char **av, char **a_env)
{
	int		end[2];
	pid_t	pid;

	pipe(end);
	pid = fork();
	if (pid < 0)
		ft_die("fork");
	if (pid == 0)
		child_process(f1, end, av, a_env);
	else
	{
		wait(0);
		parent_process(f2, end, av, a_env);
	}
}

int	main(int argc, char *argv[], char **a_env)
{
	int	infile;
	int	outfile;

	if (argc < 5)
		ft_die("Arguments error\n");
	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0664);
	ft_pipex(infile, outfile, argv, a_env);
}
