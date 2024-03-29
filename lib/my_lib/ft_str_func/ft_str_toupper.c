/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_toupper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 22:49:03 by vics              #+#    #+#             */
/*   Updated: 2023/07/01 23:25:34 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_str_toupper(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		str[x] = ft_toupper(str[x]);
		x++;
	}
}
