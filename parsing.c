#include "filler.h"
//#include "libft/ft_strsub.c"

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

void 	fill_piece(t_filler *filler)
{
	char *line;
	int fring;
	int c;
	
	c = 0;
	fring = filler->piece.size_y;
	filler->piece.piece = (char **)malloc(sizeof(char *) * (filler->piece.size_y + 1));
	while (fring-- && lgnl(0, &line))
		filler->piece.piece[c++] = ft_strdup(line);
	filler->piece.piece[c] = NULL;
	
}

int 	fill_map(t_filler *filler, int code)
{
	int 	fring;
	int 	c;
	char 	*line;
	int 	fl;
	
	fl = 0;
	c = 0;
	fring = filler->map.size_y + 1;
	filler->map.map = (char **)malloc(sizeof(char *) * filler->map.size_y);
	while (fring-- && lgnl(0, &line))
	{
		if (!fl && code == 1 && line && line[4] == '0')
		    fl = 1;
		else
			filler->map.map[c++] = ft_strdup(line + 4);
		ft_strdel(&line);
	}
	filler->map.map[c] = NULL;
	fal(filler);
	return (0);
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
//	write(1, "\n\n", 2);
//	printss(filler->bfs, filler->map.size_y, filler->map.size_x, 0, 0);

//    printf("\n\tSORTED ONE sMORE TIME\n");
//    printss(filler->bfs, filler->map.size_y, filler->map.size_x);
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
			if (filler->map.map[cc][ccc] == filler->my || filler->map.map[cc][ccc] == (filler->my + 32))
				filler->bfs[ic][iic] = -3;
			else if (filler->map.map[cc][ccc] == filler->enemy || filler->map.map[cc][ccc] == (filler->enemy + 32))
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
	filler->bfs[cc] = NULL;
	fal1(filler);
//	printss(filler->bfs, filler->map.size_y, filler->map.size_x, 0, 0);
}

void 	get_real_piece(t_filler *filler)
{
	int i;
	int j;
	int 	len_of_y;
	
	j = 0;
	i = filler->piece.start_y;
	len_of_y = filler->piece.end_y - filler->piece.start_y + 1;
	filler->piece.real_piece = (char **)malloc(sizeof(char *) * (filler->piece.size_y + 1));
	while (filler->piece.piece[i] && j < len_of_y)
	{
		filler->piece.real_piece[j] = ft_strsub(filler->piece.piece[i], (unsigned)filler->piece.start_x, (size_t)filler->piece.end_x + 1);
		i++;
		j++;
	}
	filler->piece.real_piece[j] = NULL;
}