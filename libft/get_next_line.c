/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:39:14 by bkuksa            #+#    #+#             */
/*   Updated: 2018/12/05 13:49:51 by bkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *line, size_t new_size)
{
	char	*new;
	size_t	size;

	if (!line)
	{
		new = ft_strnew(new_size);
		return (new);
	}
	size = ft_strlen(line);
	if (new_size <= size)
		return (line);
	new = ft_strnew(new_size);
	ft_memcpy(new, line, size);
	ft_strdel(&line);
	return (new);
}

int		ft_fill_line(char *buff, char **line)
{
	char	*tmp;
	int		n;

	if ((tmp = ft_strchr(buff, '\n')))
	{
		*line = ft_realloc(*line, ft_strlen(*line) + tmp - buff);
		ft_strncat(*line, buff, tmp - buff);
		ft_memmove(buff, tmp + 1, ft_strlen(tmp));
		return (1);
	}
	if ((n = ft_strlen(buff)))
	{
		*line = ft_realloc(*line, ft_strlen(*line) + n);
		ft_strncat(*line, buff, n);
		*buff = '\0';
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	int			j;
	static char	*buff[MAX_FD];

	if (fd >= MAX_FD || fd < 0 || !(line) || BUFF_SIZE < 1
		|| (!buff[fd] && !(buff[fd] = ft_strnew(BUFF_SIZE))))
		return (-1);
	*line = NULL;
	if (ft_fill_line(buff[fd], line))
		return (1);
	while ((j = read(fd, buff[fd], BUFF_SIZE)) > 0)
	{
		buff[fd][j] = '\0';
		if (ft_fill_line(buff[fd], line))
			return (1);
	}
	if (*line)
		return (1);
	ft_strdel(&buff[fd]);
	if (j < 0)
		return (-1);
	return (0);
}
