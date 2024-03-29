/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_inarr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:25:32 by victgonz          #+#    #+#             */
/*   Updated: 2023/07/01 15:34:01 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_inarr(char **arr, char *to_find)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i] != NULL)
	{
		if (ft_strcmp(arr[i], to_find) == 0)
			return (1);
		i++;
	}
	return (0);
}
