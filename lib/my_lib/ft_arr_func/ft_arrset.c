/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victgonz <victgonz@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:02:56 by victgonz          #+#    #+#             */
/*   Updated: 2023/02/02 10:03:06 by victgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrset(char **arr, char *str, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (str == NULL)
			arr[i] = NULL;
		else
			ft_strlcpy(arr[i], str, ft_strlen(str));
		i++;
	}
}
