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

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

#include "libft/libft.h"
#include "stdio.h"

int fd;
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
	char 	**real_piece;

}				t_piece;

typedef struct	s_choices
{
	int					x;
	int					y;
	int					points;
	struct s_choices	*next;

}				t_choices;

typedef struct	s_filler
{
	char		my;
	char		enemy;
	t_map		map;
	t_piece		piece;
	t_choices	*choices;
	int 		**bfs;

}				t_filler;

/*
 * parsing
 */

int		get_filler(char *line, t_filler *filler, int call);
int 	fill_map(t_filler *filler, int code);
void 	fal1(t_filler *filler);
void 	fal(t_filler *filler);
void 	get_real_piece(t_filler *filler);

/*
 * trash
 */

char    *append_char(char **s, char c);
int lgnl(int fd, char **line);
int 	ft_strlast_symb(const char *s, char c, int code);
void 	printss(int **max, int y, int x, int yc, int xc);
void 	print_choises(t_filler *filler);

/*
 * get answer
 */

int     check_points(t_choices *choices, t_filler *filler);
void 	real_work(t_filler *filler);
//int 	real_check_touches(t_filler *filler, int y_got, int x_got);
int 	check_touches(t_filler *filler, int y_got, int x_got);

/*
 * try new
 */
void 	fill_piece(t_filler *filler);


#endif