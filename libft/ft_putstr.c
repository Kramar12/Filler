/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:46:16 by ariabyi           #+#    #+#             */
/*   Updated: 2018/02/08 18:07:29 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_putstr(char const *s)
{
	size_t	counter;

	counter = ft_strlen(s);
	if (s && *s)
		write(1, s, ft_strlen(s));
	return (counter);
}
