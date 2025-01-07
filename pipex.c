/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:54:45 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/07 20:43:25 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

char	*searcher(char **envp)
{
	while (*envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5))
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}
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
}

void	parent_execute(int *pip, char **argv, char **envp)
{
	char	**SecArg;
	char	**paths;
	char	*cmd;
	int		fd;

	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, 0);
	dup2(pip[1], 1);
	close(pip[0]);
	SecArg = ft_split(argv[2], ' ');
	paths = ft_split(searcher(envp), ':');
	while (*paths)
	{
		cmd = extract_path(*paths, SecArg[0]);
		if (cmd)
			break;
		paths++;
	}
	if (execve(cmd, SecArg, envp) == -1)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	child_execute(int *pip, char **argv, char **envp)
{
	char	**ThirArg;
	char	**paths;
	char	*cmd;
	int		fd;

	fd = open(argv[4], O_WRONLY | O_CREAT, 0777);
	dup2(pip[0], 0);
	dup2(fd, 1);
	close(pip[1]);
	ThirArg = ft_split(argv[3], ' ');
	paths = ft_split(searcher(envp), ':');
	while (*paths)
	{
		cmd = extract_path(*paths, ThirArg[0]);
		if (cmd)
			break;
		paths++;
	}
	if (execve(cmd, ThirArg, envp) == -1)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void ft_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

int main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		return (0);
	pipe(fd);
	pid = fork();
	if (pid > 0)
		parent_execute(fd, argv, envp);
	else if (pid == 0)
		child_execute(fd, argv, envp);
}
