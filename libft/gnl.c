/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 16:39:33 by ariabyi           #+#    #+#             */
/*   Updated: 2018/04/01 16:39:35 by ariabyi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	endline(char *buff)
{
    int		count;

    count = 0;
    while (buff[count] != ENDL && buff[count])
        count++;
    if (buff[count] == ENDL)
    {
        buff[count] = END;
        return (count);
    }
    else
        return (-1);
}

static char	*join(char *buff, char *tab)
{
    size_t	i;
    size_t	j;
    char	*ptr;

    i = 0;
    j = 0;
    if (buff)
        i = ft_strlen(buff);
    if (tab)
        j = ft_strlen(tab);
    ptr = (char *)malloc(sizeof(*ptr) * (i + j + 1));
    ft_memcpy(ptr, buff, i);
    ft_memcpy(ptr + i, tab, j);
    ptr[i + j] = '\0';
    free(buff);
    ft_bzero(tab, BUFF_SIZE + 1);
    return (ptr);
}

static int	verif(char **buff, char **tab, char **line)
{
    char	*ptr;
    int		final;

    *buff = join(*buff, *tab);
    final = endline(*buff);
    if (final > -1)
    {
        *line = ft_strdup(*buff);
        ptr = *buff;
        *buff = ft_strdup(*buff + final + 1);
        free(ptr);
        return (1);
    }
    return (0);
}

int			gnl(int const fd, char **line)
{
    static char *buff[12000];
    char		*tmp;
    int			result;
    int			ret;

    tmp = ft_strnew(BUFF_SIZE);
    if (!line || BUFF_SIZE <= 0 || fd < 0 || (ret = read(fd, tmp, 0)) < 0)
        return (-1);
    while ((ret = read(fd, tmp, BUFF_SIZE)) > 0)
    {
        result = verif(&buff[fd], &tmp, line);
        free(tmp);
        if (result == 1)
            return (1);
        tmp = ft_strnew(BUFF_SIZE);
    }
    if ((result = verif(&buff[fd], &tmp, line)))
        return (1);
    else if (ft_strlen(buff[fd]) > 0)
    {
        *line = ft_strdup(buff[fd]);
        ft_strdel(&buff[fd]);
        return (1);
    }
    return (result);
}

//
//char	*ft_realloc(char *str)
//{
//	char	*tmp;
//	size_t	n;
//
//	if (!str)
//		return (NULL);
//	n = ft_strlen(str);
//	if (!(tmp = ft_strnew((n + BUFF_SIZE))))
//		return (NULL);
//	ft_memmove(tmp, str, n);
//	ft_strdel(&str);
//	return (tmp);
//}
//
//void	addfile(int fd, char *line, t_list **files)
//{
//	size_t	size;
//	t_list	*tmp;
//
//	if (*files)
//	{
//		tmp = *files;
//		while (tmp->next && (int)tmp->content_size != fd)
//			tmp = tmp->next;
//		if ((int)tmp->content_size == fd)
//			ft_strdel((char **)(&tmp->content));
//		else
//			ft_lstadd(files, (tmp = (t_list *)malloc(sizeof(t_list))));
//	}
//	else
//	{
//		if (!(*files = (t_list *)malloc(sizeof(t_list))))
//			return ;
//		tmp = *files;
//		tmp->next = NULL;
//	}
//	tmp->content_size = fd;
//	size = ft_strlen(line) + 1;
//	tmp->content = ft_strsub(line, size, ft_strlen(line + size));
//}
//
//int		handle_files(t_list *files, int fd, int *f, char **line)
//{
//	t_list			*file;
//	size_t			i;
//
//	file = files;
//	i = 0;
//	*f = 0;
//	if (files)
//		while (file)
//		{
//			if ((int)file->content_size == fd)
//			{
//				i = ft_strlen(file->content);
//				*f = (int)i;
//				break ;
//			}
//			file = file->next;
//		}
//	if (!(*line = ft_strnew(BUFF_SIZE + i)))
//		return (-1);
//	if (i)
//	{
//		ft_memmove(line[0], file->content, i);
//		ft_strdel((char **)(&file->content));
//	}
//	return (i);
//}
//
//void	ft_doit(int *f, long long *i)
//{
//	if (*f)
//	{
//		*f = 0;
//		*i = 0;
//	}
//}
//
//int		gnl(const int fd, char **line)
//{
//	long long		i;
//	static t_list	*files;
//	long long		ret;
//	size_t			oldi;
//	int				f;
//
//	if (!line || fd < 0 || (i = handle_files(files, fd, &f, line)) == -1)
//		return (-1);
//	while (((ret = read(fd, &line[0][i], BUFF_SIZE)) > 0) || f)
//	{
//		oldi = i;
//		ft_doit(&f, &i);
//		while (line[0][i] != '\0' && ret != -1)
//			if (line[0][i] == '\n')
//			{
//				line[0][i] = '\0';
//				if ((size_t)i < ret + oldi)
//					addfile(fd, *line, &files);
//				return (1);
//			}
//			else if ((++i % (BUFF_SIZE + oldi)) == 0)
//				*line = ft_realloc(*line);
//	}
//	ft_strdel((ret == -1) ? line : NULL);
//	return ((i > 0 && ret != -1) ? 1 : ret);
//}
