/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victgonz <victgonz@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:30:53 by victgonz          #+#    #+#             */
/*   Updated: 2023/02/12 23:21:57 by victgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

s_Main *inti_structs()
{
	s_Main	*var;

	var = ft_calloc(sizeof(s_Main), 1);
	var->flags = ft_split((const char *)"#, ,0,+,-,h,hh,l,ll,j,z,*,$,L,", ',');
	var->conv = ft_strdup("sSpdDioOuUxXcCeEfFgGaAnbrkp%");
	return (var);
}

int	ft_printf(const char *str, ...)
{
	s_Main	*var;
	va_list	list;
	int		total;

	va_start(list, str);
	var = inti_structs();
	var->first_ptr = ft_calloc(sizeof(t_list), 1);
	var->current_ptr = var->first_ptr;
	var->num_conv = ft_strlen(var->conv);
	var->arr_func = ft_calloc(sizeof(s_fnc_ptr), (var->num_conv));
	fill_operations(var->arr_func);
	total = get_params(var, (char *)str, list);
	free_all(var);
	va_end(list);
	return (total);
}
