/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otboumeh <otboumeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:54:12 by otboumeh          #+#    #+#             */
/*   Updated: 2024/05/26 16:35:39 by otboumeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char	*deposit, const char	*buffer)
{
	int		i;
	int		j;
	char	*str;

	if (!deposit)
	{
		deposit = (char *)malloc(1 * sizeof(char));
		deposit[0] = '\0';
	}
	if (!deposit || !buffer)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(deposit) + ft_strlen(buffer) + 1));
	if (str == NULL)
		return (0);
	i = -1;
	j = 0;
	if (deposit)
		while (deposit[++i] != '\0')
			str[i] = deposit[i];
	while (buffer[j] != '\0')
		str[i++] = buffer[j++];
	str[ft_strlen(deposit) + ft_strlen(buffer)] = '\0';
	free (deposit);
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	ch;

	if (!s)
		return (NULL);
	ch = (char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ch)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (s[i] == ch)
		return ((char *)&s[i]);
	return (NULL);
}
