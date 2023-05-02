/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victgonz <victgonz@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:40:42 by victgonz          #+#    #+#             */
/*   Updated: 2023/02/12 23:24:43 by victgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_parameter(s_Main *var, char *str, int *add_i)
{
	int	j;
	int	i = *add_i;
	int	start = *add_i;

	j = 0;
	var->current_ptr->parameter = malloc(sizeof(char) * 5);
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		var->current_ptr->parameter[j] = str[i];
		j++;
		i++;
	}
	var->current_ptr->parameter[j] = '\0';
	if (str[i] != '$')
	{
		var->current_ptr->parameter[0] = '\0';
		*add_i = start;
	}
	else
		*add_i = i + 1;
}

void	get_width(s_Main *var, char *str, int *add_i)
{
	int	j;
	int	i;

	j = 0;
	i = *add_i;
	var->current_ptr->width = malloc(sizeof(char) * 5);
	
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		var->current_ptr->width[j] = str[i];
		j++;
		i++;
	}
	if (str[i] == '*')
		var->current_ptr->width[j] = str[i++];
	var->current_ptr->width[j] = '\0';
	*add_i = i;
}

void	get_precision(s_Main *var, char *str, int *i)
{
	int	j;

	j = 0;
	if (str[*i] == '.')
	{
		*i += 1;
		while (str[*i] != '\0' && ft_isdigit(str[*i]))
		{
			var->current_ptr->precision[j] = str[*i];
			*i += 1;
			j++;
		}
		var->current_ptr->precision[j] = '\0';
		var->current_ptr->flag[var->current_ptr->num_flags] = ".";
		var->current_ptr->num_flags++;
	}
	else
		var->current_ptr->precision[0] = '\0';
}

int	ext_get_flags(s_Main *var, char *str, int *i, int j)
{
	if (str[*i] == var->flags[j][0]
	&& str[*i + 1] == var->flags[j][1])
	{
		var->current_ptr->flag[var->current_ptr->num_flags]
			= var->flags[j];
		var->current_ptr->num_flags++;
		var->current_ptr->flag[var->current_ptr->num_flags] = NULL;
		*i += 2;
		return (1);
	}
	return (0);
}

int	get_flags(s_Main *var, char *str, int *i)
{
	int	j;

	j = 0;
	if (str[*i] == str[*i + 1] && str[*i] != '-')
	{
		if (ext_get_flags(var, str, i, j))
			return (1);
	}
	while (var->flags[j] != NULL)
	{
		if (str[*i] == var->flags[j][0])
		{
			var->current_ptr->flag[var->current_ptr->num_flags]
				= var->flags[j];
			var->current_ptr->num_flags++;
			var->current_ptr->flag[var->current_ptr->num_flags] = NULL;
			*i += 1;
			return (1);
		}
		j++;
	}
	return (0);
}
