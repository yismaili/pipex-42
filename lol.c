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
#include <string.h>
char	*exec_cmd(char *cmd, char **a_env)
{
	char	*bin;
	int		i;
    char    **args;
    char	*arg;
	char *temp;
	char **path = git_path(a_env);
    args = ft_split(cmd, ' ');
	bin = strdup(args[0]);
	while (path[i] != NULL)
	{
        arg = ft_strjoin(path[i], "/");
		temp = ft_strjoin(arg, bin);
		free(arg);
		free(args[0]);
		args[0] = temp;
		//printf("%s\n", args[0]);
		if (access(args[0], F_OK) == 0)
		{
			execve(args[0], args, a_env);
            //int err = execve(args[0], args, a_env);
			//printf("%d\n", err);
		}
		i++;
	}
	return (NULL);
}

int main(int ac, char **av, char **env)
{
    int i = 0;
    char *arr= exec_cmd(av[2], env);
    /*while(arr[i])
    {
        printf("%c", arr[i]);
        i++;
    }*/
    // exec_cmd(av[2], env);
    return (0);
}