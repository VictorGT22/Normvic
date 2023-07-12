/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victgonz <victgonz@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:49:05 by victgonz          #+#    #+#             */
/*   Updated: 2023/02/10 08:14:16 by victgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *str, char(*f)(unsigned int, char))
{
	char			*f_str;
	unsigned int	i;

	if (!str || !f)
		return (NULL);
	f_str = malloc(sizeof(char) * (ft_strlen((char *)str) + 1));
	if (!f_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		f_str[i] = f(i, str[i]);
		i++;
	}
	f_str[i] = '\0';
	return (f_str);
}
