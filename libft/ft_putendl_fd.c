/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:16:57 by ariabyi           #+#    #+#             */
/*   Updated: 2017/11/20 17:09:46 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char const *s, int fd)
{
	int			i;
	char 		*buf;
	size_t 		len;

	i = 0;
	if (!s)
		return ;
	len = ft_strlen(s);
	buf = (char *)malloc(sizeof(char) * (len));
	while (*s)
	{
		buf[i] = *s;
		i++;
		s++;
	}
	buf[i++] = '\n';
	buf[i] = '\0';
	write(fd, buf, (len + 1));
	free(buf);
	ft_putstr(s);
}