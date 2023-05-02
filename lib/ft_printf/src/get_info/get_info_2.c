/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victgonz <victgonz@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:40:42 by victgonz          #+#    #+#             */
/*   Updated: 2023/02/12 23:24:40 by victgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_conv(s_Main *var, char *str, int *i)
{
	int	j;

	j = 0;
	while (var->conv[j] != '\0')
	{
		if (str[*i] == var->conv[j])
			var->current_ptr->conv = var->conv[j];
		j++;
	}
}

int	ext_get_params(s_Main *var, char *str, int i)
{
	int	len;

	len = i;
	var->current_ptr->flag = ft_calloc(sizeof(char *), 6);
	var->current_ptr->precision = ft_calloc(sizeof(char), 5);
	var->current_ptr->index = i;
	var->current_ptr->no_val_prec = 0;
	var->current_ptr->num_flags = 0;
	ft_arrset(var->current_ptr->flag, NULL, 5);
	i++;
	get_parameter(var, str, &i);
	while (get_flags(var, str, &i));
	get_width(var, str, &i);
	get_precision(var, str, &i);
	while (get_flags(var, str, &i));
	get_conv(var, str, &i);
	var->current_ptr->len = i - len;
	if (ft_is_inarr(var->current_ptr->flag, ".") && !var->current_ptr->precision[0])
		var->current_ptr->no_val_prec = 1;
	var->current_ptr->precision = !var->current_ptr->precision[0] ?
		strcpy(var->current_ptr->precision, "6") : var->current_ptr->precision;
	return (i);
}

int	get_params(s_Main *var, char *str, va_list list)
{
	int	i;
	int	total;

	i = 0;
	total = 0;	
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i = ext_get_params(var, str, i);
			total += func_ptr(var, list);
			var->current_ptr->current_total = total;
			var->current_ptr->next = ft_calloc(sizeof(t_list), 1);
			var->current_ptr->next->prev = var->current_ptr;
			var->current_ptr = var->current_ptr->next;
			var->current_ptr->next = NULL;
		}
		else
		{
			write(1, &str[i], 1);
			total++;
		}
		i++;
	}
	return (total);
}
