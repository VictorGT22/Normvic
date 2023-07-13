/* ************************************************************************** */
/*                                                                           */
/*                                                        :::      ::::::::   */
/*   dentro_carpeta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:24:24 by                   #+#    #+#             */
/*   Updated: 2023/07/13 15:30:22 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normez.h"

void	print_linked(lst_dir *lst)
{
	lst_dir	*temp;

	temp = lst;
	while (temp)
	{
		printf("path: %s\n", temp->path);
		temp = temp->next;
	}
}
