/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:54:45 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/12 00:24:44 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*extract_path(char *path, char *cmd)
{
	char	*temp;
	char	*str;

	temp = ft_strjoin(path, "/");
	str = ft_strjoin(temp, cmd);
	free(temp);
	if (access(str, F_OK) == 0)
		return (str);	
	else if (access(str, F_OK) == -1)
		return (free(str), NULL);
	return (NULL);
}

void	firstChild_exec(int *pip, char **argv, char **envp)
{
    char	**SecArg;
    char	**paths;
    char	*cmd;
    int		fd;
    int		i;

	i = 0;
    fd = open(argv[1], O_RDONLY, 0777);
    if (fd == -1)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    dup2(fd, 0);
    dup2(pip[1], 1);
    close(pip[0]);
    SecArg = ft_split(argv[2], ' ');
    paths = ft_split(searcher(envp), ':');
    while (paths[i])
    {
        cmd = extract_path(paths[i], SecArg[0]);
        if (cmd)
            break;
        i++;
    }
	if (!cmd)
	{
		perror("command not found");
		ft_free(SecArg, paths);
		exit(EXIT_FAILURE);
	}
	ft_free(paths, NULL);
    if (execve(cmd, SecArg, envp) == -1)
    {
        perror("execve error");
		free(cmd);
        exit(EXIT_FAILURE);
    }
    close(fd);
}

void	secChild_exec(int *pip, char **argv, char **envp)
{
	char	**ThirArg;
	char	**paths;
	char	*cmd;
	int		fd;
	int		i;

	i = 0;
	fd = open(argv[4], O_WRONLY | O_CREAT, 0777);
	if (fd == -1)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
	dup2(pip[0], 0);
	dup2(fd, 1);
	close(pip[1]);
	ThirArg = ft_split(argv[3], ' ');
	paths = ft_split(searcher(envp), ':');
	while (paths[i])
	{
		cmd = extract_path(paths[i], ThirArg[0]);
		if (cmd)
			break;
		i++;
	}
	if (!cmd)
	{
		perror("command not found"),
		ft_free(ThirArg, paths);
		exit(EXIT_FAILURE);
	}
	ft_free(paths, NULL);
	if (execve(cmd, ThirArg, envp) == -1)
	{
		perror("error");
		free(cmd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

int main(int argc, char **argv, char **envp)
{
    int     fd[2];
    int     status;
    pid_t   pid1, pid2;

    if (argc != 5)
        return (1);
    if (pipe(fd) == -1)
    {
        perror("pipe error");
        exit(EXIT_FAILURE);
    }
    pid1 = fork();
    if (pid1 == 0)
        firstChild_exec(fd, argv, envp);
	pid2 = fork();
    if (pid2 == -1 || pid1 == -1)
    {
        perror("fork error");
        exit(EXIT_FAILURE);
    }
    if (pid2 == 0)
        secChild_exec(fd, argv, envp);
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		return (EXIT_SUCCESS);
    return (1);
}
