/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victgonz <victgonz@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:16:56 by victgonz          #+#    #+#             */
/*   Updated: 2023/02/12 23:25:21 by victgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	func_p(va_list list, t_list *info)
{
	int width;
	int total;
	unsigned long long ptr;

	total = 0;
	ptr = va_arg(list, unsigned long long);
	width = atoi(info->width) - (ft_ptrlen(ptr) + 2 + ft_is_inarr(info->flag, "+"));
	width = width < 0 ? 0 : width;
	if (width > 0 && !ft_is_inarr(info->flag, "-"))
		write_width(width);
	if (ft_is_inarr(info->flag, "+"))
		write(1, "+", 1);
	if (ptr == 0)
		total += write(1, "0x0", 3);
	else
	{
		total += write(1, "0x", 2);
		total += ft_ptrlen(ptr);
		ft_putptr(ptr, "0123456789abcdef");
	}
	if (width > 0 && ft_is_inarr(info->flag, "-"))
		write_width(width);
	return (width + total + ft_is_inarr(info->flag, "+"));
}
