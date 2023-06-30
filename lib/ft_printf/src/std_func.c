/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:19:54 by victgonz          #+#    #+#             */
/*   Updated: 2023/06/22 15:04:26 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fill_operations2(s_fnc_ptr *operations)
{
	operations[13].op = 'C';
	operations[13].ptr = &func_C;
	operations[14].op = '%';
	operations[14].ptr = &func_module;
	operations[15].op = 'e';
	operations[15].ptr = &func_e;
	operations[16].op = 'E';
	operations[16].ptr = &func_E;
	operations[17].op = 'f';
	operations[17].ptr = &func_f;
	operations[18].op = 'F';
	operations[18].ptr = &func_F;
	operations[19].op = 'g';
	operations[19].ptr = &func_g;
	operations[20].op = 'G';
	operations[20].ptr = &func_G;
	operations[21].op = 'a';
	operations[21].ptr = &func_a;
	operations[22].op = 'A';
	operations[22].ptr = &func_A;
	operations[23].op = 'n';
	operations[23].ptr = &func_n;
	operations[24].op = 'b';
	operations[24].ptr = &func_b;
	operations[25].op = 'r';
	operations[25].ptr = &func_r;
	operations[26].op = 'k';
	operations[26].ptr = &func_k;
	operations[27].op = 'p';
	operations[27].ptr = &func_p;
}

void	fill_operations(s_fnc_ptr *operations)
{
	operations[0].op = 's';
	operations[0].ptr = &func_s;
	operations[1].op = 'S';
	operations[1].ptr = &func_S;
	operations[2].op = 'S';
	operations[2].ptr = &func_S;
	operations[3].op = 'd';
	operations[3].ptr = &func_d;
	operations[4].op = 'D';
	operations[4].ptr = &func_D;
	operations[5].op = 'i';
	operations[5].ptr = &func_d;
	operations[6].op = 'o';
	operations[6].ptr = &func_o;
	operations[7].op = 'O';
	operations[7].ptr = &func_O;
	operations[8].op = 'u';
	operations[8].ptr = &func_u;
	operations[9].op = 'U';
	operations[9].ptr = &func_U;
	operations[10].op = 'x';
	operations[10].ptr = &func_x;
	operations[11].op = 'X';
	operations[11].ptr = &func_X;
	operations[12].op = 'c';
	operations[12].ptr = &func_c;
	fill_operations2(operations);
}

int	ft_myputstr(char *str, t_list *info)
{
	int i;
	int len;

	i = 0;
	if (str == NULL)
		str = "(null)";
	len = ft_is_inarr(info->flag, ".") ? atoi(info->precision) : ft_strlen(str);
	len = info->no_val_prec ? 0 : len;
	while (str[i] != '\0' && i < len)
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

void	ft_len_nbr_base(long long int nb, char *base, int *len)
{
	if (nb >= ft_strlen(base))
	{
		ft_len_nbr_base(nb / ft_strlen(base), base, len);
		ft_len_nbr_base(nb % ft_strlen(base), base, len);
	}
	if (nb < ft_strlen(base))
		*len += 1;
}

void	ft_len_nbr_base_u(unsigned long int nb, char *base, int *len)
{
	if (nb >= ft_strlen(base))
	{
		ft_len_nbr_base_u(nb / ft_strlen(base), base, len);
		ft_len_nbr_base_u(nb % ft_strlen(base), base, len);
	}
	if (nb < ft_strlen(base))
		*len += 1;
}