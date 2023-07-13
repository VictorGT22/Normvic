/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dentro_carpeta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:16:44 by vics              #+#    #+#             */
/*   Updated: 2023/07/14 01:50:07 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normez.h"

int	check_spaces_operator(s_variables *var, lst_dir *lst, int *i, int op, int lower)
{
	int x;
	int space;
	int len;

	if (!ft_strcmp(var->operators[op], "(") || !ft_strcmp(var->operators[op], ")") || !ft_strcmp(var->operators[op], ";"))
	{
		int pos_keyword = is_keyword(var, lst, *i, var->keywords);
		pos_keyword != 0 ? ft_strlen(var->keywords[type_keyword(var, lst, *i, var->keywords)]) : 0;
	}
	return (space);
}
