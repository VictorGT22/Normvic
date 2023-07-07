/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dentro_carpeta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:16:44 by vics              #+#    #+#             */
/*   Updated: 2023/07/06 21:32:09 by vics             ###   ########.fr       */
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
		if (!ft_strnstr(lst->info[i], "/*", len))
		{
		}
	}
	if (error)
	{
		print_error(lst, ERROR_HEADER, line + 1, SOLVABLE);
		lst->no_error = false;
	}
	*add_i = i;
}

void	remove_last_spaces(s_variables *var, lst_dir *lst, int i)
{
	int	j;
	int	line;

	line = 0;
	j = ft_strlen(lst->info[i]) - 1;
	if (lst->info[i][j] == '\n')
	{
		lst->info[i][j] = '\0';
		j--;
	}
	while (j >= 0 && (lst->info[i][j] == ' ' || lst->info[i][j] == lst->info[i][lower]) && lst->info[i][j] == lst->info[i][lower])
	{
		if (line == 0)
		{
			line = i;
			print_error(lst, ERROR_TRALING_SPACE, line + 1, SOLVABLE);
		}
		lst->info[i][j] = '\0';
		j--;
	}
	if (!ft_strchr(lst->info[i], '\n'))
	{
		lst->info[i][j + 1] = '\n';
	}
}
