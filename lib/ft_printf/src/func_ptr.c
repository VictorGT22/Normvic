/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_ptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victgonz <victgonz@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 18:04:21 by victgonz          #+#    #+#             */
/*   Updated: 2023/02/12 23:22:08 by victgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int func_ptr(s_Main *var, va_list list)
{
    int i;

	i = 0;
    while (i < var->num_conv) {
        if (var->current_ptr->conv == var->arr_func[i].op)
			return ((*(var->arr_func[i].ptr))(list, var->current_ptr));
        i++;
    }
    return (0);
}