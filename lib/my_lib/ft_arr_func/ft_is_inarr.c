/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_inarr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victgonz <victgonz@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:25:32 by victgonz          #+#    #+#             */
/*   Updated: 2023/02/02 10:13:50 by victgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_inarr(char **arr, char *to_find)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (ft_strcmp(arr[i], to_find) == 0)
			return (1);
		i++;
	}
	return (0);
}