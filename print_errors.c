/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:37:25 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/25 16:29:50 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"

void	ft_putendl_fd(char *s1, char *s2, int fd)
{
	char	*str;
	char	*temp;

	if (s1 == NULL || fd < 0)
		return ;
	str = ft_strjoin(s1, s2);
	temp = ft_strjoin(str, "\n");
	free(str);
	write(fd, temp, ft_strlen(temp));
	free(temp);
}

void	print_if_error(int the_error, char *probleme)
{
	if (the_error == 2)
		ft_putendl_fd("No such file or directory: ", probleme, 2);
	else if (the_error == 127)
		ft_putendl_fd("command not found: ", probleme, 2);
	else if (the_error == 126)
		ft_putendl_fd("permission denied: ", probleme, 2);
}
