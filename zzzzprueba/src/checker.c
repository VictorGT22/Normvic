/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:16:44 by vics              #+#    #+#             */
/*   Updated: 2023/07/25 20:35:26 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normez.h"

void	correct_header_2(s_variables *var, lst_dir *lst, int *i)
{
	char *str;
	time_t tiempo_actual;
    struct tm *info_tiempo;
    char buffer[80];

	time(&tiempo_actual);
    info_tiempo = localtime(&tiempo_actual);
	strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S", info_tiempo);
	str = buffer;
	str = ft_strjoin(str, " by ");
	str = new_old_str(ft_strjoin(str, var->user), str);
	ft_strpop_interval(lst->info[7], 15, ft_strlen(str) + 14);
	lst->info[7] = new_old_str(ft_strjoin_accurate(lst->info[7], str, 14), lst->info[7]);
	ft_strpop_interval(lst->info[8], 15, ft_strlen(str) + 14);
	lst->info[8] = new_old_str(ft_strjoin_accurate(lst->info[8], str, 14), lst->info[8]);
	free(str);
}

void	correct_header(s_variables *var, lst_dir *lst, int *i)
{
	int x;
	char *str;

	x = 0;
	while (lst->info[x] && x < *i)
	{
		mark_empty_line(lst, x, true);
		x++;
	}
	x = 0;
	while (lst->info[x] && x <= 10)
	{
		lst->info = ft_add_str_arr(lst->info, var->header[x], x);
		x++;
	}
	str = ft_substr(lst->path, ft_strrchr_index(lst->path, '/') + 1, ft_strlen(lst->path) - ft_strrchr_index(lst->path, '/'));
	ft_strpop_interval(lst->info[3], 2, ft_strlen(str) + 1);
	lst->info[3] = new_old_str(ft_strjoin_accurate(lst->info[3], str, 5), lst->info[3]);
	free(str);
	str = ft_strdup(var->user);
	str = new_old_str(ft_strjoin(str, " <>"), str);
	str = new_old_str(ft_strjoin_accurate(str, var->user_email, ft_strlen(str) - 1), str);
	ft_strpop_interval(lst->info[5], 9, ft_strlen(str) + 8);
	lst->info[5] = new_old_str(ft_strjoin_accurate(lst->info[5], str, 9), lst->info[5]);
	free(str);
	correct_header_2(var, lst, i);
}

void	check_header(s_variables *var, lst_dir *lst, int *add_i)
{
	int i;
	int len;
	int line;
	bool error;

	error = false;
	i = *add_i;
	line = 0;
	while (lst->info[i] && i < 11
		&& ft_strstr_index_nocommented(lst->info[i], "/*", 0) != -1
		&& ft_strstr_index_nocommented(lst->info[i], "*/", 0) != -1)
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
			print_error(lst, ERROR_TRALING_SPACE, line + 1, SOLVABLE);
		}
		lst->info[i][j] = '\0';
		j--;
	}
	if (!ft_strchr(lst->info[i], '\n'))
	{
		lst->info[i][j + 1] = '\n';
	}
}

void	remove_btw_semicolon(s_variables *var, lst_dir *lst, int i)
{
	int j;
	int x;
	int line;

	line = 0;
	j = ft_strlen(lst->info[i]) - 3;
	while(j >= 0 && lst->info[i][j] !=  ')')
	{
		if (line == 0)
		{
			line = i;
			print_error(lst, ERROR_TRALING_SPACE, line + 1, SOLVABLE);
		}
		lst->info[i][j] = '\0';
		j--;
	}
	lst->info[i][j + 1] = ';';
	lst->info[i][j + 2] = '\n';
	lst->info[i][j + 3] = '\0';
}

int	check_name_prototipe(s_variables *var, lst_dir *lst, int j, int i)
{
	if (lst->info[i][j] == ' ')
	{
		lst->info[i][j] = '\t';
		print_error(lst, ERROR_WRONG_SPACE, i + 1, SOLVABLE);
	}
	while (j >= 0 && (lst->info[i][j] == ' ' || lst->info[i][j] == '\t'))
		j--;
	while (j >= 0 && lst->info[i][j] != ' ' && lst->info[i][j] != '\t')
		j--;
	if (lst->info[i][j] == '\t')
	{
		lst->info[i][j] = ' ';
		print_error(lst, ERROR_WRONG_TAB, i + 1, SOLVABLE);
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

bool	remove_mid_spaces(s_variables *var, lst_dir *lst, int i)
{
	int j;
	int	x;
	bool error;
	char *str;
	
	j = 0;
	x = 0;
	error = false;
	str = malloc(sizeof(char) * ft_strlen(lst->info[i]) + 1);
	ft_bzero(str, ft_strlen(lst->info[i]) + 1);
	while (lst->info[i][j])
	{
		if ((lst->info[i][j] != ' ' && lst->info[i][j] != '\t')
		|| (lst->info[i][j + 1] != ' ' && lst->info[i][j + 1] != '\t'))
			str[x++] = lst->info[i][j];
		else
			error = true;
		j++;
	}
	free(lst->info[i]);
	lst->info[i] = str;
	return (error);
}

bool	remove_mid_spaces_2(s_variables *var, lst_dir *lst, int i)
{
	int j;
	int	x;
	char c;
	bool error;
	char *str;
	
	j = 0;
	x = 0;
	error = false;
	str = malloc(sizeof(char) * ft_strlen(lst->info[i]) + 1);
	ft_bzero(str, ft_strlen(lst->info[i]) + 1);
	while (lst->info[i][j] && (lst->info[i][j] == ' ' || lst->info[i][j] == '\t'))
		str[x++] = lst->info[i][j++];
	while (lst->info[i][j])
	{
		if (lst->info[i][j] == '\'' || lst->info[i][j] == '"')
		{
			c = lst->info[i][j];
			str[x++] = lst->info[i][j++];
			while (lst->info[i][j] && lst->info[i][j] != c)
				str[x++] = lst->info[i][j++];
			str[x++] = lst->info[i][j++];
		}
		if ((lst->info[i][j] != ' ' && lst->info[i][j] != '\t')
		|| (lst->info[i][j + 1] != ' ' && lst->info[i][j + 1] != '\t'))
			str[x++] = lst->info[i][j];
		else
			error = true;
		j++;
	}
	free(lst->info[i]);
	lst->info[i] = str;
	return (error);
}

char	*add_void(s_variables *var, lst_dir *lst, int i, bool empty, bool proto)
{
	int j;
	int len;
	char *str;
	
	j = 0;
	if (empty)
	{
		len =  ft_strlen(lst->info[i]);
		str = malloc(sizeof(char) * len + 10);
		ft_bzero(str, len + 10);
		while (lst->info[i][j] && lst->info[i][j] != '(')
		{
			str[j] = lst->info[i][j];
			j++;
		}
		ft_strlcat(str, "(void)", len + 6);
		if (proto)
			ft_strlcat(str, ";\n", len + 8);
		else
			ft_strlcat(str, "\n", len + 7);
		free(lst->info[i]);
		print_error(lst, ERROR_VOID, i + 1, SOLVABLE);
		return (str);
	}
	return (lst->info[i]);
}

int	check_prototipe_func(s_variables *var, lst_dir *lst, int i, bool proto, int prev_aligment)
{
	int 	j;
	int		x;
	char	*str;
	bool	empty;

	empty = false;
	j = ft_strchr_nocomented(lst->info[i], '(');
	if (ft_replace_chrchr(&lst->info[i][j + 1], '\t', ' '))
		print_error(lst, ERROR_WRONG_TAB, i + 1, SOLVABLE);
	x = ft_strrchr_index(lst->info[i], ')');
	if (ft_empty_until_pos(&lst->info[i][j + 1], (x - 1) - (j + 1)))
		empty = true;
	x = j;
	j--;
	while (j >= 0 && ft_isspace(lst->info[i][j]))
		j--;
	while (j >= 0 && !ft_isspace(lst->info[i][j]))
		j--;
	if (lst->info[i][j] == ' ')
	{
		print_error(lst, ERROR_WRONG_SPACE, i + 1, SOLVABLE);
		lst->info[i][j] = '\t';
	}
	str = ft_substr(lst->info[i], j + 1, x - j - 1);
	if (!ft_str_islower(str))
	{
		print_error(lst, ERROR_FUNC_NAME, i + 1, SOLVABLE);
		ft_str_tolower(str);
		ft_strpop_interval(lst->info[i], j + 1, x - 1);
		new_old_str(ft_strjoin_accurate(lst->info[i], str, j + 1), lst->info[i]);
	}
	free(str);
	lst->info[i] = add_void(var, lst, i, empty, proto);
	int aligment = get_real_hor_pos(lst->info[i]);
	if (aligment != prev_aligment && prev_aligment != -1)
		print_error(lst, ERROR_MISALIGNED_PROTO, i + 1, SOLVABLE);
	check_operators(var, lst, &i,  true);
	return (aligment);
}

void	check_variables(s_variables *var, lst_dir *lst, int i)
{
	int len;
	int end;
	int index;
	t_lst_arr *node;

	index = ft_strchr_nocomented(lst->info[i], '=');
	len = ft_strlen(lst->info[i]);
	if (index != -1)
	{
		end = index - 1;
		index -= 2;
		while (index >= 0 && lst->info[i][index] != ' ' && lst->info[i][index] != '\t')
			index--;
		node = new_node_arr(ft_substr(lst->info[i], index, len - index));
		lst->info[i] = new_old_str(ft_substr(lst->info[i], 0, len - (len - end)), lst->info[i]);
		lst->info[i] = new_old_str(ft_strjoin_accurate(lst->info[i], ";\n", ft_strlen(lst->info[i])), lst->info[i]);
		if (node)
			lstadd_back_arr(&var->var_bad_decl, node);
		print_error(lst, ERROR_VAR_ASIGNATION, i + 1, SOLVABLE);
	}
}

int	ft_strchr_nocomented(char *str, char c)
{
	int	i;
	int num_comment;
	char c_comment;

	i = 0;
	num_comment = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c_comment = str[i];
			num_comment++;
			i++;
		}
		while(str[i] && num_comment != 0)
		{
			if (str[i] == c_comment)
				num_comment--;
			i++;
		}
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	correct_ternarian_2(s_variables *var, lst_dir *lst, int *i)
{
	int index;
	int	index_condition;
	char *tabs;
	char *asignation;
	char *condition;
	char *action_1;
	char *action_2;


	int num_tabs = count_indentations(lst->info[*i]);

	printf("num tabs 222: %d\n", num_tabs);
	index = ft_strchr_nocomented(lst->info[*i], '(');
	asignation = ft_substr(lst->info[*i], 0, index + 1);
	index_condition = ft_strchr_nocomented(lst->info[*i], '?');
	condition = ft_substr(lst->info[*i], index + 1, index_condition - (index + 2));
	index = ft_strchr_nocomented(lst->info[*i], ':');
	action_1 = ft_substr(lst->info[*i], index_condition + 1, index - index_condition - 1);
	
	tabs = malloc(sizeof(char) * num_tabs + 1);
	ft_bzero(tabs, num_tabs + 1);
	ft_memset(tabs, '\t', num_tabs);
	
	index_condition = ft_strchr_nocomented(lst->info[*i], ';');
	action_2 = ft_substr(lst->info[*i], index + 1, index_condition - index - 1);

	condition = ft_strtrim(condition, " \t");
	condition = new_old_str(ft_strjoin_accurate(condition, "if (", 0), condition);
	condition = new_old_str(ft_strjoin_accurate(condition, ")\n", ft_strlen(condition)), condition);
	condition = new_old_str(ft_strjoin_accurate(condition, tabs, 0), condition);
	mark_empty_line(lst, *i, true);
	lst->info = ft_add_str_arr(lst->info, condition, *i);

	action_1 = ft_strtrim(action_1, " )");
	action_1 = new_old_str(ft_strjoin_accurate(action_1, asignation, 0), action_1);
	action_1 = new_old_str(ft_strjoin_accurate(action_1, "\t", 0), action_1);
	action_1 = new_old_str(ft_strjoin_accurate(action_1, ");\n", ft_strlen(action_1)), action_1);
	lst->info = ft_add_str_arr(lst->info, action_1, *i + 2);

	lst->info = ft_add_str_arr(lst->info, "else\n", *i + 3);
	lst->info[*i + 3] = new_old_str(ft_strjoin_accurate(lst->info[*i + 3], tabs, 0), lst->info[*i + 3]);
	
	action_2 = ft_strtrim(action_2, " )");
	action_2 = new_old_str(ft_strjoin_accurate(action_2, asignation, 0), action_2);
	action_2 = new_old_str(ft_strjoin_accurate(action_2, "\t", 0), action_2);
	action_2 = new_old_str(ft_strjoin_accurate(action_2, ");\n", ft_strlen(action_2)), action_2);
	lst->info = ft_add_str_arr(lst->info, action_2, *i + 4);

	//*i = *i + 1;
}

void	correct_ternarian_3(s_variables *var, lst_dir *lst, int *i)
{
	int index;
	int	index_condition;
	char *tabs;
	char *asignation;
	char *condition;
	char *action_1;
	char *action_2;

	asignation = NULL;
	int num_tabs = count_indentations(lst->info[*i]);

	
	index = ft_strchr_nocomented(lst->info[*i], '=');
	if (index != -1)
	{
		asignation = ft_substr(lst->info[*i], 0, index + 1);
		asignation = new_old_str(ft_strjoin_accurate(asignation, " ", index + 1), asignation);
	}
	index_condition = ft_strchr_nocomented(lst->info[*i], '?');
	condition = ft_substr(lst->info[*i], index + 1, index_condition - (index + 2));
	index = ft_strchr_nocomented(lst->info[*i], ':');
	action_1 = ft_substr(lst->info[*i], index_condition + 1, index - index_condition - 1);
	
	tabs = malloc(sizeof(char) * num_tabs + 1);
	ft_bzero(tabs, num_tabs + 1);
	ft_memset(tabs, '\t', num_tabs);
	
	index_condition = ft_strchr_nocomented(lst->info[*i], ';');
	action_2 = ft_substr(lst->info[*i], index + 1, index_condition - index - 1);
	
	condition = ft_strtrim(condition, " \t");
	condition = new_old_str(ft_strjoin_accurate(condition, "if (", 0), condition);
	condition = new_old_str(ft_strjoin_accurate(condition, ")\n", ft_strlen(condition)), condition);
	condition = new_old_str(ft_strjoin_accurate(condition, tabs, 0), condition);
	mark_empty_line(lst, *i, true);
	lst->info = ft_add_str_arr(lst->info, condition, *i);

	action_1 = ft_strtrim(action_1, " \t");
	if (asignation)
		action_1 = new_old_str(ft_strjoin_accurate(action_1, asignation, 0), action_1);
	else
		action_1 = new_old_str(ft_strjoin_accurate(action_1, tabs, 0), action_1);
	action_1 = new_old_str(ft_strjoin_accurate(action_1, "\t", 0), action_1);
	action_1 = new_old_str(ft_strjoin_accurate(action_1, ";\n", ft_strlen(action_1)), action_1);
	lst->info = ft_add_str_arr(lst->info, action_1, *i + 2);

	lst->info = ft_add_str_arr(lst->info, "else\n", *i + 3);
	lst->info[*i + 3] = new_old_str(ft_strjoin_accurate(lst->info[*i + 3], tabs, 0), lst->info[*i + 3]);
	
	action_2 = ft_strtrim(action_2, " \t");
	if (asignation)
		action_2 = new_old_str(ft_strjoin_accurate(action_2, asignation, 0), action_2);
	else
		action_2 = new_old_str(ft_strjoin_accurate(action_2, tabs, 0), action_2);
	action_2 = new_old_str(ft_strjoin_accurate(action_2, "\t", 0), action_2);
	action_2 = new_old_str(ft_strjoin_accurate(action_2, ";\n", ft_strlen(action_2)), action_2);
	lst->info = ft_add_str_arr(lst->info, action_2, *i + 4);
}