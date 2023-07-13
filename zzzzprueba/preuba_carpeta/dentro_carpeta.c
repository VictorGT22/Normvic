/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dentro_carpeta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:16:44 by vics              #+#    #+#             */
/*   Updated: 2023/07/13 21:46:46 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normez.h"

void	correct_line_long(s_variables *var, lst_dir *lst, int *i)
{
	int		index;
	int		tabs;
	char	*str;
	char	*str_tabs;

	tabs = count_indentations(lst->info[*i]);
	index = get_operator_divide(var, lst, i);
	if (index != 0)
	{
		str_tabs = malloc(sizeof(char) * tabs + 1);
		bzero(str_tabs, tabs + 1);
		ft_memset(str_tabs, '\t', tabs);
		str = ft_substr(lst->info[*i], index, ft_strlen(lst->info[*i]));
		str = ft_strjoin(str_tabs, str);
		lst->info = ft_add_str_arr(lst->info, str, *i + 1);
		lst->line_compensation++;
		ft_strpop_interval(lst->info[*i], index - 1, ft_strlen(lst->info[*i]) - 2);
		*i += 1;
	}
}
