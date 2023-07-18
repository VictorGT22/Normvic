/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dentro_carpeta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:16:44 by vics              #+#    #+#             */
/*   Updated: 2023/07/18 14:04:03 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normez.h"

void	correct_header_2(s_variables *var, lst_dir *lst, int *i)
{
	char		*str;
	time_t		tiempo_actual;
	struct tm	*info_tiempo;
	char		buffer[80];

	if (*prueba && &prueba_2)
		prueba = *i + *i;
	j = (index == -1) ? ft_strlen(lst->info[*i]) - 3 : index - 2;
	index = ft_strchr_nocomented(lst->info[*i], '(');
	if (index != -1 && index < j)
		j = ft_strchr_nocomented(lst->info[*i], '(') + 1;
}
