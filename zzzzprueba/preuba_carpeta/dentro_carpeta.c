/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dentro_carpeta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:14:22 by vics              #+#    #+#             */
/*   Updated: 2023/07/04 11:54:43 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normez.h"

void	print_linked(lst_dir *lst)
{
	int		i;
	lst_dir	*temp;

	temp = lst;
	while (temp)
	{
		printf("path: %s\n", temp->path);
		printf(prueba > 3 ? "Action 1" : "Action 2");
	}
}
