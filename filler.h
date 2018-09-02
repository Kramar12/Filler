/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 16:53:00 by ariabyi           #+#    #+#             */
/*   Updated: 2018/08/19 16:53:00 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

typedef struct	s_coordinates
{
	int		x;
	int		y;

}				t_coordinates;

typedef struct	s_map
{
	int		size_x;
	int		size_y;
	char	**map;

}				t_map;

typedef struct	s_piece
{
//	int		start_x;
//	int		end_x;
//	int		start_y;
//	int		end_y;
	//		^^^^?????
	int		size_x;
	int		size_y;
	char	**piece;

}				t_piece;

typedef struct	s_filler
{
	char		*my;
	char		*enemy;
	t_map		map;
	t_piece		piece;
	int 		**bfs;

	t_coordinates		valid;

}				t_filler;

#endif