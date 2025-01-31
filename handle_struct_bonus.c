/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_struct_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:57:18 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/31 18:44:42 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils_bonus.h"

void	close_pipes(t_box *container)
{
	int	i;

	i = 0;
	while (i < container->pipe_count)
	{
		close(container->pipes[i][0]);
		close(container->pipes[i][1]);
		i++;
	}
}

void	free_pipes(t_box *container)
{
	int	i;

	i = 0;
	while (i < container->pipe_count)
	{
		free(container->pipes[i]);
		i++;
	}
	free(container->pipes);
}

void	free_t_box(t_box *container)
{
	close_pipes(container);
	free_pipes(container);
	free(container->pids);
	free(container);
}

void	make_pipes(t_box *container)
{
	int	i;

	i = 0;
	while (i < container->pipe_count)
	{
		container->pipes[i] = malloc(sizeof(int) * 2);
		if (!container->pipes[i] || pipe(container->pipes[i]) == -1)
			exit (1);
		i++;
	}
}
