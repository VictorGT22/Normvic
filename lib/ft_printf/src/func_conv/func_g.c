/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_g.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victgonz <victgonz@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:37:20 by victgonz          #+#    #+#             */
/*   Updated: 2023/02/12 23:25:12 by victgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	precision_reduce(double num, int prec)
{
	char	*arr_num;
	int		i;

	i = 0;
	arr_num = malloc(sizeof(char) * ft_nbrlen(prec));
	ft_itoa_base(num, "0123456789", arr_num, &i);
	i = prec - 1;
	while (i >= 0 && arr_num[i] == '0')
		i--;
	return (prec - (i + 1));
}

void	get_lower_num(double num, t_list *info, char c)
{
	long	unit_part;
	double	deci_part;
	int		precision;
	int		exp;
	int		i;

	i = 0;
	precision = atoi(info->precision);
	ft_itoa_base(atoi(info->precision) - (precision_reduce(num,
				atoi(info->precision)) + 1), "0123456789", info->precision, &i);
	exp = get_exponent(&num);
	unit_part = num;
	deci_part = num - unit_part;
	print_decimal_part(unit_part, deci_part, info, "0123456789");
	write(1, &c, 1);
	write_exp(exp);
}

void get_lower_num2(double num, t_list *info)
{
	long	unit_part;
	double	deci_part;
	int		precision;
	int		i;

	i = 0;
	precision = atoi(info->precision);
	unit_part = num;
	deci_part = num - unit_part;
	if (atoi(info->precision) - ft_nbrlen(num) > 0)
	{
		ft_itoa_base(atoi(info->precision) - ft_nbrlen(num),
			"0123456789", info->precision, &i);
		print_decimal_part(unit_part, deci_part, info, "0123456789");
	}
	else
		ft_putnbr_base_l(num, "0123456789");
}

int	func_g(va_list list, t_list *info)
{
	int		exp;
	double	num;
	long	unit_part;
	double	deci_part;

	num = va_arg(list, double);
	unit_part = num;
	deci_part = num - unit_part;
	if (atoi(info->precision) < ft_nbrlen(unit_part))
		get_lower_num(num, info, 'e');
	else
		get_lower_num2(num, info);
	return (0);
}

int	func_G(va_list list, t_list *info)
{
	double	num;
	long	unit_part;
	double	deci_part;

	num = va_arg(list, double);
	unit_part = num;
	deci_part = num - unit_part;
	if (atoi(info->precision) < ft_nbrlen(unit_part))
		get_lower_num(num, info, 'E');
	else
		get_lower_num2(num, info);
	return (0);
}