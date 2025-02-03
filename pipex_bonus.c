/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:26:49 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/31 19:30:22 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils_bonus.h"

t_box	*handle_here_doc(char **av, int ac)
{
	char	*input;
	t_box	*container;

	container = init_t_box(ac, 1);
	while (1)
	{
		write(1, "heredoc>", 8);
		input = get_next_line(0);
		if (!input)
			write(1, "\n", 1);
		if (ft_strncmp(av[2], input, ft_strlen(input) - 1) == 0)
		{
			free(input);
			break ;
		}
		write(container->pipes[0][1], input, ft_strlen(input));
		free(input);
	}
	close(container->pipes[0][1]);
	get_next_line(-1);
	return (container);
}

int	main(int ac, char **av, char **envp)
{
	t_box	*container;
	int		status;

	status = 0;
	if (ac < 5)
		return (ft_putendl_fd("syntax error :",
				"./pipex infile cmd1 cmd2 ... outfile", 2), 1);
	if (ft_strncmp("here_doc", av[1], 9) == 0)
		container = handle_here_doc(av, ac);
	else
		container = init_t_box(ac, 0);
	forking_for_executing(container, av, envp);
	wait_all_childs(container, &status);
	free_t_box(container);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
