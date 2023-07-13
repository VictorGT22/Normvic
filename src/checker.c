/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:16:44 by vics              #+#    #+#             */
/*   Updated: 2023/07/13 15:04:27 by vics             ###   ########.fr       */
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

unsigned int	check_header(s_variables *var, lst_dir *lst, int *add_i)
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
			print_error(lst, ERROR_TRALING_SPACE, line + 1, SOLVABLE);
		}
		lst->info[i][j] = '\0';
		j--;
	}
	//printf("str: %s\n", lst->info[i]);
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
	j = ft_strrchr_index(lst->info[i], '(');
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
	lst->info[i] = add_void(var, lst, i, empty, proto);
	int aligment = get_real_hor_pos(lst->info[i]);
	if (aligment != prev_aligment && prev_aligment != -1)
		print_error(lst, ERROR_MISALIGNED_PROTO, i + 1, SOLVABLE);
	check_operators(var, lst, &i);
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

	action_1 = ft_strtrim(action_1, " )\t");
	action_1 = new_old_str(ft_strjoin_accurate(action_1, asignation, 0), action_1);
	action_1 = new_old_str(ft_strjoin_accurate(action_1, "\t", 0), action_1);
	action_1 = new_old_str(ft_strjoin_accurate(action_1, ");\n", ft_strlen(action_1)), action_1);
	lst->info = ft_add_str_arr(lst->info, action_1, *i + 2);

	lst->info = ft_add_str_arr(lst->info, "else\n", *i + 3);
	lst->info[*i + 3] = new_old_str(ft_strjoin_accurate(lst->info[*i + 3], tabs, 0), lst->info[*i + 3]);
	
	action_2 = ft_strtrim(action_2, " )\t");
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

void	correct_ternarian(s_variables *var, lst_dir *lst, int *i)
{
	int index;
	int num_tabs;
	int	index_condition;
	char *tabs;

	num_tabs = count_indentations(lst->info[*i - 1]) - count_indentations(lst->info[*i]);
	
	if (ft_strchr_nocomented(lst->info[*i - 1], '{') != -1 || is_keyword(var, lst, *i - 1, var->keywords) != 0)
		num_tabs++;
	if (num_tabs != 0)
	{
		tabs = malloc(sizeof(char) * num_tabs + 1);
		ft_bzero(tabs, num_tabs + 1);
		ft_memset(tabs, '\t', num_tabs);
		lst->info[*i] = new_old_str(ft_strjoin_accurate(lst->info[*i], tabs, 0), lst->info[*i]);	
	}
	index = ft_strchr_nocomented(lst->info[*i], '=');
	if (index != -1 && (lst->info[*i][index - 1] != ' ' || lst->info[*i][index + 1] != ' '))
		index = -1;
	if (index == -1)
	{
		index = ft_strchr_nocomented(lst->info[*i], '(');
		index_condition = ft_strchr_nocomented(lst->info[*i], '?');
		if (index == -1 || index > index_condition || ft_empty_until_pos(lst->info[*i], index - 1))
			correct_ternarian_3(var, lst, i);
		else
			correct_ternarian_2(var, lst, i);
	}
	else
		correct_ternarian_3(var, lst, i);
	*i = *i + 4;
}

bool	is_ternarian(lst_dir *lst, char *str, int *i)
{
	if (ft_strchr_nocomented(str, ';') != -1 && ft_strchr_nocomented(str, ':') != -1
	&& ft_strchr_nocomented(str, '?') != -1)
		return (true);
	return (false);
}

bool	is_var(char *str)
{
	int num;
	int brackets;
	int len;

	num = 0;
	brackets = 0;
	len = ft_strlen(str);
	if (ft_strchr_nocomented(str, ';') == -1 || (ft_strchr_nocomented(str, '=') != -1 && str[ft_strchr_nocomented(str, '=') - 1] != ' '))
		return (false);
	len = ft_strchr_nocomented(str, '=') != -1 ? ft_strchr_nocomented(str, '=') - 1 : ft_strchr_nocomented(str, ';');
	len--;
	while (str[len] == ' ' || str[len] == '\t')
		len--;
	while (len > 0)
	{
		if (str[len] == ')' || str[len] == '+' || str[len] == '-')
			return (false);
		if ((str[len] == ' ' || str[len] == '\t')
		&& (str[len - 1] != ' ' && str[len - 1] != '\t'))
			num++;
		len--;
	}
	if (num == 0)
		return (false);
	return (true);
}

char	*new_old_str(char *new, char *old)
{
	char *str_new;

	free(old);
	str_new = ft_strdup(new);
	free(new);
	return (str_new);
}

int	operator_start(lst_dir *lst, int *i, int lower)
{
	int x;

	x = lower - 1;
	while (x >= 0)
	{
		if (lst->info[*i][x] != ' ' && lst->info[*i][x] != '\t')
			return (0);
		x--;
	}
	return (1);
}

int	operator_end(lst_dir *lst, int *i, int lower, char *op)
{
	int x;
	int len;

	len = ft_strlen(op);
	x = lower + len;
	if (!ft_strcmp(op, "/*") || !ft_strcmp(op, "*/") || !ft_strcmp(op, "//"))
		return (0);
	while (lst->info[*i][x])
	{
		if (lst->info[*i][x] != ' ' && lst->info[*i][x] != '\t' && lst->info[*i][x] != '\n')
			return (0);
		x++;
	}
	return (1);
}

void	confirmacion_replace(s_variables *var)
{
	char confirmation;

	blue();
	printf("Are you sure you want to fix the errors?\t");
	reset();
	printf("(Y : N)\n");
	scanf("%s", &confirmation);
	if (confirmation != 'y' && confirmation != 'Y')
		var->flags->replace = false;
}

void	grade_the_app(s_variables *var)
{
	char rate;

	while (true)
	{
		blue();
		printf("Rate the app.\t");
		reset();
		printf("(0 - 5)\n");
		scanf(" %c", &rate);
		if (rate >= '0' && rate <= '5')
			break;
	}
	green();
	printf("We don't care your opinion, keep working on 42 projects.\n\n");
}

int	remove_comment(lst_dir *lst, int lower, int *i, char *op)
{
	bool	long_comment;
	int index;

	long_comment = false;
	while (lower - 1 >= 0 && (lst->info[*i][lower - 1] == ' ' ||  lst->info[*i][lower - 1] == '\t'))
		lower--;
	index = ft_strstr_index_nocommented(lst->info[*i], "*/", 0);
	if (!ft_strcmp(op, "/*") && index == -1)
		long_comment = true;
	if (operator_start(lst, i, lower))
	{
		if (!ft_strcmp(op, "//") || (index != -1 && lst->info[*i][index + 2] == '\n') || index == -1)
			mark_empty_line(lst, *i, true);
		else if (index != -1)
			ft_strpop_interval(lst->info[*i], lower, index + 1);
	}
	else
	{
		ft_strpop_interval(lst->info[*i], lower, ft_strlen(lst->info[*i]) - 2);
	}
	while (long_comment)
	{
		*i = *i + 1;
		index = ft_strstr_index_nocommented(lst->info[*i], "*/", 0);
		if (index != -1)
		{
			long_comment = false;
			if (lst->info[*i][index + 2] == '\n')
				mark_empty_line(lst, *i, true);
			else
				ft_strpop_interval(lst->info[*i], 0, index + 1);
		}
		else
			mark_empty_line(lst, *i, true);
	}
}

int	check_spaces_operator(s_variables *var, lst_dir *lst, int *i, int op, int lower)
{
	int x;
	int space;
	int len;

	x = 0;
	space = 0;
	len = ft_strlen(var->operators[op]);
	if (!ft_strcmp(var->operators[op], "++") || !ft_strcmp(var->operators[op], "--"))
	{
		if (lst->info[*i][lower - 1] == ' ' || lst->info[*i][lower - 1] == '\t')
		{
			ft_strpop_pos(lst->info[*i], lower - 1);
			print_error(lst, ERROR_SPACE_BEFORE_INCREMENTAL, *i + 1, SOLVABLE);
			space++;
		}
		if (lst->info[*i][lower + len - space] == ' ' || lst->info[*i][lower + len - space] == '\t')
		{
			ft_strpop_pos(lst->info[*i], lower + len - space);
			print_error(lst, ERROR_SPACE_AFTER_INCREMENTAL, *i + 1, SOLVABLE);
			space++;
		}
	}
	else if (!ft_strcmp(var->operators[op], "->") || !ft_strcmp(var->operators[op], "."))
	{
		if (!operator_start(lst, i, lower) && lst->info[*i][lower - 1] == ' ' || lst->info[*i][lower - 1] == '\t')
		{
			ft_strpop_pos(lst->info[*i], lower - 1);
			print_error(lst, ERROR_SPACE_BEFORE_STRUCT_OPERATOR, *i + 1, SOLVABLE);
			space++;
		}
		if (lst->info[*i][lower + len - space] == ' ' || lst->info[*i][lower + len] == '\t')
		{
			ft_strpop_pos(lst->info[*i], lower + len - space);
			print_error(lst, ERROR_SPACE_AFTER_STRUCT_OPERATOR, *i + 1, SOLVABLE);
			space++;
		}
	}
	else if (!ft_strcmp(var->operators[op], "//") || !ft_strcmp(var->operators[op], "/*")
	|| !ft_strcmp(var->operators[op], "*/"))
	{
		if (!ft_strcmp(var->operators[op], "//") || !ft_strcmp(var->operators[op], "/*"))
		{
			print_error(lst, ERROR_COMMENT_FUNCTION, *i + 1, 3);
			remove_comment(lst, lower, i, var->operators[op]);
			space--;
		}
	}
	else if (!ft_strcmp(var->operators[op], "(") || !ft_strcmp(var->operators[op], ")") || !ft_strcmp(var->operators[op], ";"))
	{
		int pos_keyword = is_keyword(var, lst, *i, var->keywords);
		int len = pos_keyword != 0 ? ft_strlen(var->keywords[type_keyword(var, lst, *i, var->keywords)]) : 0;

		if (!ft_strcmp(var->operators[op], "(") && (lst->info[*i][lower - 1] == ' '	|| lst->info[*i][lower - 1] == '\t') && (pos_keyword == 0 || (pos_keyword + 1 + len) != lower) && ft_isalnum(lst->info[*i][lower - 2]))
		{
			ft_strpop_pos(lst->info[*i], lower - 1);
			print_error(lst, ERROR_SPACE_FUNCTION, *i + 1, SOLVABLE);
			space++;
		}
		else if (!ft_strcmp(var->operators[op], "(") && (lst->info[*i][lower + 1] == ' ' || lst->info[*i][lower + 1] == '\t'))
		{
			ft_strpop_pos(lst->info[*i], lower + 1);
			print_error(lst, ERROR_SPACE_AFTER_PARENTHESIS, *i + 1, SOLVABLE);
			space++;
		}
		else if (((!operator_start(lst, i, lower) && !ft_strcmp(var->operators[op], ")")) || (!ft_strcmp(var->operators[op], ";") && pos_keyword == 0)) && (lst->info[*i][lower - 1] == ' ' || lst->info[*i][lower - 1] == '\t'))
		{
			ft_strpop_pos(lst->info[*i], lower - 1);
			!ft_strcmp(var->operators[op], ")") ? print_error(lst, ERROR_SPACE_BEFORE_PARENTHESIS, *i + 1, SOLVABLE) : print_error(lst, ERROR_SPACE_BEFORE_SEMICOLON, *i + 1, SOLVABLE);
			space++;
		}
	}
	else if (!ft_strcmp(var->operators[op], "[") || !ft_strcmp(var->operators[op], "]"))
	{
		if (!operator_start(lst, i, lower) && (!ft_strcmp(var->operators[op], "[") || !ft_strcmp(var->operators[op], "]")) && (lst->info[*i][lower - 1] == ' ' || lst->info[*i][lower - 1] == '\t'))
		{
			ft_strpop_pos(lst->info[*i], lower - 1);
			print_error(lst, ERROR_SPACE_BEFORE_BRACKETS, *i + 1, SOLVABLE);
			space++;
		}
		if (!ft_strcmp(var->operators[op], "[") && (lst->info[*i][lower + 1 - space] == ' ' || lst->info[*i][lower + 1 - space] == '\t'))
		{
			ft_strpop_pos(lst->info[*i], lower + 1 - space);
			print_error(lst, ERROR_SPACE_AFTER_BRACKETS, *i + 1, SOLVABLE);
			space++;
		}
	}
	else if (!ft_strcmp(var->operators[op], ","))
	{
		if (!operator_start(lst, i, lower) && lst->info[*i][lower - 1] == ' ' || lst->info[*i][lower - 1] == '\t')
		{
			ft_strpop_pos(lst->info[*i], lower - 1);
			print_error(lst, ERROR_SPACE_BEFORE_COMMA, *i, SOLVABLE);
			space++;
		}
		if (lst->info[*i][lower + 1 - space] != ' ')
		{
			if (lst->info[*i][lower + 1 - space] == '\t')
				lst->info[*i][lower + 1 - space] = ' ';
			else
				lst->info[*i] = new_old_str(ft_strjoin_accurate(lst->info[*i], " ", lower + 1 - space), lst->info[*i]);
			print_error(lst, ERROR_SPACE_AFTER_COMMA, *i, SOLVABLE);
			space--;
		}	
	}
	else if (ft_strcmp(var->operators[op], "//") != 0 && ft_strcmp(var->operators[op], "/*") != 0)
	{
		if (!operator_start(lst, i, lower) && lst->info[*i][lower - 1] != ' ' && lst->info[*i][lower - 2] != '=')
		{
			print_error(lst, ERROR_NO_SPACE_BEFORE_OPERATOR, *i + 1, SOLVABLE);
			space++;
			lst->info[*i] = new_old_str(ft_strjoin_accurate(lst->info[*i], " ", lower), lst->info[*i]);
		}
		if (lst->info[*i][lower + len + space] != ' ' && lst->info[*i][lower - 2] != '=')
		{
			print_error(lst, ERROR_NO_SPACE_AFTER_OPERATOR, *i + 1, SOLVABLE);
			lst->info[*i] = new_old_str(ft_strjoin_accurate(lst->info[*i], " ", lower + len + space), lst->info[*i]);
			space--;
		}
	}
	return (space);
}

void	check_operators(s_variables *var, lst_dir *lst, int *i)
{
	int x;
	int lower;
	int prev;
	int prev_len;
	int index;
	int op;

	prev = 0;
	lower = 0;
	prev_len = 0;
	while (lower != -1)
	{
		x = 0;
		lower = -1;
		op = -1;
		while (var->operators[x])
		{
			index = ft_strstr_index_nocommented(lst->info[*i], var->operators[x], prev + prev_len);
			if (index != -1 && (lower > index || lower == -1))
			{
				if ((prev + prev_len <= index)
				|| prev == 0)
				{
					lower = index;
					op = x;
				}
			}
			x++;
		}
		if (op != -1)
		{
			if (operator_end(lst, i, lower, var->operators[op])
				&& (ft_strcmp(var->operators[op], "(") != 0 && ft_strcmp(var->operators[op], ")") != 0)
				&& ft_strcmp(var->operators[op], ";") != 0 && ft_strcmp(var->operators[op], "]") != 0)
				print_error(lst, ERROR_OPPERATOR_END, *i + 1, SOLVABLE);
			else //&& (!operator_start(lst, i, lower) || !ft_strcmp(var->operators[op], "//") || !ft_strcmp(var->operators[op], "/*")))
				lower -= check_spaces_operator(var, lst, i, op, lower);
		}
		if (op != -1)
			prev_len = ft_strlen(var->operators[op]);
		prev = lower;

	}
}

int	is_keyword(s_variables *var, lst_dir *lst, int i, char **keywords)
{
	int x;
	int index;
	
	x = 0;
	while (keywords[x])
	{
		index = ft_strstr_index_nocommented(lst->info[i], keywords[x], 0);
		if (index != -1 && operator_start(lst, &i, index))
			return (index);
		x++;
	}
	return (0);
}

int	type_keyword(s_variables *var, lst_dir *lst, int i, char **keywords)
{
	int x;
	int index;
	
	x = 0;
	while (keywords[x])
	{
		index = ft_strstr_index_nocommented(lst->info[i], keywords[x], 0);
		if (index != -1)
			return (x);
		x++;
	}
	return (0);
}

void	check_keywords(s_variables *var, lst_dir *lst, int *i)
{
	int x;
	int index;

	x = 0;
	while (var->keywords[x])
	{
		index = ft_strstr_index_nocommented(lst->info[*i], var->keywords[x], 0);
		if (index != -1 && operator_start(lst, i, index))
		{
			index = index + ft_strlen(var->keywords[x]);
			if (lst->info[*i][index] != ' ' && !ft_isalpha(lst->info[*i][index]) && lst->info[*i][index] != '\n')
			{
				print_error(lst, ERROR_NO_SPACE_KEYWORD, *i + 1, SOLVABLE);
				lst->info[*i] =  new_old_str(
				ft_strjoin_accurate(lst->info[*i], " ", index), lst->info[*i]);
			}
		}
		x++;
	}
}

void	correct_line_bracket(s_variables *var, lst_dir *lst, int i, int index)
{
	char *str;
	int num_tabs;
	char *tabs_str;

	num_tabs = count_indentations(lst->info[i]);
	str = ft_substr(lst->info[i], index, ft_strlen(lst->info[i]));
	while (index >= 0 && (lst->info[i][index - 1] == ' ' || lst->info[i][index - 1] == '\t'))
		index--;
	lst->info[i][index] = '\n';
	lst->info[i][index + 1] = '\0';
	lst->info = ft_add_str_arr(lst->info, str, i + 1);
	lst->line_compensation++;
	tabs_str = malloc(sizeof(char) * num_tabs + 1);
	ft_bzero(tabs_str, num_tabs + 1);
	ft_memset(tabs_str, '\t', num_tabs);
	lst->info[i + 1] =  new_old_str(ft_strjoin_accurate(lst->info[i + 1], tabs_str, 0), lst->info[i + 1]);
	free(tabs_str);
}

bool	check_brackets(s_variables *var, lst_dir *lst, int i)
{
	int index;
	bool error;
	char *str;
	char *tabs_str;

	error = 0;
	index = ft_strchr_nocomented(lst->info[i], '{');
	if (index != -1)
	{
		if (!ft_empty_until_pos(lst->info[i], index - 1))
		{
			correct_line_bracket(var, lst, i, index);
			print_error(lst, ERROR_BRACKET_KEYWORD, i + 1, SOLVABLE);
			error = true;
		}
		else if (!ft_empty_line(&lst->info[i][count_indentations(lst->info[i]) + 1]))
		{
			correct_line_bracket(var, lst, i, index + 1);
			print_error(lst, ERROR_BRACKET_NOEMPTY, i + 1, SOLVABLE);
			error = true;
		}
		lst->num_bracket++;
	}
	index = ft_strchr_nocomented(lst->info[i], '}');
	if (index != -1)
	{
		if (!ft_empty_line(&lst->info[i][index + 1]))
		{
			correct_line_bracket(var, lst, i, index + 1);
			print_error(lst, ERROR_CLOSE_BRACKET_NOEMPTY, i + 1, SOLVABLE);
			error = true;
		}
		lst->num_bracket--;
	}
	return (error);
}

void	save_var_bad_line(s_variables *var, lst_dir *lst, int *i)
{
	char c;
	int index;
	t_lst_arr *node;

	index = ft_strchr_nocomented(lst->info[*i], '=');
	c = index != -1 ? ' ' : '\n';
	printf("str: %s\n", ft_substr(lst->info[*i], 0, ft_strchr_nocomented(lst->info[*i], c)));
	node = new_node_arr(ft_substr(lst->info[*i], 0, ft_strchr_nocomented(lst->info[*i], c)));
	if (index != -1)
		node->str = new_old_str(ft_strjoin_accurate(node->str, ";\n", ft_strlen(node->str)), node->str);
	else
		node->str = new_old_str(ft_strjoin_accurate(node->str, "\n", ft_strlen(node->str)), node->str);
	if (node)
		lstadd_back_arr(&var->var_bad_line, node);
	if (index == -1)
		mark_empty_line(lst, *i, true);
	else
		ft_strpop_interval(lst->info[*i], 1, 4);
}

void	correct_indentation(s_variables *var, lst_dir *lst, int i, int indentation)
{
	char *num_tabs;

	if (lst->indent > indentation && !ft_empty_line(lst->info[i]))
	{
		num_tabs = malloc(sizeof(char) * (lst->indent - indentation) + 2);
		ft_bzero(num_tabs, (lst->indent - indentation) + 2);
		memset(num_tabs, '\t', lst->indent - indentation);
		lst->info[i] = new_old_str(ft_strjoin_accurate(lst->info[i], num_tabs, 0), lst->info[i]);
		free(num_tabs);
		print_error(lst, ERROR_INDENTATION, i + 1, SOLVABLE);
	}
	else if (lst->indent < indentation && !ft_empty_line(lst->info[i]))
	{
		ft_strpop_interval(lst->info[i], 0, (indentation - lst->indent) - 1);
		print_error(lst, ERROR_INDENTATION, i + 1, SOLVABLE);
	}
}

int	count_indentations(char *str)
{
	int i;

	i = 0;
	while (str[i] == '\t' || str[i] == ' ')
	{
		if (str[i] == ' ')
			str[i] = '\t';
		i++;
	}
	return (i);
}

void	inside_keyword(s_variables *var, lst_dir *lst, int *i)
{
	int x;
	int pos_keyword;
	int num_brackets;
	char comment_open;
	int  indentation;

	pos_keyword = *i;
	num_brackets = -1;
	while (lst->info[*i] && num_brackets != 0)
	{
		x = 0;
		if (num_brackets == -1)
			num_brackets = 0;
		indentation = count_indentations(lst->info[*i]);
		if (pos_keyword < *i)
			indentation--;
		correct_indentation(var, lst, *i, indentation);
		while (lst->info[*i][x])
		{
			if (lst->info[*i][x] == '"' || lst->info[*i][x] == '\'')
			{
				comment_open = lst->info[*i][x];
				x++;
				while (lst->info[*i][x] && lst->info[*i][x] != comment_open)
					x++;
				x++;
			}
			if (lst->info[*i][x] == '(')
				num_brackets++;
			else if (lst->info[*i][x] == ')')
				num_brackets--;
			x++;
		}
		*i += 1;
	}
}

void	check_indentation(s_variables *var, lst_dir *lst, int i)
{
	int		pos;
	int		indentation;
	int		keyword_no_bracket;
	
	lst->indent = 1;
	lst->num_bracket = 1;
	keyword_no_bracket = 0;
	while (lst->info[i] && lst->num_bracket != 0)
	{
		if (keyword_no_bracket)
		{
			keyword_no_bracket = 0;
			lst->indent--;
		}
		if (ft_strchr_nocomented(lst->info[i], '}') != -1)
		{
			lst->num_bracket--;
			lst->indent--;
		}
		pos = is_keyword(var, lst, i, var->keywords_indent);
		if (pos != 0)
		{
			inside_keyword(var, lst, &i);
			if (ft_strchr_nocomented(lst->info[i], '{') != -1)
				keyword_no_bracket = 0;
			else
				keyword_no_bracket = 1;
			lst->indent++;
		}
		indentation = count_indentations(lst->info[i]);
		if (ft_strchr_nocomented(lst->info[i], '{') != -1)
		{
			lst->num_bracket++;
			indentation++;
		}
		if (ft_strcmp(lst->info[i], "@#~#@\n") != 0)
			correct_indentation(var, lst, i, indentation);
		i += 1;
	}
}

void	free_linked_arr(t_lst_arr **lst)
{
	t_lst_arr *temp;

	if (*lst)
	{
		while (*lst)
		{
			temp = *lst;
			(*lst) = (*lst)->next;
			free(temp);
		}
	}
}

int 	get_operator_divide(s_variables *var, lst_dir *lst, int *i)
{
	int x;
	int op;
	int prev;
	int lower;
	int index;

	lower = 0;
	prev = 0;
	while (lower != -1)
	{
		x = 0;
		lower = -1;
		while (var->op_divide[x])
		{
			index = ft_strstr_index_nocommented(lst->info[*i], var->op_divide[x], prev + 1);
			if (index != -1 && index <= 80 && (prev < index || prev == 0))
			{
				prev = index;
				lower = index;
				op = x;
				
			}
			x++;
		}
	}
	return (prev);	
}

void	correct_line_long(s_variables *var, lst_dir *lst, int *i)
{
	int index;
	int tabs;
	char *str;
	char *str_tabs;

	tabs = count_indentations(lst->info[*i]);
	index = get_operator_divide(var, lst, i);
	if (index != 0)
	{
		//if (is_keyword(var, lst, *i, var->keywords))
		//{
		//	printf("lina con keyword: %s\n", lst->info[*i]);
		//}	//tabs++;
		str_tabs = malloc(sizeof(char) * tabs + 1);
		bzero(str_tabs, tabs + 1);
		ft_memset(str_tabs, '\t', tabs);
		str = ft_substr(lst->info[*i], index, ft_strlen(lst->info[*i]));
		str = ft_strjoin(str_tabs, str);
		lst->info = ft_add_str_arr(lst->info, str, *i + 1);
		lst->line_compensation++;
		ft_strpop_interval(lst->info[*i], index - 1, ft_strlen(lst->info[*i]) - 2);
		//printf("%s\n", str);
		*i += 1;
	}
}

void	check_columns(s_variables *var, lst_dir *lst, int *i)
{
	int	num_columns;

	num_columns = 0; //get_real_hor_pos(lst->info[*i]);
	if (num_columns > 80) // linea muy larga
	{
		print_error_var(lst, ERROR_TO_LONG_LINE, *i + 1, NOSOLVABLE);
		printf("(");		 
		green();
		printf("80 ");		 
		reset();
		printf("-> ");		 
		red();
		printf("%d", num_columns);		 
		reset();
		printf(")");
		if (num_columns > 150)
		{
			red();
			printf("\tWTF R U CRAZY?");
			reset();
		}
		printf("\n\n");
		//correct_line_long(var, lst, i);
	}
}

void	inside_function(s_variables *var, lst_dir *lst, int *i)
{
	int max;
	bool followed_var;
	int	start;
	int	num_misaligned;
	int num_var;
	t_lst_arr *temp;
	bool error_empty;
	int index;
	int prev_aligment = -1;
	
	max = 0;
	error_empty = false;
	num_var = 0;
	lst->num_bracket = 0;
	lst->inside_comment = 0;
	start = *i + 1 + check_brackets(var, lst, *i);
	followed_var = is_var(lst->info[start]);
	check_prototipe_func(var, lst, *i - 1, false, -1); // revisar esto
	if (remove_mid_spaces(var, lst, *i - 1))
		print_error(lst, ERROR_MULTIPLE_SPACES, *i + 1, SOLVABLE);
	*i = start;
	if (ft_empty_line(lst->info[start]))
		print_error(lst, ERROR_WRONG_EMPTY_LINE, start + 1, SOLVABLE);
	while (lst->info[*i] && lst->num_bracket != 0)
	{
		check_brackets(var, lst, *i);
		check_columns(var, lst, i);
		if (!lst->info[*i + 1] && !ft_strchr(lst->info[*i], '\n'))
			print_error(lst, ERROR_ENTER_END_FILE, *i + 1, SOLVABLE);
		remove_last_spaces(var, lst, *i);
		if (is_var(lst->info[*i]) && !is_ternarian(lst, lst->info[*i], i))
		{
			num_var++;
			prev_aligment = correct_var(var, lst, i, prev_aligment);
			max = get_max(max, get_real_hor_pos(lst->info[*i]));
			if (!followed_var)
			{
				save_var_bad_line(var, lst, i);
				print_error(lst, ERROR_VARIBALES_FOLLOWED, *i + 1, SOLVABLE);
			}
			else
				check_variables(var, lst, *i);
		}
		else
		{
			if (remove_mid_spaces_2(var, lst, *i))
				print_error(lst, ERROR_MULTIPLE_SPACES, *i + 1, SOLVABLE);
			if (followed_var)
			{
				temp = var->var_bad_decl;
				while (temp) // ADD BAD DECLARATION VARIABLES (ASIGNATION AND DECLARATION)
				{
					lst->info = ft_add_str_arr(lst->info, temp->str, *i);
					lst->line_compensation++;
					temp = temp->next;
				}
			}
			else
			{
				check_operators(var, lst, i);
				check_keywords(var, lst, i);
			}
			followed_var = false;
		}
		*i += 1;
	}
	if (num_var > 5)
		print_error(lst, ERROR_MANY_VAR, start + 1, NOSOLVABLE);
	lst->num_bracket = 1;
	temp = var->var_bad_line;
	while (temp) // ADD BAD DECLARATION LINE VARIABLES (ASIGNATION AND DECLARATION)
	{
		lst->info = ft_add_str_arr(lst->info, temp->str, start);
		lst->line_compensation++;
		temp = temp->next;
	}
	lst->indent = 0;
	*i = start;
	followed_var = is_var(lst->info[*i]);
	while (lst->info[*i] && lst->num_bracket != 0)
	{
		check_brackets(var, lst, *i);
		if (is_var(lst->info[*i]) && !is_ternarian(lst, lst->info[*i], i))
		{
			num_misaligned =  get_real_hor_pos(lst->info[*i]);
			if (max > num_misaligned)
				correct_misaligned(lst, *i, max, num_misaligned);
		}
		else if (followed_var && !ft_empty_line(lst->info[*i]) && ft_strcmp(lst->info[*i], "@#~#@\n") != 0)
		{
			lst->info = ft_add_str_arr(lst->info, "\n", *i);
			lst->line_compensation++;
			print_error(lst, ERROR_NO_EMPTY_LINE_VAR, *i - 1, SOLVABLE);
			followed_var = false;
		}
		else if (!followed_var && ft_empty_line(lst->info[*i]))
			mark_empty_line(lst, *i, false);
		else
			followed_var = false;
		
		if (ft_strchr_nocomented(lst->info[*i], ';') != -1 && ft_strchr_nocomented(lst->info[*i], ':') != -1
			&& ft_strchr_nocomented(lst->info[*i], '?') != -1)
		{
			print_error(lst, ERROR_TERNARIAN, *i + 1, SOLVABLE);		
			//correct_ternarian(var, lst, i);
		}
		*i += 1;
	}	
	check_indentation(var, lst, start);
	free_linked_arr(&var->var_bad_decl);
	free_linked_arr(&var->var_bad_line);

	if (lst->info[*i])
	{
		if (!ft_empty_line(lst->info[*i]))
		{
			print_error(lst, ERROR_ENTER_FUNCTIONS, *i + 1, SOLVABLE);
			lst->info = ft_add_str_arr(lst->info, "\n", *i);
			lst->line_compensation++;
		}
	}
}

void	check_num_lines(lst_dir *lst, int num_lines, int line, int i)
{
	if (num_lines > 25)
	{
		print_error_var(lst, ERROR_NUM_LINES, line + 1, NOSOLVABLE);
		printf("(");		 
		green();
		printf("25 ");		 
		reset();
		printf("-> ");		 
		red();
		printf("%d", num_lines);		 
		reset();
		printf(")");
		if (num_lines > 50)
		{
			red();
			printf("\tWTF R U CRAZY?");
			reset();
		}
		printf("\n\n");
		
	}
}

void	check_errors(s_variables *var, lst_dir *lst)
{
	int i;
	int	len;
	bool error;
	bool empty;
	int empty_lines;
	int	num_lines;

	i = 0;
	empty_lines = 0;
	lst->num_bracket = 0;
	check_header(var, lst, &i);
	while (lst->info[i])
	{
		len = ft_strlen(lst->info[i]);
		remove_last_spaces(var, lst, i);
		empty = ft_empty_line(lst->info[i]);
		!empty ? empty_lines = 0 , error = 0 : empty_lines++;
		if (empty_lines > 1 || lst->info[i + 1] == NULL)
		{
			mark_empty_line(lst, i, error);
			error = true;
		}
		if (ft_strstr_index_nocommented(lst->info[i], "/*", 0) != -1)
		{
			while (lst->info[i] && ft_strstr_index_nocommented(lst->info[i], "*/", 0) == -1)
				i++;
		}
		if (ft_strstr_index_nocommented(lst->info[i], ";", 0) != -1)
			check_prototipe_func(var, lst, i, true, -1);
		if (ft_strnstr(lst->info[i], "{", len))
		{
			num_lines = i;
			inside_function(var, lst, &i);
			num_lines = i - num_lines;
			check_num_lines(lst, num_lines - 2, i - num_lines, i);	
			lst->num_functions++;
		}
		else
			i++;
	}
	if (lst->num_functions > 5)
	{
		print_error_var(lst, ERROR_NUM_FUNCTIONS, i + 1, NOSOLVABLE);
		printf("(");		 
		green();
		printf("5 ");		 
		reset();
		printf("-> ");		 
		red();
		printf("%d", lst->num_functions);		 
		reset();
		printf(")\n\n");
	}

}