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

typedef struct	s_map
{
	int		size_x;
	int		size_y;
	char	**map;

}				t_map;

typedef struct	s_piece
{
	int		start_x;
	int		end_x;
	int		start_y;
	int		end_y;
	int		size_x;
	int		size_y;
	char	**piece;

}				t_piece;

typedef struct	s_choices
{
	int					x;
	int					y;
	int					points;
	int                 min;
	struct s_choices	*next;

}				t_choices;

typedef struct	s_filler
{
	char		*my;
	char		*enemy;
	t_map		map;
	t_piece		piece;
	t_choices	*choices;
	int 		**bfs;

}				t_filler;

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

#endif