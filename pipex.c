/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:33:55 by yismaili          #+#    #+#             */
/*   Updated: 2022/02/19 12:34:02 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_die(char *s)
{
    perror(s);
    exit(1);
}

char    **git_path(char **a_env)
{
	int	i;
	char **path;

	i = 0;
	while (a_env[i])
	{
		if (ft_strncmp(a_env[i], "PATH=", 5)== 0)
		{
			path = ft_split(a_env[i] + 5,':');
			return(path);
		}
		i++;
	}
	return (0);
}

char	*exec_cmd(char *cmd, char **a_env)
{
		char	*bin;
	int		i = 0;
    char    **args;
    char	*arg;
	char *temp;
	char **path = git_path(a_env);
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
void     child_process(int f1, int end[2], char **av, char **a_env)
{
        close(end[0]);
        dup2(f1, STDIN_FILENO);
        dup2(end[1], STDOUT_FILENO);
		exec_cmd(av[2], a_env);
         if(!&exec_cmd)
            ft_die("command not found");
}

void     parent_process(int f2, int end[2], char **av, char **a_env)
{
        close(end[1]);
        dup2(end[0], STDIN_FILENO);
        dup2(f2, STDOUT_FILENO);
		exec_cmd(av[3], a_env);
         printf("pareint\n");
        if(!&exec_cmd)
            ft_die("command not found");
}

void ft_pipex(int f1, int f2, char **av, char **a_env)
{
    int     end[2];
    pid_t   pid = 0;

    pipe(end);
    pid = fork();
	if (pid < 0)
		ft_die("fork");
    if (pid == 0)
    {
        child_process(f1, end, av, a_env);
    }
    else
    {
        wait(0);
        parent_process(f2, end, av, a_env);
    }
}

int main(int argc, char *argv[], char **a_env)
{
    int     infile;
    int     outfile;

    if (argc < 5)
    {
        ft_die("Arguments error\n");
    }
    infile = open(argv[1], O_RDONLY);
    outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0664); 
    ft_pipex(infile, outfile, argv, a_env);

}