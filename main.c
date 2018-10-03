#include "filler.h"


void 	set_nude_pieces_coord(t_filler *filler)
{
	int		x;
	int 	y;

	y = 0;
	filler->piece.start_x = 20000000;
	filler->piece.end_x = 0;
	filler->piece.start_y = -1;
	filler->piece.end_y = 0;
	while (y < filler->piece.size_y)
	{
		x = 0;
		while (x < filler->piece.size_x)
		{
			if (filler->piece.piece[y][x] == '*')
			{
				if (x < filler->piece.start_x)
					filler->piece.start_x = x;

				if (x > filler->piece.end_x)
					filler->piece.end_x = x;

				if (filler->piece.start_y == -1)
					filler->piece.start_y = y;

				if (filler->piece.end_y < y)
					filler->piece.end_y = y;
			}
			x++;
		}
		y++;
	}
}

void	find_absolute_coord(t_filler *filler)
{
	filler->choices->x -= filler->piece.start_x;
	filler->choices->y -= filler->piece.start_y;
}

int 	check_absolute_cord(t_filler *filler, t_choices *temp)
{
	if (filler->choices->x - temp->x > filler->map.size_x || filler->choices->y - temp->y > filler->map.size_y ||
	filler->choices->x - temp->x < 0 || filler->choices->y - temp->y < 0)
		return (0);
	return (1);
}

void 	find_the_best_choice(t_filler *filler)
{
	t_choices	*tiny;
	t_choices	*temp;

	temp = filler->choices;
	tiny = filler->choices;
//	tiny = NULL;
	while (temp)
	{
		if (temp->points < tiny->points && check_absolute_cord(filler, temp))
			tiny = temp;
		temp = temp->next;
	}
	filler->choices = tiny;
	//delete old
}

void    clean_all(t_filler *filler)
{
    int     size_y;
    int     size_piece_y;
    t_choices   *temp;

    size_y = filler->map.size_y;
    while (size_y--)
    {
//        free(filler->map.map[size_y]);
//		filler->map.map[size_y] = NULL;
        free(filler->bfs[size_y]);
		filler->bfs[size_y] = NULL;
    }
    free(filler->bfs);
    filler->bfs = NULL;
    size_piece_y = filler->piece.size_y;
    while (size_piece_y--)
    {
    	
        free(filler->piece.piece[size_piece_y]);
		filler->piece.piece[size_piece_y] = NULL;
    }
    while (filler->choices)
    {
        temp = filler->choices->next;
        free(filler->choices);
        filler->choices = NULL;
        filler->choices = temp;
    }
    free(filler->piece.piece);
    filler->piece.piece = NULL;
    free(filler->map.map);
	filler->map.map = NULL;
	size_piece_y = filler->piece.end_y - filler->piece.start_y + 1;
	while (size_piece_y != -1)
	{
		free(filler->piece.real_piece[size_piece_y]);
		filler->piece.real_piece[size_piece_y] = NULL;
		size_piece_y--;
	}
	free(filler->piece.real_piece);
	filler->piece = (t_piece){0, 0, 0, 0, 0, 0, NULL, NULL};
	filler->piece.real_piece = NULL;
}



int		main(void)
{
	char *line;
	t_filler filler;
	
	filler.my = '\0';
    filler.choices = NULL;  //delete
    fd = open("test", O_RDWR | O_APPEND);
	while (lgnl(0, &line) > 0)
	{
        if (!line || *line == '\n' || *line == 0)
            exit (1);
		if (!filler.my && ft_strstr(line, "$$$") && ft_strstr(line, "ariabyi.filler"))
		{
			filler.my = (line[10] == '1') ? (char)'O' : (char)'X';
			filler.enemy = (line[10] == '1') ? (char)'X' : (char)'O';
		}
		else if (ft_strstr(line, "Plateau "))
		{
			get_filler(line, &filler, 1);
            fill_map(&filler, 1);
        }
		else if (ft_strstr(line, "Piece "))
		{
			get_filler(line, &filler, 3);
            ft_putendl_fd("before", fd);
            fill_piece(&filler);
			set_nude_pieces_coord(&filler);
			get_real_piece(&filler);
			real_work(&filler);
            find_the_best_choice(&filler);
            ft_putendl_fd("after", fd);
            if (filler.choices)
            {
				find_absolute_coord(&filler);
                ft_putnbr_fd(filler.choices->y, fd);
                ft_putchar_fd(' ', fd);
                ft_putnbr_fd(filler.choices->x, fd);
                ft_putchar_fd('\n', fd);
                ft_putnbr_fd(filler.choices->y, 1);
                ft_putchar_fd(' ', 1);
                ft_putnbr_fd(filler.choices->x, 1);
                ft_putchar_fd('\n', 1);
            }
            else
            {
				clean_all(&filler);
				return  (0);
            }
            clean_all(&filler);
        }
	}
    ft_putendl_fd("fin", fd);
    return (0);
}
