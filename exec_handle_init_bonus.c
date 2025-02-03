/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handle_init_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:58:59 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/31 18:43:19 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils_bonus.h"

void	open_a_file(t_box *container, char **av, int i)
{
	if (i == 0)
	{
		container->in_file = open(av[1], O_RDONLY);
		if (container->in_file == -1)
		{
			print_if_error(2, av[1]);
			free_t_box(container);
			exit(2);
		}
	}
	else if (i == container->pipe_count)
	{
		if (container->is_there_heredoc)
			container->out_file = open(av[i + 3],
					O_CREAT | O_APPEND | O_WRONLY, 0644);
		else
			container->out_file = open(av[i + 3],
					O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (container->out_file == -1)
		{
			print_if_error(126, av[i + 3]);
			free_t_box(container);
			exit(1);
		}
	}
}

void	child_execute(t_box *container, char **av, int i, char **envp)
{
	i += container->is_there_heredoc;
	open_a_file(container, av, i);
	if (i == 0)
	{
		dup2(container->in_file, 0);
		dup2(container->pipes[i][1], 1);
		close(container->in_file);
		close(container->pipes[i][1]);
	}
	else if (i == container->pipe_count)
	{
		dup2(container->out_file, 1);
		dup2(container->pipes[i - 1][0], 0);
		close(container->out_file);
		close(container->pipes[i - 1][0]);
	}
	else
	{
		dup2(container->pipes[i - 1][0], 0);
		dup2(container->pipes[i][1], 1);
		close(container->pipes[i - 1][0]);
		close(container->pipes[i][1]);
	}
	free_t_box(container);
	init_nd_execute(ft_split(av[i + 2], ' '), envp);
}

t_box	*init_t_box(int argc, int heredoc)
{
	t_box	*container;

	container = malloc(sizeof(t_box));
	if (!container)
	{
		ft_putendl_fd("error :", "malloc failed while allocating", 2);
		exit(1);
	}
	container->is_there_heredoc = heredoc;
	container->cmd_count = argc - 3 - container->is_there_heredoc;
	container->pipe_count = argc - 4 ;
	container->pipes = malloc(sizeof(int *) * container->pipe_count);
	container->pids = malloc(sizeof(pid_t) * container->cmd_count);
	if (!container->pipes || !container->pids)
	{
		ft_putendl_fd("error :", "malloc failed while allocating", 2);
		exit(1);
	}
	make_pipes(container);
	return (container);
}

void	wait_all_childs(t_box *container, int *status)
{
	int	i;

	i = 0;
	while (i < container->cmd_count)
	{
		waitpid(container->pids[i], status, 0);
		i++;
	}
}

void	forking_for_executing(t_box *container, char **av, char **envp)
{
	int	i;

	i = 0;
	while (i < container->cmd_count)
	{
		container->pids[i] = fork();
		if (container->pids[i] == -1)
		{
			free_t_box(container);
			exit (1);
		}
		else if (container->pids[i] == 0)
			child_execute(container, av, i, envp);
		if (i > 0)
			close(container->pipes[i - 1][0]);
		if (i < container->pipe_count)
			close(container->pipes[i][1]);
		i++;
	}
}
