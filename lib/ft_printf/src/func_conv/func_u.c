/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victgonz <victgonz@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:36:57 by victgonz          #+#    #+#             */
/*   Updated: 2023/02/12 23:25:30 by victgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	func_u(va_list list, t_list *info)
{
	int				len;
	unsigned int	nbr;
	unsigned int	nbr1;
	int				width;
	int				precision;

	precision = 0;
	width = 0;
	len = 0;
	nbr = va_arg(list, unsigned int);
	ft_len_nbr_base_u(nbr, "0123456789", &len);
	width = atoi(info->width);
	if (nbr == 0 && ft_is_inarr(info->flag, "."))
		len = 0;
	if (ft_is_inarr(info->flag, "+") && nbr >= 0)
		width -= 1;
	if (ft_is_inarr(info->flag, ".") && !info->no_val_prec)
	{
		precision = atoi(info->precision) - len;
		if (nbr < 0)
			precision++;
	}
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
	if (nbr < 0)
	{
		nbr *= -1;
		write(1, "-", 1);
	}
	else
		flag_sign(nbr, info);
	if (precision > 0)
		put_c_num('0', precision);
	if (width > 0 && !ft_is_inarr(info->flag, ".") && ft_is_inarr(info->flag, "0"))
		put_c_num('0', width + ft_is_inarr(info->flag, " "));
	if (nbr != 0 || !ft_is_inarr(info->flag, "."))
		ft_putnbr_base_l(nbr, "0123456789");
	if (width > 0 && ft_is_inarr(info->flag, "-"))
		write_width(width);
	if (ft_is_inarr(info->flag, " ") && nbr >= 0 && (!width || !precision))
		width += ft_is_inarr(info->flag, " ") && nbr1 >= 0 ? 1 : 0;
	width += ft_is_inarr(info->flag, "+") && nbr1 >= 0 ? 1 : 0;
	return (width + len + precision);
}

int	func_U(va_list list, t_list *info)
{
	int len;
	int total;
	unsigned long int nbr;
	int width;

	total = 0;
	len = 0;
	nbr = va_arg(list, unsigned long int);
	ft_len_nbr_base_u(nbr, "0123456789", &len);
	width = atoi(info->width) - len;
	width = width < 0 ? 0 : width;
	if (width > 0 && !ft_is_inarr(info->flag, "-"))
		write_width(width);
	ft_putnbr_base_u(nbr, "0123456789");
	if (width > 0 && ft_is_inarr(info->flag, "-"))
		write_width(width);
	return (width + len);
}