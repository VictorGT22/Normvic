/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_putnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victgonz <victgonz@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:46:27 by victgonz          #+#    #+#             */
/*   Updated: 2023/02/12 23:22:28 by victgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base_u(unsigned long long int nb, char *base)
{
	if (nb < 0)
	{
		nb *= -1;
		write(1, "-", 1);
	}
	if (nb >= (unsigned long long int)ft_strlen(base))
	{
		ft_putnbr_base_u(nb / (unsigned long long int)ft_strlen(base), base);
		ft_putnbr_base_u(nb % (unsigned long long int)ft_strlen(base), base);
	}
	if (nb < (unsigned long long int)ft_strlen(base))
		write(1, &base[nb], 1);
}

void	ft_putnbr_base(long int nb, char *base)
{

	if (nb >= ft_strlen(base))
	{
		ft_putnbr_base(nb / ft_strlen(base), base);
		ft_putnbr_base(nb % ft_strlen(base), base);
	}
	if (nb < ft_strlen(base))
		write(1, &base[nb], 1);
}

void	ft_itoa_base(unsigned long int nb, char *base, char *arr, int *i)
{
	if (nb >= (unsigned long int)ft_strlen(base))
	{
		ft_itoa_base(nb / ft_strlen(base), base, arr, i);
		ft_itoa_base(nb % ft_strlen(base), base, arr, i);
	}
	if (nb < (unsigned long int)ft_strlen(base))
	{
		arr[*i] = base[nb];
		arr[*i + 1] = '\0';
		*i += 1;
	}
}

void	ft_putnbr_base_l(unsigned long int nb, char *base)
{
	if (nb >= (unsigned long long int)ft_strlen(base))
	{
		ft_putnbr_base_l(nb / (unsigned long long int)ft_strlen(base), base);
		ft_putnbr_base_l(nb % (unsigned long long int)ft_strlen(base), base);
	}
	if (nb < (unsigned long long int)ft_strlen(base))
		write(1, &base[nb], 1);
}

void	ft_putnbr_base_ll(long long int nb, char *base)
{
	if (nb >= (long long int)ft_strlen(base))
	{
		ft_putnbr_base_ll(nb / (long long int)ft_strlen(base), base);
		ft_putnbr_base_ll(nb % (long long int)ft_strlen(base), base);
	}
	if (nb < (long long int)ft_strlen(base))
		write(1, &base[nb], 1);
}
