/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_open_exece.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:47:59 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/31 18:49:17 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"

void	close_node(t_utils *container)
{
	close(container->pipe[0]);
	close(container->pipe[1]);
}

void	safer_dup(t_utils *container)
{
	dup2(container->in_file, 0);
	close(container->in_file);
	dup2(container->out_file, 1);
	close(container->out_file);
}

int	check_file(char *file)
{
	if (access(file, F_OK) == -1)
		return (2);
	else if (access(file, F_OK) == 0)
		return (126);
	return (0);
}

void	safer_open(t_utils *container, int i)
{
	if (i == 1)
	{
		container->in_file = open(container->av[1], O_RDONLY);
		container->out_file = container->pipe[1];
		close(container->pipe[0]);
		if (container->in_file == -1)
			print_if_error(check_file(container->av[1]), container->av[1]);
	}
	else
	{
		container->in_file = container->pipe[0];
		container->out_file = open(container->av[4],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(container->pipe[1]);
		if (container->out_file == -1)
			print_if_error(check_file(container->av[4]), container->av[4]);
	}
	if (container->in_file == -1 || container->out_file == -1)
	{
		close_node(container);
		exit(1);
	}
	safer_dup(container);
}

void	child_exec(t_utils *container, int i)
{
	char	**arg;
	char	**envp;

	arg = container->av;
	envp = container->envp;
	safer_open(container, i);
	if (1 == i)
	{
		free(container);
		init_nd_execute(ft_split(arg[2], ' '), envp);
	}
	else if (2 == i)
	{
		free(container);
		init_nd_execute(ft_split(arg[3], ' '), envp);
	}
	free(container);
	exit(2);
}
