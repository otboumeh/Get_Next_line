/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:53:58 by otboumeh          #+#    #+#             */
/*   Updated: 2024/05/26 16:35:38 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// This function extracts and returns the part of the deposit string that comes after the first newline character.
char	*excess(char *deposit)
{
	char	*excess;
	int		j;
	int		i;

	i = 0;
	j = 0;
	// Find the index of the first newline character or the end of the string
	while (deposit[i] != '\0' && deposit[i] != '\n')
		i++;
	// If no newline character is found, free the deposit and return NULL
	if (!deposit[i])
	{
		free (deposit);
		return (NULL);
	}
	// Allocate memory for the excess string, which is the remaining part after the newline
	excess = malloc(sizeof(char) * (ft_strlen(deposit) - i + 1));
	if (!excess)
		return (NULL);
	i++; // Move past the newline character
	// Copy the rest of the string into excess
	while (deposit[i])
	{
		excess[j++] = deposit[i++];
	}
	excess[j] = '\0'; // Null-terminate the excess string
	free(deposit);    // Free the original deposit string
	return (excess);  // Return the excess part
}
//This function creates and returns a new string containing a single line 
//(up to and including the first newline character) from the deposit.
char	*create_line(char *deposit)
{
	char	*line;
	int		i;

	i = 0;
	// If the deposit is empty, return NULL
	if (!deposit[0])
		return (NULL);
	// Find the length of the line (up to the first newline character or end of string)
	while (deposit[i] && deposit[i] != '\n')
		i++;
	// Allocate memory for the line, including space for the newline character and null terminator
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	// Copy the characters from deposit to line
	while (deposit[i] && deposit[i] != '\n')
	{
		line[i] = deposit[i];
		i++;
	}
	// If there's a newline character, include it in the line
	if (deposit[i] == '\n')
	{
		line[i] = deposit[i];
		i++;
	}
	line[i] = '\0';  // Null-terminate the line
	return (line);  // Return the line
}
//This function reads from the file descriptor fd and returns the next line, 
//maintaining state across multiple calls using a static variable.

char	*get_next_line(int fd)
{
	static char	*deposit; // Static variable to store leftover data between function calls
	char		buffer[BUFFER_SIZE +1]; // Buffer to store data read from the file
	int			readbytes; // Number of bytes read from the file
	char		*line;

	// Validate file descriptor and buffer size
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	readbytes = 1;
	// Continue reading until a newline is found or end of file is reached
	while (!ft_strchr(deposit, '\n') && readbytes > 0)
	{
		readbytes = read(fd, buffer, BUFFER_SIZE); // Read data into the buffer
		if (readbytes == -1)        // Check for read error
			return (NULL);
		buffer[readbytes] = '\0'; // Null-terminate the buffer
		deposit = ft_strjoin(deposit, buffer); // Append buffer to deposit
	}
	if (readbytes == -1)
		free (deposit); // Free deposit if there's a read error
	if (!deposit)
		return (NULL); // Return NULL if deposit is empty
	line = create_line(deposit); // Create a line from the deposit
	deposit = excess(deposit); // Update deposit with the excess part after the newline
	return (line); // Return the line
}
