/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:54:30 by otboumeh          #+#    #+#             */
/*   Updated: 2024/05/26 16:35:41 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*excess(char *deposit)
{
	char	*excess;
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (deposit[i] != '\0' && deposit[i] != '\n')
		i++;
	if (!deposit[i])
	{
		free (deposit);
		return (NULL);
	}
	excess = malloc(sizeof(char) * (ft_strlen(deposit) - i + 1));
	if (!excess)
		return (NULL);
	i++;
	while (deposit[i])
	{
		excess[j++] = deposit[i++];
	}
	excess[j] = '\0';
	free(deposit);
	return (excess);
}

char	*create_line(char *deposit)
{
	char	*line;
	int		i;

	i = 0;
	if (!deposit[0])
		return (NULL);
	while (deposit[i] && deposit[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (deposit[i] && deposit[i] != '\n')
	{
		line[i] = deposit[i];
		i++;
	}
	if (deposit[i] == '\n')
	{
		line[i] = deposit[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}
/* Using deposit[fd] allows get_next_line to maintain separate reading states for multiple file 
descriptors, enabling concurrent reading from multiple files without data collision or loss.
 This approach makes the function robust and versatile in handling various file I/O scenarios.
 */
char	*get_next_line(int fd)
{
	static char	*deposit[4096]; // Static array to store leftover data for each file descriptor
	char		buffer[BUFFER_SIZE +1];
	int			readbytes;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	readbytes = 1;
	while (!ft_strchr(deposit[fd], '\n') && readbytes != 0)
	{
		readbytes = read(fd, buffer, BUFFER_SIZE);
		if (readbytes == -1)
			return (NULL);
		buffer[readbytes] = '\0';
		deposit[fd] = ft_strjoin(deposit[fd], buffer);
	}
	if (!deposit[fd])
		return (NULL);
	line = create_line(deposit[fd]);
	deposit[fd] = excess(deposit[fd]);
	return (line);
}
