#include <stdio.h>
#include "libft/libft.h"
#include "filler.h"

void 	fal(t_filler *filler);
void 	printss(int **max, int y, int x)
{
	int 	i = 0, j = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			printf("%3d", max[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void 	tryon_piece(t_filler *filler)
{

}

void 	fal1(t_filler *filler)
{
	int	i;
	int	j;
	int num;

	num = 0;
	i = 0;
	while (i < filler->map.size_y)
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
		printf("\n\tSORTED ONE MORE TIME\n");
		printss(filler->bfs, filler->map.size_y, filler->map.size_x);
	}
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
	else if (code == 2)
		filler->piece.piece = (char **)malloc(sizeof(char *) * filler->piece.size_y);
	while (fring-- && gnl(0, &line) > 0)
	{
		if (!fl && code == 1 && line && line[4] == '0' && (fl = 1))
			continue ;
		if (code == 1)
			filler->map.map[c++] = ft_strdup(line + 4);
		else if (code == 2)
			filler->piece.piece[c++] = ft_strdup(line);
		ft_strdel(&line);
	}
	if (code == 1)
	{
		fal(filler);
//		printss(filler->bfs, filler->map.size_y, filler->map.size_x);
		fal1(filler);
//		exit (0);
		printf("\n\tSORTED ONE MORE TIME\n");
		printss(filler->bfs, filler->map.size_y, filler->map.size_x);
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
				filler->bfs[ic][iic] = 0;
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

int		main(void)
{
	char *line;
	t_filler filler;

	filler.my = '\0';
	while (gnl(0, &line) > 0)
	{
		if (!filler.my && ft_strstr(line, "ariabyi.filler"))
		{
			filler.my = (line[10] == '2') ? "Oo" : "Xx";
			filler.enemy = (line[10] == '2') ? "Xx" : "Oo";
		}
		else if (ft_strncmp("Plateau", line, 7) == 0) // add 32
		{
			get_filler(line, &filler, 1);
			fill_filler(&filler, 1);
		}
		else if (ft_strncmp("Piece", line, 5) == 0)
		{
			get_filler(line, &filler, 3);
			fill_filler(&filler, 2);
			//return coordinates
			//free all
		}
		ft_strdel(&line);
	}
	return (0);
}
