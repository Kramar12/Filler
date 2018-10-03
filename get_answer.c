#include "filler.h"

int     check_points(t_choices *choices, t_filler *filler)
{
	int 	sum;
	int     x_map, y_map;
	int     i = 0, j = 0;
	
	sum = 0;
	x_map = choices->x;
	y_map = choices->y;
	while (i < filler->piece.size_y && filler->piece.real_piece && filler->piece.real_piece[i] && filler->piece.real_piece[i][j])
	{
		while (filler->piece.real_piece && filler->piece.real_piece[i] && filler->piece.real_piece[i][j])
		{
			if (filler->bfs && filler->bfs[y_map])
			{
				if (filler->piece.real_piece[i][j] != '.')
					sum += filler->bfs[y_map][x_map];
			}
			else
				return (-1);
			j++;
			x_map++;
		}
		i++;
		x_map = choices->x;
		j = 0;
		y_map++;
	}
	choices->points = sum;
	return (1);
}

int 	check_touches(t_filler *filler, int y_got, int x_got)
{
	int 	touches;
	int     x_map, y_map;
	int         i = 0, j = 0;
	
	touches = 0;
	x_map = x_got;
	y_map = y_got;
	while (i <=  (filler->piece.end_y - filler->piece.start_y + 1))
	{
		while (filler->piece.real_piece && filler->piece.real_piece[i] && filler->piece.real_piece[i][j] && j <= filler->piece.end_x)
		{
			if (y_map >= filler->map.size_y || x_map >= filler->map.size_x || filler->map.map[y_map][x_map] == 0)
				return (0);
			if ((filler->map.map[y_map][x_map] == filler->my || filler->map.map[y_map][x_map] == (filler->my + 32)) && filler->piece.real_piece[i][j] != '.')
				if (++touches > 1)
				{
					return (0);
				}
			if ((filler->map.map[y_map][x_map] == filler->enemy || filler->map.map[y_map][x_map] == (filler->enemy + 32)))
				return (0);
			j++;
			x_map++;
		}
		i++;
		x_map = x_got;
		j = 0;
		y_map++;
	}
	return (touches);
}

void 	get_push_to_ll(t_filler *filler, int y_offset, int x_offset)
{
	t_choices 	*choices;
	
	choices = (t_choices *)malloc(sizeof(t_choices));
	choices->x = x_offset;
	choices->y = y_offset;
	if (check_points(choices, filler) == 1 && choices->points <= -3)
	{
		free(choices);
		return ;
	}
	choices->next = filler->choices;
	filler->choices = choices;
}

void 	real_work(t_filler *filler)
{
	int x;
	int y;
	
	y = 0;
	while (y < filler->map.size_y)
	{
		x = 0;
		while (x < filler->map.size_x)
		{
			if (check_touches(filler, y, x))
			{
				get_push_to_ll(filler, y, x);
			}
			x++;
		}
		y++;
	}
}