#include "pipex.h"
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
	char	*file;
	int		i;
    char    **args;
    char	*arg;
	char **path = git_path(a_env);
    args = ft_split(cmd, ' ');
	while (path[i] != NULL)
	{
        arg = ft_strjoin(path[i], "/");
		file = ft_strjoin(&arg[i], cmd);
		if (access(file, F_OK))
            execve(file, args, a_env);
		//free(file);
		i++;
	}
       printf("ok\n");
	return (file);
}

int main(int ac, char **av, char **env)
{
    int i = 0;
    char *arr= exec_cmd(av[2], env);
    while(arr[i])
    {
        printf("%c", arr[i]);
        i++;
    }
    // exec_cmd(av[2], env);
    return (0);
}