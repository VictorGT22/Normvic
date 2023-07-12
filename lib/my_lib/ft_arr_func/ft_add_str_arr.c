/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_str_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:50:37 by vics              #+#    #+#             */
/*   Updated: 2023/07/11 14:53:09 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_add_str_arr(char **src_arr, char *str, int pos)
{
	int		i;
	int		len;
	char	**arr;

	i = 0;
	len = ft_arrlen(src_arr);
	arr = malloc(sizeof(char *) * len + 2);
	while (src_arr[i] && i < pos)
	{
		arr[i] = strdup(src_arr[i]);
		i++;
	}
	arr[i] = strdup(str);
	i++;
	while (src_arr[i - 1])
	{
		arr[i] = strdup(src_arr[i - 1]);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
