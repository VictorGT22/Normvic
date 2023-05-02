/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_s_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victgonz <victgonz@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 09:57:19 by victgonz          #+#    #+#             */
/*   Updated: 2023/02/12 23:25:24 by victgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	func_c(va_list list, t_list *info)
{
	char c;
	int width;

	if (atoi(info->precision) > 0)
	{
		c = va_arg(list, int);
		width = atoi(info->width) - 1;
		if (width < 0)
			width = 0;
		if (width > 0 && !ft_is_inarr(info->flag, "-"))
			write_width(width);
		write(1, &c, 1);
		if (width > 0 && ft_is_inarr(info->flag, "-"))
			write_width(width);
		return (1 + width);
	}
	return (0);
}

int	func_C(va_list list, t_list *info)
{
	char c;
	int width;

	c = va_arg(list, int);
	width = atoi(info->width) - 1;
	if (width < 0)
		width = 0;
	if (width > 0 && !ft_is_inarr(info->flag, "-"))
		write_width(width);
	write(1, &c, 1);
	if (width > 0 && ft_is_inarr(info->flag, "-"))
		write_width(width);
	return (1 + width);
}

int	get_len(t_list *info, char *s)
{
	int len;

	if (ft_is_inarr(info->flag, ".") && !info->no_val_prec)
	{
		if (s && ft_strlen(s) < atoi(info->precision))
			len = ft_strlen(s);
		else if (!s && 6 <= atoi(info->precision))
			len = 6;
		else if(!s)
			len = 0;
		else
			len = atoi(info->precision);
	}
	else if(ft_is_inarr(info->flag, ".") && info->no_val_prec)
		len = 0;
	else
	{
		if (s)
			len = ft_strlen(s);
		else
			len = 6;
	}
	return (len);
}

int	func_s(va_list list, t_list *info)
{
	char *s;
	int total;
	int width;
	int	len;

	s = va_arg(list, char *);
	len = get_len(info, s);
	width = atoi(info->width) - len;
	if (width < 0)
		width = 0;
	if (width > 0 && !ft_is_inarr(info->flag, "-"))
		write_width(width);
	if (s || !ft_is_inarr(info->flag, ".") || len != 0)
		total = ft_myputstr(s, info);
	if (width > 0 && ft_is_inarr(info->flag, "-"))
		write_width(width);
	return (total + width);
}

int	func_S(va_list list, t_list *info)
{
	char *s;
	int total;
	int width;
	int	len;

	s = va_arg(list, char *);
	len = get_len(info, s);
	width = atoi(info->width) - len;
	if (width < 0)
		width = 0;
	if (width > 0 && !ft_is_inarr(info->flag, "-"))
		write_width(width);
	if (s || !ft_is_inarr(info->flag, ".") || len != 0)
		total = ft_myputstr(s, info);
	if (width > 0 && ft_is_inarr(info->flag, "-"))
		write_width(width);
	return (total + width);
}