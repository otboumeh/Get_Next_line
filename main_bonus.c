/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:34:37 by otboumeh          #+#    #+#             */
/*   Updated: 2024/05/26 16:35:36 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	main(void)
{
	int		fd1, fd2, fd3;
	char	*line;
	int		count;

	fd1 = open("text.txt", O_RDONLY);
    fd2 = open("text1.txt", O_RDONLY);
    fd3 = open("text2.txt", O_RDONLY);
	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
	{
		printf("Error opening file\n");
		return (1);
	}
	count = 0;
	while (1)
	{
		line = get_next_line(fd1);
		if (line == NULL)
			break ;
		count++;
		printf("line[%d] : %s", count, line);
		free(line);
		line = NULL;
	}
	printf("\n---------------------END OF FILE 1--------------------------\n");
    count = 0;
	while (1)
	{
		line = get_next_line(fd2);
		if (line == NULL)
			break ;
		count++;
		printf("line[%d] : %s", count, line);
		free(line);
		line = NULL;
	}
	printf("\n---------------------------END OF FILE 2----------------------\n");
    count = 0;
	while (1)
	{
		line = get_next_line(fd3);
		if (line == NULL)
			break ;
		count++;
		printf("line[%d] : %s", count, line);
		free(line);
		line = NULL;
	}
	printf("\n-----------------END OF FILE 3---------------------------\n");
	close(fd1);
    close(fd2);
    close(fd3);
	return (0);
} 