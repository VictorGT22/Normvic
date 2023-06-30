/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:34:30 by victgonz          #+#    #+#             */
/*   Updated: 2023/04/29 01:01:19 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, char c)
{
	char	*p;

	p = (char *)str;
	while (*p != '\0')
	{
		if ((unsigned char)*p == (unsigned char)c)
			return (p);
		p++;
	}
	if (c == '\0')
		return (p);
	return (NULL);
}

int	ft_chr_index(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);// he cambiado esto cuidado
		}

 int	ft_last_chr_index(char *str, char c)
{
	int		i;

	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == c)
			return (i);
		i--;
	}
	return (i);
}