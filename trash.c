#include "filler.h"

char    *append_char(char **s, char c)
{
	char *temp;
	size_t len;
	
	if (!*s)
	{
		temp = ft_memalloc(2);
		temp[0] = c;
		temp[1] = '\0';
		return (temp);
	}
	len = ft_strlen(*s);
	temp = ft_memalloc(len + 2);
	ft_strcpy(temp, *s);
	temp[len] = c;
	temp[len + 1] = '\0';
//	free(*s); //we need free this
	*s = NULL;
	return (temp);
}

int lgnl(int fd, char **line)
{
	char buf;
	
	if (fd < 0 || !line)
		return (-1);
	*line = NULL;
	while (read(fd, &buf, 1) > 0)
	{
		if (buf == '\n' || buf == '\0')
			break;
		*line = append_char(line, buf);
	}
	return ((int)ft_strlen(*line));
}

int 	ft_strlast_symb(const char *s, char c, int code)
{
	int 	i;
	int 	last;
	
	i = 0;
	last = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
		{
			last = i;
			if (code == 0)
				return (last);
		}
		i++;
	}
	return (last);
}

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

void 	print_choises(t_filler *filler)
{
	t_choices *back;
	
	back = filler->choices;
	while (filler->choices)
	{
		printf("y = %d, x = %d, points = %d, touches = %d\n", filler->choices->y, filler->choices->x, filler->choices->points, check_touches(filler, filler->choices->y, filler->choices->x));
		filler->choices = filler->choices->next;
	}
	filler->choices = back;
}