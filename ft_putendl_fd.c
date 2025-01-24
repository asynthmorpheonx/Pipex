/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:37:25 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/01/24 21:16:49 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"

void	ft_putendl_fd(char *s1, char *s2, int fd)
{
	char *str;
	char *temp;

	if (s1 == NULL || fd < 0)
		return ;
	str = ft_strjoin(s1, s2);
	temp = ft_strjoin(str, "\n");
	free(str);
	write(fd, temp, ft_strlen(temp));
	free(temp);
}
