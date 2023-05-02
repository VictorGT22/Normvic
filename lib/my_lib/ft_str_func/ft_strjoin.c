/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:41:55 by victgonz          #+#    #+#             */
/*   Updated: 2023/04/26 21:49:29 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ext_join(char *s1, char *s2)
{
	char	*str;
	int		len_s1;
	int		len_s2;
	int		x;

	len_s1 = ft_strlen((char *)s1);
	len_s2 = ft_strlen((char *)s2);
	str = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str)
		return (0);
	x = -1;
	while (s1[++x])
		str[x] = s1[x];
	x = -1;
	while (s2[++x])
		str[x + len_s1] = s2[x];
	str[x + len_s1] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	if (!s1)
	{
		s1 = malloc(sizeof(char) + 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	if (s1 && s2)
		return (ext_join(s1, s2));
	return (NULL);
}
