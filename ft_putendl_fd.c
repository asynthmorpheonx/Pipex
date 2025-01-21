/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:37:25 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/21 20:28:11 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"

void	ft_putendl_fd(char *s1, char *s2, int fd)
{
	size_t	i;

	i = 0;
	if (s1 == NULL || fd < 0)
		return ;
	while (s1[i] != '\0')
	{
		write(fd, &s1[i], 1);
		i++;
	}
	i = 0;
	if (s2)
	{
		while (s2[i] != '\0')
		{
			write(fd, &s2[i], 1);
			i++;
		}	
	}
	write(fd, "\n", 1);
}
