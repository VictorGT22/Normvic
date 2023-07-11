/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:41:55 by victgonz          #+#    #+#             */
/*   Updated: 2023/07/11 15:57:36 by vics             ###   ########.fr       */
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

char	*ft_strjoin_accurate(char *str_1, char *str_2, int pos)
{
	int	i;
	int	j;
	int	x;
	char *str;

	i = 0;
	x = 0;
	j = 0;
	str = malloc(sizeof(char) * ft_strlen(str_1) + ft_strlen(str_2) + 1);
	while (str_1[i] && i < pos)
		str[x++] = str_1[i++];
	while (str_2[j])
		str[x++] = str_2[j++];
	while (str_1[i])
		str[x++] = str_1[i++];
	str[x] = '\0';
	return (str);
} 