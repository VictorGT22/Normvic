/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victgonz <victgonz@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:29:11 by victgonz          #+#    #+#             */
/*   Updated: 2023/02/10 08:22:03 by victgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include "struct.h"
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <ctype.h>
# include <stdlib.h>
# include <math.h>
# include <stdint.h>

int		ft_printf(const char *str, ...);

int		ft_myputstr(char *str, t_list *info);
int		is_in_arr(char **arr, char *to_find);
void	ft_arrset(char **arr, char *str, int len);

//putnbr_base
void	ft_itoa_base(unsigned long int nb, char *base, char *arr, int *i);
void	ft_putnbr_base(long int nb, char *base);
void	ft_putnbr_base_l(unsigned long int nb, char *base);
void	ft_len_nbr_base(long long int nb, char *base, int *len);
void	ft_len_nbr_base_u(unsigned long int nb, char *base, int *len);
void	func_flag_length(va_list list, t_list *info, char *base);
void	ft_putnbr_base_u(unsigned long long int nb, char *base);

//std functions
int		ft_nbrlen(long long int nb);
void	write_width(int width);
int		ft_ptrlen(uintptr_t num);
void	put_c_num(char c, int n);

char	**str_word_arr(char *str, char sep);
int		func_ptr(s_Main *var, va_list list);
int		get_params(s_Main *var, char *str, va_list list);
void	fill_operations(s_fnc_ptr *operations);
void	ft_putnbr_base_ll(long long int nb, char *base);

//free
void	free_all(s_Main *var);

//GET INFO
void	get_parameter(s_Main *var, char *str, int *add_i);
void	get_width(s_Main *var, char *str, int *add_i);
void	get_precision(s_Main *var, char *str, int *i);
int		get_flags(s_Main *var, char *str, int *i);
int		get_params(s_Main *var, char *str, va_list list);

int		flag_sign(long long int nbr, t_list *info);
int		get_exponent(double *num);
void	print_decimal_part(long num, double decimal, t_list *info, char *base);
void	write_exp(int exp);
void	ft_putptr(uintptr_t num, char *base);
//functions flags
int		func_s(va_list list, t_list *info);
int		func_S(va_list list, t_list *info);
int		func_p(va_list list, t_list *info);
int		func_d(va_list list, t_list *info);
int		func_D(va_list list, t_list *info);
int		func_o(va_list list, t_list *info);
int		func_O(va_list list, t_list *info);
int		func_u(va_list list, t_list *info);
int		func_U(va_list list, t_list *info);
int		func_x(va_list list, t_list *info);
int		func_X(va_list list, t_list *info);
int		func_c(va_list list, t_list *info);
int		func_C(va_list list, t_list *info);
int		func_module(va_list list, t_list *info);
int		func_e(va_list list, t_list *info);
int		func_E(va_list list, t_list *info);
int		func_f(va_list list, t_list *info);
int		func_F(va_list list, t_list *info);
int		func_g(va_list list, t_list *info);
int		func_G(va_list list, t_list *info);
int		func_a(va_list list, t_list *info);
int		func_A(va_list list, t_list *info);
int		func_n(va_list list, t_list *info);
int		func_b(va_list list, t_list *info);
int		func_r(va_list list, t_list *info);
int		func_k(va_list list, t_list *info);

#endif
