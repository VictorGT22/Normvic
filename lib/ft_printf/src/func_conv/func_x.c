/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victgonz <victgonz@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 19:03:21 by victgonz          #+#    #+#             */
/*   Updated: 2023/02/12 23:25:34 by victgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	func_x(va_list list, t_list *info)
{
	int				len;
	int				total;
	unsigned int	nbr;
	int				width;
	int				precision;

	precision = 0;
	total = 0;
	len = 0;
	nbr = va_arg(list, unsigned int);
	ft_len_nbr_base(nbr, "0123456789abcdef", &len);
	width = atoi(info->width);
	if (nbr == 0 && ft_is_inarr(info->flag, "."))
		len = 0;
	if (ft_is_inarr(info->flag, "#"))
		width -= 2;
	if (ft_is_inarr(info->flag, ".") && !info->no_val_prec)
		precision = atoi(info->precision) - len;
	if (precision <= 0)
		width -= len;
	else
		width -= (precision + len);
	if (width < 0)
		width = 0;
	if (precision < 0)
		precision = 0;
	if (width > 0 && !ft_is_inarr(info->flag, "-") && (!ft_is_inarr(info->flag, "0") || ft_is_inarr(info->flag, ".")))
		write_width(width);
	if (ft_is_inarr(info->flag, " ") && nbr >= 0 && (!width || !precision))
		write(1, " ", 1);
	if (ft_is_inarr(info->flag, "#") && nbr != 0)
		total += write(1, "0x", 2);
	if (precision > 0)
		put_c_num('0', precision);
	if (width > 0 && !ft_is_inarr(info->flag, ".") && ft_is_inarr(info->flag, "0"))
		put_c_num('0', width + ft_is_inarr(info->flag, " "));
	if (nbr != 0 || !ft_is_inarr(info->flag, "."))
		ft_putnbr_base(nbr, "0123456789abcdef");
	if (width > 0 && ft_is_inarr(info->flag, "-") && !ft_is_inarr(info->flag, "0"))
		write_width(width);
	if (ft_is_inarr(info->flag, " ") && nbr >= 0 && (!width || !precision))
		width += ft_is_inarr(info->flag, " ") ? 1 : 0;
	width += ft_is_inarr(info->flag, "#") && nbr != 0 ? 2 : 0;
	return (width + len + precision);
}

int	func_X(va_list list, t_list *info)
{
	int len;
	int total;
	unsigned int nbr;
	int width;
	int precision = 0;

	total = 0;
	len = 0;
	nbr = va_arg(list, unsigned int);
	ft_len_nbr_base(nbr, "0123456789ABCDEF", &len);
	width = atoi(info->width);
	if (nbr == 0 && ft_is_inarr(info->flag, "."))
		len = 0;
	if (ft_is_inarr(info->flag, "#"))
		width -= 2;
	if (ft_is_inarr(info->flag, ".") && !info->no_val_prec)
		precision = atoi(info->precision) - len;
	if (precision <= 0)
		width -= len;
	else
		width -= (precision + len);
	if (width < 0)
		width = 0;
	if (precision < 0)
		precision = 0;
	if (width > 0 && !ft_is_inarr(info->flag, "-") && (!ft_is_inarr(info->flag, "0") || ft_is_inarr(info->flag, ".")))
		write_width(width);
	if (ft_is_inarr(info->flag, " ") && nbr >= 0 && (!width || !precision))
		write(1, " ", 1);
	if (ft_is_inarr(info->flag, "#") && nbr != 0)
		total += write(1, "0X", 2);
	if (precision > 0)
		put_c_num('0', precision);
	if (width > 0 && !ft_is_inarr(info->flag, ".") && ft_is_inarr(info->flag, "0"))
		put_c_num('0', width + ft_is_inarr(info->flag, " "));
	if (nbr != 0 || !ft_is_inarr(info->flag, "."))
		ft_putnbr_base(nbr, "0123456789ABCDEF");
	if (width > 0 && ft_is_inarr(info->flag, "-") && !ft_is_inarr(info->flag, "0"))
		write_width(width);
	if (ft_is_inarr(info->flag, " ") && nbr >= 0 && (!width || !precision))
		width += ft_is_inarr(info->flag, " ") ? 1 : 0;
	width += ft_is_inarr(info->flag, "#") && nbr != 0 ? 2 : 0;
	return (width + len + precision);
}