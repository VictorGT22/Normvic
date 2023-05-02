/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victgonz <victgonz@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:54:03 by victgonz          #+#    #+#             */
/*   Updated: 2023/02/10 08:14:16 by victgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	itoa_getnbr(long int nbr, char *str)
{
	if (nbr < 0)
	{
		nbr *= -1;
		ft_add_in_str(str, '-');
	}
	if (nbr > 9)
	{
		itoa_getnbr(nbr / 10, str);
		itoa_getnbr(nbr % 10, str);
	}
	else
		ft_add_in_str(str, nbr + '0');
}

char	*ft_itoa(int n)
{
	char		*str;
	long int	nbr;

	nbr = (long int)n;
	str = malloc(sizeof(char) * ft_nbrlen(nbr) + 1);
	if (!str)
		return (NULL);
	ft_memset(str, '\0', ft_nbrlen(nbr) + 1);
	itoa_getnbr(nbr, str);
	return (str);
}
