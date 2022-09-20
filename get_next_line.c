/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssawane <ssawane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:01:43 by ssawane           #+#    #+#             */
/*   Updated: 2021/11/16 15:05:19 by ssawane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	char	*str;
	ssize_t	rd;

	rd = read(fd, buf, BUFFER_SIZE);
	if (rd <= 0)
		return (NULL);
	buf[rd] = '\0';
	str = ft_strdup(buf);
	return (str);
}

static char	*disconnect(char **rest)
{
	char	*p_n;
	char	*tmp;
	char	*str;

	if (ft_strlen(*rest) == 0)
	{
		free(*rest);
		*rest = NULL;
		return (NULL);
	}
	p_n = ft_strchr(*rest, '\n');
	if (p_n == 0)
	{
		str = ft_strdup(*rest);
		free(*rest);
		*rest = NULL;
		return (str);
	}
	*p_n = '\0';
	str = ft_strjoin(*rest, "\n");
	p_n++;
	tmp = *rest;
	*rest = ft_strdup(p_n);
	free(tmp);
	return (str);
}

static void	connect(char **rest, int fd)
{
	char	*line;
	char	*tmp;

	while (ft_strchr(*rest, '\n') == 0)
	{
		line = ft_read(fd);
		tmp = *rest;
		if (line == 0)
			break ;
		else
			*rest = ft_strjoin(*rest, line);
		free(tmp);
		free(line);
	}
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (rest == 0)
	{
		rest = ft_read(fd);
		if (rest == 0)
			return (NULL);
	}
	connect(&rest, fd);
	str = disconnect(&rest);
	return (str);
}
