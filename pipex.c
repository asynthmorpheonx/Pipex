/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:54:45 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/24 23:45:55 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"

void	print_if_error(int the_error, char *probleme)
{
	if (the_error == 2)
		ft_putendl_fd("No such file or directory: ", probleme, 2);
	else if (the_error == 127)
		ft_putendl_fd("command not found: ", probleme, 2);
	else if (the_error == 126)
		ft_putendl_fd("permission denied: ", probleme, 2);	
}

int	check_access(char **path, char *cmd)
{
	char	*str;

	if (cmd[0] == '/' || cmd[0] == '~' || cmd[0] == '.')
	{
		if (access(cmd, F_OK | X_OK) == 0)
				return (0);
		else if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == -1)
			return (126);		
	}
	if (!path)
		return (127);
	str = extract_path(path, cmd);
	if (str)
	{
		if (access(str, X_OK) == 0)
			return (free(str), 0);
		return (free(str), 126);
	}
	return (free(str), 127);
}

char	*extract_path(char **path, char *cmd)
{
	char	*temp;
	char	*str;
	int		i;

	i = 0;
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	if (!path)
		return (NULL);
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		str = ft_strjoin(temp, cmd);
		if (access(str, X_OK | F_OK) == 0)
			return (free(temp), str);
		free(temp);
		free(str);
		i++;
	}
	return (NULL);
}

void	handler(char **path, char **arg)
{
	int		access_status;

	access_status = check_access(path, arg[0]);
	print_if_error(access_status, arg[0]);
	ft_free(path, arg);
	exit(access_status);
}

void	init_nd_execute(char **arg, char **envp)
{
	char **path;
	char *cmd;

	path = NULL;
	cmd = NULL;
	if (!arg[0])
	{
		print_if_error(127, " ");
		exit(127);
	}
	if (envp)
		path = ft_split(searcher(envp), ':');
	cmd = extract_path(path, arg[0]);
	if (!cmd)
		handler(path, arg);
	execve(cmd, arg, envp);
	ft_free(arg, path);
	free(cmd);
	exit(2);
}
void	firstChild_exec(int *pip, char **argv, char **envp)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		print_if_error(2, argv[1]);
		close(pip[0]);
		close(pip[1]);
		exit(2);
	}
	dup2(fd, 0);
	close(fd);
	dup2(pip[1], 1);
	close(pip[1]);
	close(pip[0]);
	init_nd_execute(ft_split(argv[2], ' '), envp);
	exit(2);
}

void	secChild_exec(int *pip, char **argv, char **envp)
{
	int		fd;

	fd = open(argv[4], O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		print_if_error(126, argv[4]);
		close(pip[0]);
		close(pip[1]);
		exit(1);
	}
	dup2(pip[0], 0);
	dup2(fd, 1);
	close(fd);
	close(pip[0]);
	close(pip[1]);
	init_nd_execute(ft_split(argv[3], ' '), envp);
	exit(2);
}

int main(int argc, char **argv, char **envp)
{
	int     fd[2];
	int     status;
	pid_t   pid1, pid2;

	if (argc != 5)
		return (1);
	if (pipe(fd) == -1)
		exit(1);
	pid1 = fork();
	if (pid1 == -1)
		exit(1);
	if (pid1 == 0)
		firstChild_exec(fd, argv, envp);
	pid2 = fork();
	if (pid2 == -1)
		exit(1);
	if (pid2 == 0)
		secChild_exec(fd, argv, envp);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	close(fd[0]);
	close(fd[1]);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
