/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dentro_carpeta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <victgonz>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 17:50:56 by                   #+#    #+#             */
/*   Updated: 2023/07/09 17:50:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	check_header(s_variables *var, lst_dir *lst, int *add_i)
{
	bool	error;
	int		i;
	int		len;
	int		line;

	error = false;
	i = *add_i;
	line = 0;
	error = false;
	while (lst->info[i] && i < 11
		&& ft_strstr_index_nocomented(lst->info[i], "/*", 0) != -1
		&& ft_strstr_index_nocomented(lst->info[i], "*/", 0) != -1)
	{
		len = ft_strlen(lst->info[i]);
		if ((!ft_strnstr(lst->info[i], "/*", len)
			|| !ft_strnstr(lst->info[i], "*/", len) || len != 81) && !error)
		{
			line = i;
			error = true;
		}
		i++;
	}
	if (error || i != 11)
	{
		print_error(lst, ERROR_HEADER, line + 1, SOLVABLE);
		correct_header(var, lst, &i);
		lst->no_error = false;
	}
	*add_i = i;
}
