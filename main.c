#include <stdio.h>
#include "libft/libft.h"
#include "filler.h"

void 	fal(t_filler *filler);
int 	check_touches(t_choices *choices, t_filler *filler);
int     check_points(t_choices *choices, t_filler *filler);

void 	printss(int **max, int y, int x, int yc, int xc)
{
	int 	i = 0, j = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
		    if (i == yc && j == xc)
                printf("%s%3d%s",RED,  max[i][j],RESET);
		    else
                printf("%3d", max[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void 	fal1(t_filler *filler)
{
	int	i;
	int	j;
	int num;

	num = -1;
	i = 0;
	while (i < filler->map.size_y && num < filler->map.size_y + filler->map.size_x)
	{
		j = 0;
		while (j < filler->map.size_x)
		{
			if (filler->bfs[i][j] == num)
			{
				//hor_vir
				if (j + 1 < filler->map.size_x && filler->bfs[i][j + 1] == -2)
					filler->bfs[i][j + 1] = num + 1;
				if (j - 1 >= 0 && filler->bfs[i][j - 1] == -2)
					filler->bfs[i][j - 1] = num + 1;
				if (i + 1 < filler->map.size_y && filler->bfs[i + 1][j] == -2)
					filler->bfs[i + 1][j] = num + 1;
				if (i - 1 >= 0 && filler->bfs[i - 1][j] == -2)
					filler->bfs[i - 1][j] = num + 1;

				//diagonals
				if (i - 1 >= 0 && j + 1 < filler->map.size_x && filler->bfs[i - 1][j + 1] == -2)
					filler->bfs[i - 1][j + 1] = num + 1;
				if (i - 1 >= 0 && j - 1 >= 0 && filler->bfs[i - 1][j - 1] == -2)
					filler->bfs[i - 1][j - 1] = num + 1;
				if (i + 1 < filler->map.size_y && j + 1 < filler->map.size_x && filler->bfs[i + 1][j + 1] == -2)
					filler->bfs[i + 1][j + 1] = num + 1;
				if (i + 1 < filler->map.size_y && j - 1 >= 0 && filler->bfs[i + 1][j - 1] == -2)
					filler->bfs[i + 1][j - 1] = num + 1;
			}
			j++;
		}
		if (++i == filler->map.size_y)
			 if (ft_check_iarr(filler->bfs, filler->map.size_x, filler->map.size_y, -2) && !(i = 0))
				 num++;
//		printf("\n\tSORTED ONE MORE TIME\n");
//		printss(filler->bfs, filler->map.size_y, filler->map.size_x);
	}
	i = 0;
	while (i < filler->map.size_y)
    {
	    j = 0;
	    while (j < filler->map.size_x)
        {
	        if (filler->bfs[i][j] == -2)
	            filler->bfs[i][j] = 99;
	        j++;
        }
        i++;
    }
//    printf("\n\tSORTED ONE sMORE TIME\n");
//    printss(filler->bfs, filler->map.size_y, filler->map.size_x);
}



int 	fill_filler(t_filler *filler, int code)
{
	int 	fring;
	int 	c;
	char 	*line;
	int 	fl;

	fl = 0;
	c = 0;
	fring = (code == 1) ? filler->map.size_y + 1 : filler->piece.size_y;
	if (code == 1)
		filler->map.map = (char **)malloc(sizeof(char *) * filler->map.size_y);
	if (code == 2)
		filler->piece.piece = (char **)malloc(sizeof(char *) * filler->piece.size_y);


    // in this loop


    while (fring-- && gnl(0, &line) > 0)
	{
        if (!fl && code == 1 && line && line[4] == '0' && (fl = 1))
		{
		    free(line);
            continue;
        }
        if (code == 1)
        {
            filler->map.map[c++] = ft_strdup(line + 4);

        }
		if (code == 2)
        {
			filler->piece.piece[c++] = ft_strdup(line);
		}
		ft_strdel(&line);
	}


    if (code == 1)
	{
		fal(filler);
		fal1(filler);
	}
	return (0);
}

int		get_filler(char *line, t_filler *filler, int call)
{
	if (call == 1 || call == 3)
	{
		if (call == 1)
			filler->map.size_y = ft_atoi(line + 7);
		else
			filler->piece.size_y = ft_atoi(line + 5);
		get_filler(line + ft_strlen(line), filler, (call == 1) ? 2 : 4);
	}
	else if (call == 2 || call == 4)
	{
		while (*line != ' ')
			line--;
		if (call == 2)
			filler->map.size_x = ft_atoi(line);
		else
			filler->piece.size_x = ft_atoi(line);
	}
	return (0);
}

void 	fal(t_filler *filler)
{
	int 	cc;
	int 	ccc;
	int 	ic;
	int 	iic;

	ic = 0;
	cc = 0;
	filler->bfs = (int **)malloc(sizeof(int *) * (filler->map.size_y));
	while (filler->map.map[cc])
	{
		ccc = 0;
		iic = 0;
		filler->bfs[ic] = (int *)malloc(sizeof(int) * filler->map.size_x);
		while (filler->map.map[cc][ccc])
		{
			if (filler->map.map[cc][ccc] == filler->my[0] || filler->map.map[cc][ccc] == filler->my[1])
				filler->bfs[ic][iic] = -3;
			else if (filler->map.map[cc][ccc] == filler->enemy[0] || filler->map.map[cc][ccc] == filler->enemy[1])
				filler->bfs[ic][iic] = -1;
			else
				filler->bfs[ic][iic] = -2;
			ccc++;
			iic++;
		}
		ic++;
		cc++;
		if (cc == filler->map.size_y)
			break ;
	}
}

void 	set_nude_pieces_coord(t_filler *filler)
{
	int		x;
	int 	y;

	y = 0;
	filler->piece.start_x = 20000000;
	filler->piece.end_x = 0;
	filler->piece.start_y = 0;
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

				if (filler->piece.start_y == 0)
					filler->piece.start_y = y;

				if (filler->piece.end_y < y)
					filler->piece.end_y = y;
			}
			x++;
		}
		y++;
	}
}

t_choices 	*delete_choice(t_choices *choices)
{
	free(choices);
	return NULL;
}




t_choices 	*tryon_piece(t_filler *filler, int y_offset, int x_offset)
{
    t_choices 	*choices;

    choices = (t_choices *)malloc(sizeof(t_choices));
    choices->x = x_offset;
    choices->y = y_offset;
    if (!check_touches(choices, filler))
    {
        return (delete_choice(choices));
    }
    choices->min = check_points(choices, filler);
    if (filler->choices && choices->min < filler->choices->min)
    {
        return (delete_choice(choices));
    }
    return (choices);
}

int 	check_touches(t_choices *choices, t_filler *filler)
{
	int 	touches;
	int     x_map, y_map;
    int         i = 0, j = 0;

    touches = 0;
	x_map = choices->x;
	y_map = choices->y;
	while (i < filler->piece.size_y && filler->piece.piece && filler->piece.piece[i] && filler->piece.piece[i][j])
	{
	    while (filler->piece.piece && filler->piece.piece[i] && filler->piece.piece[i][j])
	    {
	        if (y_map >= filler->map.size_y || x_map >= filler->map.size_x || filler->map.map[y_map][x_map] == 0)
	            return (0);
            if ((filler->map.map[y_map][x_map] == filler->my[0] || filler->map.map[y_map][x_map] == filler->my[1]) && filler->piece.piece[i][j] != '.')
                if (++touches > 1)
                    return (0);
            if ((filler->map.map[y_map][x_map] == filler->enemy[0] || filler->map.map[y_map][x_map] == filler->enemy[1]))
                return (0);
                j++;
            x_map++;
        }
        i++;
        x_map = choices->x;
	    j = 0;
	    y_map++;
	}
    return (touches ? 1 : 0);
}

int     check_points(t_choices *choices, t_filler *filler)
{
    int 	sum;
    int     x_map, y_map;
    int     i = 0, j = 0;

    sum = 0;
    x_map = choices->x;
    y_map = choices->y;
//    if (choices->y == 8 && choices->x == 2)	//delete
//        write (1, "sd", 0); // delete
    while (i < filler->piece.size_y && filler->piece.piece && filler->piece.piece[i] && filler->piece.piece[i][j])
    {
        while (filler->piece.piece && filler->piece.piece[i] && filler->piece.piece[i][j])
        {
            if (filler->piece.piece[i][j] != '.')
                sum += filler->bfs[y_map][x_map];
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

void 	push_to_ll(t_choices *choices, t_filler *filler)
{
	if (choices == NULL || !check_touches(choices, filler))
    {
	    free(choices);
	    return ;
    }
    check_points(choices, filler);
//	printf("y = %d x = %d p = %d\n", choices->y, choices->x, choices->points);
	choices->next = filler->choices;
	filler->choices = choices;
}

void 	get_all_choices(t_filler *filler)
{
	int x;
	int y;

	y = 0;
	t_filler	*to_ret;
	to_ret = filler;
	while (y < filler->map.size_y)
	{
		x = 0;
		while (x < filler->map.size_x)
		{
			if (x == 2 && y == 7)
				write (1, "fgdg", 0);
			push_to_ll(tryon_piece(filler, y, x), filler);
			x++;
		}
		y++;
	}
	filler = to_ret;
}

void	find_absolute_coord(t_filler *filler)
{
//    printf("\nuntil|y = %d x = %d|\n", filler->choices->y, filler->choices->x);
//	filler->choices->x -= filler->piece.start_x + 1;
//	filler->choices->y -= filler->piece.start_y;
}

void 	find_the_best_choice(t_filler *filler)
{
	t_choices	*tiny;
	t_choices	*temp;

	temp = filler->choices;
	tiny = filler->choices;
	while (temp)
	{
		if (temp->points < tiny->points)
			tiny = temp;
		temp = temp->next;
	}
	filler->choices = tiny;
	//delete old
	if (**filler->piece.piece == '.')
        find_absolute_coord(filler); // HERE I AM!!!!!!!
}

void    clean_all(t_filler *filler)
{
    int     size_y;
    int     size_piece_y;
    t_choices   *temp;

    size_y = filler->map.size_y;
    while (size_y--)
    {
        free(filler->map.map[size_y]);
        free(filler->bfs[size_y]);
    }
    size_piece_y = filler->piece.size_y;
    while (size_piece_y--)
    {
        free(filler->piece.piece[size_piece_y]);
    }
    while (filler->choices)
    {
        temp = filler->choices->next;
        free(filler->choices);
        filler->choices = NULL; // mb i have to delete this
        filler->choices = temp;
    }
    free(filler->piece.piece);
    free(filler->map.map);
}

int		main(void)
{
	char *line;
	t_filler filler;

	filler.my = NULL;
    filler.choices = NULL;  //delete
//    ft_putstr_fd("8 2\n", 2);
//    int fd = 1;

//    write(1, "8 2\n", 4);
//    exit (0);



	while (gnl(0, &line) > 0)
	{
        if (!line || *line == '\n' || *line == 0)
            exit (1);
		if (!filler.my && ft_strstr(line, "$$$") && ft_strstr(line, "ariabyi.filler"))
		{
			filler.my = (line[10] == '2') ? "Xx" : "Oo";
			filler.enemy = (line[10] == '2') ? "Oo" : "Xx";
		}
		else if (ft_strstr(line, "Plateau ")) // add 32
		{

            if (!filler.my)
		        return ((int)write(1, "\nERROR\n", 7));
			get_filler(line, &filler, 1);


            fill_filler(&filler, 1);


        }
		else if (ft_strstr(line, "Piece "))
		{
			get_filler(line, &filler, 3);
			fill_filler(&filler, 2);
			set_nude_pieces_coord(&filler);
            get_all_choices(&filler);

//            printss(filler.bfs, filler.map.size_y, filler.map.size_x, 13 , 13);
            find_the_best_choice(&filler);
//          ft_pmult_fd(fd, 4, ft_itoa(filler.choices->y), " ", ft_itoa(filler.choices->x), "\n");
//			ft_putendl(filler.my);
		if (filler.choices)
		{
			ft_putnbr_fd(filler.choices->y, 1);
			ft_putchar_fd(' ', 1);
			ft_putnbr_fd(filler.choices->x, 1);
			ft_putchar_fd('\n', 1);
		}
		else
			write (1, "THERE IS NOT ENOUGH PLACE!!!\n", 29);
            clean_all(&filler);
//            exit (1);
		}
		ft_strdel(&line);
//        ft_putstr_fd("2 2\n", 2);
	}
	return (0);
}
