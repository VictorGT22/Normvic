/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:14:52 by vics              #+#    #+#             */
/*   Updated: 2023/07/11 15:15:41 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strpop_pos(char *str, int pos)
{
	int	x;

	x = pos;
	while (str[x + 1])
	{
		str[x] = str[x + 1];
		x++;
	}
	str[x] = '\0';
}

void	ft_strpop_interval(char *str, int ini, int end)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (str[i])
	{
		while (str[i] && i >= ini && i <= end)
			i++;
		str[x] = str[i];
		x++;
		i++;
	}
	str[x] = '\0';
}
