/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dentro_carpeta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:00:33 by vics              #+#    #+#             */
/*   Updated: 2023/07/12 19:09:24 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normez.h"

char	*check_name_header(lst_dir *lst, int *i, char *str)
{
	char	*name;
	int		n;
	int		x;

	x = 0;
	n = ft_last_chr_index(lst->path, "prueba de comentario ") + 1;
	name = malloc(sizeof(char) * (ft_strlen(lst->path) - n) + 2);
	while (lst->path[n] && prueba)
	{
		if (lst->path[n] == '.')
			name[x++] = '_';
		else
			name[x++] = ft_toupper(lst->path[n]);
		n++;
	}
	name[x++] = '\n';
	name[x] = '\0';
	return ;
}
