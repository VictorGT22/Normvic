/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victgonz <victgonz@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 09:36:40 by victgonz          #+#    #+#             */
/*   Updated: 2023/02/10 08:13:12 by victgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void free_atr(s_Main *var)
{
	if (var->first_ptr->precision)
		free(var->first_ptr->precision);
	if (var->first_ptr->parameter)
		free(var->first_ptr->parameter);
	if (var->first_ptr->width)
		free(var->first_ptr->width);
}

void	free_linked(s_Main *var)
{
	int i;
	t_list *temp;

	while (var->first_ptr)
	{
		i = 0;
		if (var->first_ptr->flag)
		{
			i = 0;
			if (var->first_ptr->flag)
				free(var->first_ptr->flag);
		}
		free_atr(var);
		temp = var->first_ptr;
		var->first_ptr = var->first_ptr->next;
		if (temp)
			free(temp);
	}
}

void	free_all(s_Main *var)
{
	int i;

	if (var->flags)
	{
		i = 0;
		while (var->flags[i])
			free(var->flags[i++]);
		free(var->flags);
	}

	if (var->conv)
		free(var->conv);
	if (var->first_ptr != var->current_ptr)
		free_linked(var);
	else
		free(var->current_ptr);
	free(var->arr_func);
	free(var);
}