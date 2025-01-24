/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:54:45 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/25 00:35:53 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"

void	ft_close(int *pip)
{
	close(pip[0]);
	close(pip[1]);
}

void	firstchild_exec(int *pip, char **argv, char **envp)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		print_if_error(2, argv[1]);
		ft_close(pip);
		exit(2);
	}
	dup2(fd, 0);
	close(fd);
	dup2(pip[1], 1);
	ft_close(pip);
	init_nd_execute(ft_split(argv[2], ' '), envp);
	exit(2);
}

void	secchild_exec(int *pip, char **argv, char **envp)
{
	int		fd;

	fd = open(argv[4], O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		print_if_error(126, argv[4]);
		ft_close(pip);
		exit(1);
	}
	dup2(pip[0], 0);
	dup2(fd, 1);
	close(fd);
	ft_close(pip);
	init_nd_execute(ft_split(argv[3], ' '), envp);
	exit(2);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		status;
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		return (1);
	if (pipe(fd) == -1)
		exit(1);
	pid1 = fork();
	if (pid1 == -1)
		exit(1);
	if (pid1 == 0)
		firstchild_exec(fd, argv, envp);
	pid2 = fork();
	if (pid2 == -1)
		exit(1);
	if (pid2 == 0)
		secchild_exec(fd, argv, envp);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	ft_close(fd);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
