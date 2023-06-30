/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dentro_carpeta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:16:44 by vics              #+#    #+#             */
/*   Updated: 2023/06/30 22:28:45 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normez.h"

unsigned int	check_header(s_variables *var, lst_dir *lst, int *add_i)
{
	int		i;
	int		len;
	int		line;
	bool	error;

	error = false;
	i = *add_i;
	while (lst->info[i] && i < 11) 
	{
		len = ft_strlen(lst->info[i]);
		if ((!ft_strnstr(lst->info[i], "/*", len)
		|| !ft_strnstr(lst->info[i], "*/", len) || len != 81) && !error)
		{
			line = i;
			error = true;
		}
		i++;
	}
	if (error)
	{
		print_error(lst->path, ERROR_HEADER, line + 1, LOW);
		lst->no_error = false;
	}
	*add_i = i;
	/*prueba
	a ver como borro esto*/
}
