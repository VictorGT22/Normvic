/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:35:24 by victgonz          #+#    #+#             */
/*   Updated: 2023/06/19 11:50:11 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, char c)
{
	char	*ptr;

	ptr = NULL;
	while (*str != '\0')
	{
		if (*str == c)
			ptr = (char *)str;
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return (ptr);
}
int	ft_strrchr_index(const char *str, char c)
{
	int	i;
	int	index;

	i = 0;
	index = -1;
	while (str[i])
	{
		if (str[i] == c)
			index = i;
		i++;
	}
	if (c == '\0')
		return (i);
	return (index);
}
