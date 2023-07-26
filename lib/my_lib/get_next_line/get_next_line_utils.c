/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:18:02 by victgonz          #+#    #+#             */
/*   Updated: 2023/07/26 12:11:19 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*get_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ext_join_getline(char *s1, char *s2)
{
	char	*str;
	int		len_s1;
	int		len_s2;
	int		x;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = calloc(sizeof(char), (len_s1 + len_s2 + 1));
	if (!str)
		return (NULL);
	x = -1;
	while (s1[++x])
		str[x] = s1[x];
	x = -1;
	while (s2[++x])
		str[x + len_s1] = s2[x];
	str[len_s2 + len_s1] = '\0';
	free(s1);
	return (str);
}

char	*ft_strjoin_getline(char *s1, char *s2)
{
	if (!s1)
	{
		s1 = malloc(sizeof(char) + 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	if (s1 && s2)
		return (ext_join_getline(s1, s2));
	return (NULL);
}
