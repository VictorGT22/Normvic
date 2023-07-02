/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dQntro_carpeta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:16:44 by vics              #+#    #+#             */
/*   Updated: 2023/07/02 19:00:43 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normez.h"

unsigned int	check_header(s_variables *var, lst_dir *lst, int *add_i)
{
	if (lst->info[*i][x] == '/' && (lst->info[*i][x + 1] == '/' ||
	lst->info[*i][x + 1] == '*'))
		print_error(lst->path, ERROR_HEADER, 1 + 1, LOW);
	//PRUEBA
}
