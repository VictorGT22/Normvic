/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_empty_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:21:37 by vics              #+#    #+#             */
/*   Updated: 2023/07/11 17:31:43 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_empty_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '\n' && line[i] != '\t' && line[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}