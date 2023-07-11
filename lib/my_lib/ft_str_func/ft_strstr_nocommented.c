/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_nocommented.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:06:18 by vics              #+#    #+#             */
/*   Updated: 2023/07/11 14:06:33 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strstr_index_nocommented(const char *haystack, const char *needle, int ini)
{
	size_t	i;
	size_t	j;
	char c_comment;
	int num_comment;

	i = ini;
	num_comment = 0;
	if (!needle[0])
		return (-1);
	if (ini > ft_strlen(haystack))
		return (-1);
	while (haystack[i])
	{
		j = 0;
		if (haystack[i] == '"' || haystack[i] == '\'')
		{
			c_comment = haystack[i];
			num_comment++;
			i++;
		}
		while(haystack[i] && num_comment != 0)
		{
			if (haystack[i] == c_comment)
				num_comment--;
			i++;
		}
		while (needle[j] && haystack[i + j] == needle[j])
			j++;
		if (!needle[j])
			return (i);
		i++;
	}
	return (-1);
}