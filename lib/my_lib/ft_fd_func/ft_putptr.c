/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victgonz <victgonz@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:25:51 by victgonz          #+#    #+#             */
/*   Updated: 2023/02/02 10:26:19 by victgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putptr(uintptr_t num, char *base)
{
	if (num >= 16)
	{
		ft_putptr(num / 16, base);
		ft_putptr(num % 16, base);
	}
	else
		ft_putchar_fd((base[num]), 1);
}
