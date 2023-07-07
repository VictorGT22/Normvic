/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isupper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 22:36:38 by vics              #+#    #+#             */
/*   Updated: 2023/07/07 17:00:01 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_isupper(char *str) //acabo de modificar esta funcion
{
	int x;

	x = 0;
	while (str[x])
	{
		if (ft_isalpha(str[x]) && (str[x] < 'A' || str[x] > 'Z'))
			return (0);
		x++;
	}
	return (1);
}