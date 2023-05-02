/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victgonz <victgonz@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:34:32 by victgonz          #+#    #+#             */
/*   Updated: 2023/02/12 23:25:15 by victgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	func_n(va_list list, t_list *info)
{
	int len;
	int *int_ptr;

	if (info->prev != NULL)
		len = info->prev->current_total +
			(info->index - (info->prev->index + info->prev->len) - 1);
	else
		len = info->index;
	
	int_ptr = va_arg(list, int *);
	*int_ptr = len;
	return (0);
}
