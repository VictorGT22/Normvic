/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dentro_carpeta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:16:44 by vics              #+#    #+#             */
/*   Updated: 2023/07/08 02:53:48 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normez.h"

unsigned int	check_header(s_variables *var, lst_dir *lst, int *add_i)
{
	int		len;
	int		i;
	int		line;
	bool	error;

	error = false;
	i = *add_i;
	len = 0;
	while (lst->info[i] && i < 11)
	{
		len = ft_strlen(lst->info[i]);
		if (!ft_strnstr(lst->info[i], "/*", len))
		{
			error = 0;
		}
	}
	if (error)
	{
		print_error(lst, ERROR_HEADER, line + 1, SOLVABLE);
		lst->no_error = false;
	}
	*add_i = i;
}

unsigned int	check_header(s_variables *var, lst_dir *lst, int *add_i)
{
	int		len;
	int		i;
	int		line;
	bool	error;

	error = false;
	i = *add_i;
	len = 0;
	while (lst->info[i] && i < 11)
	{
		len = ft_strlen(lst->info[i]);
		if (!ft_strnstr(lst->info[i], "/*", len))
		{
			error = 0;
		}
	}
	if (error)
	{
		print_error(lst, ERROR_HEADER, line + 1, SOLVABLE);
		lst->no_error = false;
	}
	*add_i = i;
}
