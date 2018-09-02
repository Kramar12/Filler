/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_iarr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 18:51:09 by ariabyi           #+#    #+#             */
/*   Updated: 2018/08/29 18:53:14 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int 	ft_check_iarr(int **arr, int x, int y, int num)
{
	int 		i;
	int 		j;

	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			if (arr[i][j] == num)
				return (1);
			j++;
		}
		i++;
	}

	return (0);
}
