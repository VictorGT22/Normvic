/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dentro_carpeta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:53:06 by vics              #+#    #+#             */
/*   Updated: 2023/05/15 09:32:28 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	check_errors(s_variables *var, lst_dir *lst)
{
	int		num;
	int		len;
	char	*brackets;

	num = 0;
	brackets = 0;
	len = ft_strlen(str);
	if (ft_strchr_nocomented(str, ';') == - 1)
		return (false);
	len = ft_strchr(str, '=') ? ft_chr_index(str, '=') - 2 : ft_chr_index(str, ';');
	while (len > 0)
	{
		if (str[len] == ')' || str[len] == '+' || str[len] == '-')
			return (false);
		if ((str[len] == ' ' || str[len] == '\t')
		 && (str[len - 1] != ' ' && str[len - 1] != '\t' && str[len - 1] != '\n'))
			num++;
		len--;
	}
		if (num == 0)
		return (false);
	return (true);
}
