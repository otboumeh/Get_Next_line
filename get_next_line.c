/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:48:47 by otboumeh          #+#    #+#             */
/*   Updated: 2024/05/25 11:56:49 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "get_next_line.h"

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

char	*get_next_line(int fd)
{
	static char	*deposit;
	char		buffer[BUFFER_SIZE +1];
	int			readbytes;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	readbytes = 1;
	while (!ft_strchr(deposit, '\n') && readbytes > 0)
	{
		readbytes = read(fd, buffer, BUFFER_SIZE);
		if (readbytes == -1)
			return (NULL);
		buffer[readbytes] = '\0';
		deposit = ft_strjoin(deposit, buffer);
	}
	if (!deposit)
		return (NULL);
	line = create_line(deposit);
	deposit = excess(deposit);
	return (line);
}

/* int	main(void)
{
	int		fd;
	char	*line;

	fd = open("read_error.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
} */