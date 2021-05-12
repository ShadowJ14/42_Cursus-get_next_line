/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:59:26 by lprates           #+#    #+#             */
/*   Updated: 2021/02/27 11:39:51 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*trim_keep(char *keep)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!keep)
		return (0);
	while (keep[i] && keep[i] != '\n')
		i++;
	if (!keep[i])
	{
		free(keep);
		return (0);
	}
	if (!(tmp = malloc(sizeof(char) * ((ft_strlen(keep) - i) + 1))))
		return (0);
	i++;
	while (keep[i])
		tmp[j++] = keep[i++];
	tmp[j] = '\0';
	free(keep);
	return (tmp);
}

char	*check_keep(char *keep)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!keep)
		return (0);
	while (keep[i] && keep[i] != '\n')
		i++;
	if (!(tmp = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (keep[i] && keep[i] != '\n')
	{
		tmp[i] = keep[i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}

int		get_next_line(int fd, char **line)
{
	static char		*keep;
	char			*buffer;
	int				reader;

	reader = 1;
	if ((read(fd, 0, 0) == -1) || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buffer = malloc(BUFFER_SIZE + 1)))
		return (-1);
	while (!has_line(keep) && reader != 0)
	{
		if ((reader = read(fd, buffer, BUFFER_SIZE)) == -1)
		{
			free(buffer);
			return (-1);
		}
		buffer[reader] = 0;
		keep = ft_strjoin(keep, buffer);
	}
	free(buffer);
	*line = check_keep(keep);
	keep = trim_keep(keep);
	if (reader == 0)
		return (0);
	return (1);
}
