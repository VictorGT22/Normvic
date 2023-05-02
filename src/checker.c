/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:16:44 by vics              #+#    #+#             */
/*   Updated: 2023/04/30 15:03:38 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normez.h"

unsigned int	check_header(s_variables *var, lst_dir *lst, int *add_i)
{
	int i;
	int len;
	int line;
	bool error;

	error = false;
	i = *add_i;
	while (lst->info[i] && i < 11)
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
	if (error)
	{
		print_error(lst->path, ERROR_HEADER, line + 1, 1);
		lst->no_error = false;
	}
	*add_i = i;
}

void	remove_last_spaces(s_variables *var, lst_dir *lst, int i)
{
	int j;
	int line;

	line = 0;
	j = ft_strlen(lst->info[i]) - 1;
	if (lst->info[i][j] == '\n')
	{
		lst->info[i][j] = '\0';
		j--;
	}
	while(j >= 0 && (lst->info[i][j] == ' ' || lst->info[i][j] == '\t'))
	{
		if (line == 0)
		{
			line = i;
			print_error(lst->path, ERROR_TRALING_SPACE, line + 1, 2);
		}
		lst->info[i][j] = '\0';
		j--;
	}
	if (!ft_strchr(lst->info[i], '\n'))
		lst->info[i][j + 1] = '\n';
}

int	check_name_prototipe(s_variables *var, lst_dir *lst, int j, int i)
{
	if (lst->info[i][j] == ' ')
	{
		lst->info[i][j] = '\t';
		print_error(lst->path, ERROR_WRONG_SPACE, i + 1, 1);
	}
	while (j >= 0 && (lst->info[i][j] == ' ' || lst->info[i][j] == '\t'))
		j--;
	while (j >= 0 && lst->info[i][j] != ' ' && lst->info[i][j] != '\t')
		j--;
	if (lst->info[i][j] == '\t')
	{
		lst->info[i][j] = ' ';
		print_error(lst->path, ERROR_WRONG_TAB, i + 1, 1);
	}
	return (j);
}

void	remove_extra_spaces(s_variables *var, lst_dir *lst, int i)
{
	int j;
	int	x;
	char *str;
	
	j = 0;
	x = 0;
	str = malloc(sizeof(char) * ft_strlen(lst->info[i]) + 1);
	ft_bzero(str, ft_strlen(lst->info[i]) + 1);
	while (lst->info[i][j] && (lst->info[i][j] == ' ' || lst->info[i][j] == '\t'))
		j++;
	while (lst->info[i][j])
	{
		if ((lst->info[i][j] != ' ' && lst->info[i][j] != '\t')
		|| (lst->info[i][j + 1] != ' ' && lst->info[i][j + 1] != '\t'))
			str[x++] = lst->info[i][j];
		j++;
	}
	free(lst->info[i]);
	lst->info[i] = str;
}

void	remove_extra_spaces_2(s_variables *var, lst_dir *lst, int i)
{
	int j;
	int	x;
	char *str;
	
	j = 0;
	x = 0;
	str = malloc(sizeof(char) * ft_strlen(lst->info[i]) + 1);
	ft_bzero(str, ft_strlen(lst->info[i]) + 1);
	while (lst->info[i][j])
	{
		if ((lst->info[i][j] != ' ' && lst->info[i][j] != '\t')
		|| (lst->info[i][j + 1] != ' ' && lst->info[i][j + 1] != '\t'))
			str[x++] = lst->info[i][j];
		j++;
	}
	free(lst->info[i]);
	lst->info[i] = str;
}

void	remove_mid_spaces(s_variables *var, lst_dir *lst, int i)
{
	int j;
	int	x;
	char *str;
	
	j = 0;
	x = 0;
	str = malloc(sizeof(char) * ft_strlen(lst->info[i]) + 1);
	ft_bzero(str, ft_strlen(lst->info[i]) + 1);
	while (lst->info[i][j])
	{
		if ((lst->info[i][j] != ' ' && lst->info[i][j] != '\t')
		|| (lst->info[i][j + 1] != ' ' && lst->info[i][j + 1] != '\t'))
			str[x++] = lst->info[i][j];
		j++;
	}
	free(lst->info[i]);
	lst->info[i] = str;
}

void	add_void(s_variables *var, lst_dir *lst, int i, bool empty)
{
	int j;
	int len;
	char *str;
	
	j = 0;
	if (empty)
	{
		len =  ft_strlen(lst->info[i]);
		str = malloc(sizeof(char) * len + 5);
		ft_bzero(str, len + 5);
		while (lst->info[i][j] && lst->info[i][j] != '(')
		{
			str[j] = lst->info[i][j];
			j++;
		}
		ft_strlcat(str, "(void)\n", len + 6);
		free(lst->info[i]);
		lst->info[i] = str;
	}
}

void	check_prototipe_func(s_variables *var, lst_dir *lst, int i)
{
	int 	j;
	bool	error;
	bool	empty;
	int 	bracket;

	bracket = 0;
	error = false;
	empty = true;
	j = ft_strlen(lst->info[i]);
	printf("proto: %s\n", lst->info[i]);
	while (j >= 0)
	{
		if (lst->info[i][j] == '\t' && bracket > 0)
		{
			lst->no_error = false;
			lst->info[i][j] = ' ';
			if (!error)
				print_error(lst->path, ERROR_WRONG_TAB, i + 1, 1);
			error = true;
		}
		if (lst->info[i][j] != ' ' && lst->info[i][j] != '\t' && lst->info[i][j] != '(' && bracket == 1)
			empty = false;
		if (lst->info[i][j] == ')')
			bracket++;
		else if (lst->info[i][j] == '(')
			bracket--;
		if (lst->info[i][j] == '(' && bracket == 0 && (lst->info[i][j - 1] == ' ' || lst->info[i][j - 1] == '\t'))
		{
			print_error(lst->path, ERROR_SPACE_NAME_FUNC, i + 1, 1);
			j--;
		}
		else if (bracket == 0 && (lst->info[i][j] == ' ' || lst->info[i][j] == '\t'))
			j = check_name_prototipe(var, lst, j, i);
		j--;
	}
	add_void(var, lst, i, empty);
}

void	check_variables(s_variables *var, lst_dir *lst, int i)
{
	int j;
	int	start;
	
	j = 0;
	while (lst->info[i][j])
	{
		j++;
	}
}

int	inside_function(s_variables *var, lst_dir *lst, int *add_i)
{
	int i;
	int	first_line;
	bool check_var;
	int len;
	
	i = *add_i;
	check_var = true;
	first_line = i;
	printf("linea: %d\n", i);
	check_prototipe_func(var, lst, i - 1);
	remove_extra_spaces(var, lst, i - 1);
	//while (lst->info[i] && )
	//	i++;
	
	while (lst->info[i] && lst->num_key != 0)
	{
		remove_last_spaces(var, lst, i);
		len = ft_strlen(lst->info[i]);
		if (ft_strnstr(lst->info[i], "}", len))
			lst->num_key--;
		if (check_var)
			check_variables(var, lst, i);
		
		i++;
	}
	return (i);
}

void	find_functions(s_variables *var, lst_dir *lst, int *add_i)
{
	int i;
	int len;
	int line;
	int	num_brackets;
	
	i = *add_i;
	lst->num_key = 0;
	while (lst->info[i])
	{
		len = 0;
		remove_last_spaces(var, lst, i);
		len = ft_strlen(lst->info[i]);
		if (ft_strnstr(lst->info[i], "{", len))
		{
			lst->num_key++;
			if (lst->num_key == 1)
				i = inside_function(var, lst, &i);
		}
		i++;
	}
	
}

void	check_errors(s_variables *var, lst_dir *lst)
{
	int i;

	i = 0;
	check_header(var, lst, &i);
	find_functions(var, lst, &i);
}

/*
__attribute__((constructor))
{
	
}*/