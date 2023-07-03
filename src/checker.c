/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:16:44 by vics              #+#    #+#             */
/*   Updated: 2023/07/03 14:52:24 by vics             ###   ########.fr       */
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
		print_error(lst->path, ERROR_HEADER, line + 1, LOW);
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
			print_error(lst->path, ERROR_TRALING_SPACE, line + 1, MEDIUM);
		}
		lst->info[i][j] = '\0';
		j--;
	}
	if (!ft_strchr(lst->info[i], '\n'))
		lst->info[i][j + 1] = '\n';
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
			print_error(lst->path, ERROR_TRALING_SPACE, line + 1, MEDIUM);
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
		print_error(lst->path, ERROR_WRONG_SPACE, i + 1, MEDIUM);
	}
	while (j >= 0 && (lst->info[i][j] == ' ' || lst->info[i][j] == '\t'))
		j--;
	while (j >= 0 && lst->info[i][j] != ' ' && lst->info[i][j] != '\t')
		j--;
	if (lst->info[i][j] == '\t')
	{
		lst->info[i][j] = ' ';
		print_error(lst->path, ERROR_WRONG_TAB, i + 1, MEDIUM);
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

void	remove_mid_spaces_2(s_variables *var, lst_dir *lst, int i)
{
	int j;
	int	x;
	char *str;
	
	j = 0;
	x = 0;
	str = malloc(sizeof(char) * ft_strlen(lst->info[i]) + 1);
	ft_bzero(str, ft_strlen(lst->info[i]) + 1);
	while (lst->info[i][j] && (lst->info[i][j] == ' ' || lst->info[i][j] == '\t'))
		str[x++] = lst->info[i][j++];
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

char	*add_void(s_variables *var, char *info, bool empty, bool proto)
{
	int j;
	int len;
	char *str;
	
	j = 0;
	if (empty)
	{
		len =  ft_strlen(info);
		str = malloc(sizeof(char) * len + 10);
		ft_bzero(str, len + 10);
		while (info[j] && info[j] != '(')
		{
			str[j] = info[j];
			j++;
		}
		ft_strlcat(str, "(void)", len + 6);
		if (proto)
			ft_strlcat(str, ";\n", len + 8);
		else
			ft_strlcat(str, "\n", len + 7);
		free(info);
		return (str);
	}
	return (info);
}

void	check_prototipe_func(s_variables *var, lst_dir *lst, int i, bool proto)
{
	int 	j;
	int		x;
	bool	error;
	bool	empty;
	int 	bracket;

	bracket = 0;
	error = false;
	empty = true;
	j = ft_strlen(lst->info[i]);
	while (j >= 0)
	{
		if (lst->info[i][j] == '\t' && bracket > 0)
		{
			lst->no_error = false;
			lst->info[i][j] = ' ';
			if (!error)
				print_error(lst->path, ERROR_WRONG_TAB, i + 1, LOW);
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
			x = j;
			j--;
			while (j >= 0 && lst->info[i][j] == ' ' || lst->info[i][j] == '\t')
				j--;
			j++;
			x = j;
			while (lst->info[i][x])
			{
				if (lst->info[i][x] != ' ' && lst->info[i][x] != '\t')
				{
					lst->info[i][j] = lst->info[i][x];
					j++;
				}
				x++;
			}
			lst->info[i][j] = '\0';
			remove_extra_spaces_2(var, lst, i);
			print_error(lst->path, ERROR_SPACE_NAME_FUNC, i + 1, LOW);
			j--;
		}
		else if (bracket == 0 && (lst->info[i][j] == ' ' || lst->info[i][j] == '\t'))
			j = check_name_prototipe(var, lst, j, i);
		j--;
	}
	lst->info[i] = add_void(var, lst->info[i], empty, proto);
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
		print_error(lst->path, ERROR_VAR_ASIGNATION, i + 1, MEDIUM);
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

bool	is_ternarian(lst_dir *lst, char *str, int *i)
{
	//printf("line: %s\n", str);
	//printf("; %d\n", ft_strchr_nocomented(str, ';'));
	//printf(": %d\n", ft_strchr_nocomented(str, ':'));
	//printf("? %d\n", ft_strchr_nocomented(str, '?'));
	if (ft_strchr_nocomented(str, ';') != -1 && ft_strchr_nocomented(str, ':') != -1
	&& ft_strchr_nocomented(str, '?') != -1)
	{
		print_error(lst->path, ERROR_TERNARIAN, *i, 4);
		return (true);
	}
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
		&& (str[len - 1] != ' ' && str[len - 1] != '\t' && str[len - 1] != '\n'))
			num++;
		len--;
	}
	if (num == 0)
		return (false);
	return (true);
}

int	ft_strstr_index_nocomented(const char *haystack, const char *needle, int ini)
{
	size_t	i;
	size_t	j;
	char c_comment;
	int num_comment;

	i = ini;
	num_comment = 0;
	if (!needle[0])
		return (-1);
	if (ini > ft_strlen(haystack))
		return (-1);
	while (haystack[i])
	{
		j = 0;
		if (haystack[i] == '"' || haystack[i] == '\'')
		{
			c_comment = haystack[i];
			num_comment++;
			i++;
		}
		while(haystack[i] && num_comment != 0)
		{
			if (haystack[i] == c_comment)
				num_comment--;
			i++;
		}
		while (needle[j] && haystack[i + j] == needle[j])
			j++;
		if (!needle[j])
			return (i);
		i++;
	}
	return (-1);
}

char	*new_old_str(char *new, char *old)
{
	char *str_new;

	free(old);
	str_new = ft_strdup(new);
	free(new);
	return (str_new);
}

void	ft_str_pop_pos(char *str, int pos)
{
	int x;

	x = pos;
	while (str[x + 1])
	{
		str[x] = str[x + 1];
		x++;
	}
	str[x] = '\0';
}
void	ft_str_pop_interval(char *str, int ini, int end)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (str[i])
	{
		while (str[i] && i >= ini && i <= end)
			i++;
		str[x] = str[i];
		x++;
		i++;
	}
	str[x] = '\0';
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

char	**ft_add_str_arr(char **src_arr, char *str, int pos)
{
	int i;
	int len;
	char	**arr;

	i = 0;
	len = ft_arrlen(src_arr);
	arr = malloc(sizeof(char *) * len + 2);
	while (src_arr[i] && i < pos)
	{
		arr[i] = strdup(src_arr[i]);
		i++;
	}
	arr[i] = strdup(str);
	i++;
	while (src_arr[i - 1])
	{
		arr[i] = strdup(src_arr[i - 1]);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}


char	**ft_add_chr_arr(char **src_arr, char c, int pos)
{
	int i;
	int len;
	char	**arr;

	i = 0;
	len = ft_arrlen(src_arr);
	arr = malloc(sizeof(char *) * len + 2);
	while (src_arr[i] && i < pos)
	{
		arr[i] = strdup(src_arr[i]);
		i++;
	}
	arr[i] = malloc(sizeof(char) * 2);
	arr[i][0] = c;
	arr[i][1] = '\0';
	i++;
	while (src_arr[i - 1])
	{
		arr[i] = strdup(src_arr[i - 1]);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	remove_comment(lst_dir *lst, int lower, int *i, char *op)
{
	bool	long_comment;
	int index;

	long_comment = false;
	index = ft_strstr_index_nocomented(lst->info[*i], "*/", 0);
	if (!ft_strcmp(op, "/*") && index == -1)
		long_comment = true;
	if (operator_start(lst, i, lower))
	{
		if (!ft_strcmp(op, "//") || index != -1 && operator_end(lst, i, lower, op))
			mark_empty_line(lst, *i, true);
		else if (index != -1)
			ft_str_pop_interval(lst->info[*i], lower, index + 1);
	}
	else
		ft_str_pop_interval(lst->info[*i], lower, index + 1);
	*i += 1;
	while (long_comment)
	{
		index = ft_strstr_index_nocomented(lst->info[*i], "", 0);
		if (index == -1)
			mark_empty_line(lst, *i, true);
		else if (index != -1 && lst->info[*i][index + 2] == '\n')
		{
			mark_empty_line(lst, *i, true);
			long_comment = false;
		}
		else if (index != -1)
		{
			ft_str_pop_interval(lst->info[*i], 0, index + 1);
			long_comment = false;
		}
		*i = *i + 1;
	}
}

void	check_spaces_operator(s_variables *var, lst_dir *lst, int *i, int op, int lower)
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
			space++;
			ft_str_pop_pos(lst->info[*i], lower - 1);
			print_error(lst->path, ERROR_SPACE_BEFORE_INCREMENTAL, *i + 1, MEDIUM);
		}
		if (lst->info[*i][lower + len - space] == ' ' || lst->info[*i][lower + len - space] == '\t')
		{
			ft_str_pop_pos(lst->info[*i], lower + len - space);
			print_error(lst->path, ERROR_SPACE_AFTER_INCREMENTAL, *i + 1, MEDIUM);
		}
	}
	else if (!ft_strcmp(var->operators[op], "->") || !ft_strcmp(var->operators[op], "."))
	{
		if (lst->info[*i][lower - 1] == ' ' || lst->info[*i][lower - 1] == '\t')
			print_error(lst->path, ERROR_SPACE_BEFORE_STRUCT_OPERATOR, *i + 1, MEDIUM);
		if (lst->info[*i][lower + len - space] == ' ' || lst->info[*i][lower + len] == '\t')
			print_error(lst->path, ERROR_SPACE_AFTER_STRUCT_OPERATOR, *i + 1, MEDIUM);
	}
	else if (!ft_strcmp(var->operators[op], "//") || !ft_strcmp(var->operators[op], "/*")
	|| !ft_strcmp(var->operators[op], "*/"))
	{
		if (!ft_strcmp(var->operators[op], "//") || !ft_strcmp(var->operators[op], "/*"))
		{
			print_error(lst->path, ERROR_COMMENT_FUNCTION, *i + 1, 3);
		remove_comment(lst, lower, i, var->operators[op]);
		}
		
	}
	else if (!ft_strcmp(var->operators[op], ","))
	{
		if (lst->info[*i][lower - 1] == ' ' || lst->info[*i][lower - 1] == '\t')
		{
			ft_str_pop_pos(lst->info[*i], lower - 1);
			print_error(lst->path, ERROR_SPACE_BEFORE_COMMA, *i, MEDIUM);
		}
		if (lst->info[*i][lower + 1] != ' ')
		{
			if (lst->info[*i][lower + 1] == '\t')
				lst->info[*i][lower + 1] = ' ';
			else
				lst->info[*i] = new_old_str(ft_strjoin_accurate(lst->info[*i], " ", lower + 1), lst->info[*i]);
			print_error(lst->path, ERROR_SPACE_AFTER_COMMA, *i, MEDIUM);
		}	
	}
	else
	{
		if (lst->info[*i][lower - 1] != ' ' && lst->info[*i][lower - 2] != '=')
		{
			print_error(lst->path, ERROR_NO_SPACE_BEFORE_OPERATOR, *i + 1, MEDIUM);
			space++;
			lst->info[*i] = new_old_str(ft_strjoin_accurate(lst->info[*i], " ", lower), lst->info[*i]);
		}
		if (lst->info[*i][lower + len + space] != ' ' && lst->info[*i][lower - 2] != '=')
		{
			print_error(lst->path, ERROR_NO_SPACE_AFTER_OPERATOR, *i + 1, MEDIUM);
			lst->info[*i] = new_old_str(ft_strjoin_accurate(lst->info[*i], " ", lower + len + space), lst->info[*i]);
		}
	}
}

void	check_operators(s_variables *var, lst_dir *lst, int *i)
{
	int x;
	int lower;
	int prev;
	int index;
	int op;

	prev = -2;
	lower = 0;
	while (lower != -1)
	{
		x = 0;
		lower = -1;
		op = -1;
		while (var->operators[x])
		{
			index = ft_strstr_index_nocomented(lst->info[*i], var->operators[x], prev + 2);
			if (index != -1 && (lower > index || lower == -1))
			{
				if ((prev < index && prev + ft_strlen(var->operators[x]) < index)
				|| prev == -2)
				{
					lower = index;
					op = x;
				}
			}
			x++;
		}
		if (op != -1)
		{
			if (operator_end(lst, i, lower, var->operators[op]))
				print_error(lst->path, ERROR_OPPERATOR_END, *i + 1, LOW);
			else if (op != -1 && (!operator_start(lst, i, lower) || !ft_strcmp(var->operators[op], "//")
			|| !ft_strcmp(var->operators[op], "/*")))
				check_spaces_operator(var, lst, i, op, lower);
		}
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
		index = ft_strstr_index_nocomented(lst->info[i], keywords[x], 0);
		if (index != -1)
			return (index);
		x++;
	}
	return (-1);
}

void	check_keywords(s_variables *var, lst_dir *lst, int *i)
{
	int x;
	char *tabs_str;
	int	len;
	int bracket;
	int index;

	x = 0;
	while (var->keywords[x])
	{
		index = ft_strstr_index_nocomented(lst->info[*i], var->keywords[x], 0);
		if (index != -1)
		{
			index = index + ft_strlen(var->keywords[x]);
			if (lst->info[*i][index] != ' ' && !ft_isalpha(lst->info[*i][index]) && lst->info[*i][index] != '\n')
			{
				print_error(lst->path, ERROR_NO_SPACE_KEYWORD, *i + 1, LOW);
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
	tabs_str = malloc(sizeof(char) * num_tabs + 1);
	ft_bzero(tabs_str, num_tabs + 1);
	ft_memset(tabs_str, '\t', num_tabs);
	lst->info[i + 1] =  new_old_str(ft_strjoin_accurate(lst->info[i + 1], tabs_str, 0), lst->info[i + 1]);
	free(tabs_str);
}

int	empty_until_pos(char *str, int pos)
{
	int i;

	i = 0;
	while (str[i] && i <= pos)
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
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
		if (!empty_until_pos(lst->info[i], index - 1))
		{
			correct_line_bracket(var, lst, i, index);
			print_error(lst->path, ERROR_BRACKET_KEYWORD, i + 1, MEDIUM);
			error = true;
		}
		else if (!empty_line(&lst->info[i][count_indentations(lst->info[i]) + 1]))
		{
			correct_line_bracket(var, lst, i, index + 1);
			print_error(lst->path, ERROR_BRACKET_NOEMPTY, i + 1, MEDIUM);
			error = true;
		}
		lst->num_bracket++;
	}
	index = ft_strchr_nocomented(lst->info[i], '}');
	if (index != -1)
	{
		if (!empty_line(&lst->info[i][index + 1]))
		{
			correct_line_bracket(var, lst, i, index + 1);
			print_error(lst->path, ERROR_CLOSE_BRACKET_NOEMPTY, i + 1, MEDIUM);
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
		ft_str_pop_interval(lst->info[*i], 1, 4);
}

void	correct_indentation(s_variables *var, lst_dir *lst, int i, int indentation)
{
	char *num_tabs;

	if (lst->indent > indentation && !empty_line(lst->info[i]))
	{
		num_tabs = malloc(sizeof(char) * (lst->indent - indentation) + 2);
		ft_bzero(num_tabs, (lst->indent - indentation) + 2);
		memset(num_tabs, '\t', lst->indent - indentation);
		lst->info[i] = new_old_str(ft_strjoin_accurate(lst->info[i], num_tabs, 0), lst->info[i]);
		free(num_tabs);
		print_error(lst->path, ERROR_INDENTATION, i + 1, MEDIUM);
	}
	else if (lst->indent < indentation && !empty_line(lst->info[i]))
	{
		ft_str_pop_interval(lst->info[i], 0, (indentation - lst->indent) - 1);
		print_error(lst->path, ERROR_INDENTATION, i + 1, MEDIUM);
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
		pos = is_keyword(var, lst, i, var->keywords);
		if (pos != -1)
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

void	print_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		write(1, arr[i], ft_strlen(arr[i]));
		write(1, "\n", 1);
		i++;
	}	
}

void	check_columns(lst_dir *lst, int *i)
{
	int	num_columns;

	num_columns = get_real_hor_pos(lst->info[*i]);
	if (num_columns > 80) // linea muy larga
	{
		print_error_var(lst->path, ERROR_TO_LONG_LINE, *i + 1, MEDIUM);
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
	}
}


void	inside_function(s_variables *var, lst_dir *lst, int *i)
{
	int max;
	bool followed_var;
	int	start;
	int	num_misaligned;
	int num_var;
	int len;
	t_lst_arr *temp;
	bool error_empty;
	int index;
	
	max = 0;
	error_empty = false;
	num_var = 0;
	lst->num_bracket = 0;
	lst->inside_comment = 0;
	start = *i + 1 + check_brackets(var, lst, *i);
	followed_var = is_var(lst->info[start]);
	check_prototipe_func(var, lst, *i - 1, false);
	remove_mid_spaces(var, lst, *i - 1);
	*i = start;
	if (empty_line(lst->info[start]))
		print_error(lst->path, ERROR_WRONG_EMPTY_LINE, start + 1, MEDIUM);
	while (lst->info[*i] && lst->num_bracket != 0)
	{
		check_brackets(var, lst, *i);
		len = ft_strlen(lst->info[*i]);
		check_columns(lst, i);
		remove_last_spaces(var, lst, *i);
		remove_mid_spaces_2(var, lst, *i);
		if (is_var(lst->info[*i]) && !is_ternarian(lst, lst->info[*i], i))
		{
			num_var++;
			max = correct_var(var, lst, i, max);
			if (!followed_var)
			{
				save_var_bad_line(var, lst, i);
				print_error(lst->path, ERROR_VARIBALES_FOLLOWED, *i + 1, MEDIUM);
			}
			else
				check_variables(var, lst, *i);
		}
		else
		{
			if (followed_var)
			{
				temp = var->var_bad_decl;
				while (temp) // ADD BAD DECLARATION VARIABLES (ASIGNATION AND DECLARATION)
				{
					lst->info = ft_add_str_arr(lst->info, temp->str, *i);
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
		print_error(lst->path, ERROR_MANY_VAR, start + 1, MEDIUM);
	lst->num_bracket = 1;
	temp = var->var_bad_line;
	while (temp) // ADD BAD DECLARATION LINE VARIABLES (ASIGNATION AND DECLARATION)
	{
		lst->info = ft_add_str_arr(lst->info, temp->str, start);
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
				lst->info[*i] = correct_misaligned(lst->info[*i], max, num_misaligned);
		}
		else if (followed_var && !empty_line(lst->info[*i]) && ft_strcmp(lst->info[*i], "@#~#@\n") != 0)
		{
			lst->info = ft_add_str_arr(lst->info, "\n", *i);
			print_error(lst->path, ERROR_NO_EMPTY_LINE_VAR, *i - 1, MEDIUM);
			followed_var = false;
		}
		else if (!followed_var && empty_line(lst->info[*i]))
			mark_empty_line(lst, *i, false);
		else
			followed_var = false;
		is_ternarian(lst, lst->info[*i], i);
		*i += 1;
	}
	check_indentation(var, lst, start);
	free_linked_arr(&var->var_bad_decl);
	free_linked_arr(&var->var_bad_line);
	if (lst->info[*i])
	{
		if (!empty_line(lst->info[*i]))
		{
			print_error(lst->path, ERROR_ENTER_FUNCTIONS, *i + 1, MEDIUM);
			lst->info = ft_add_str_arr(lst->info, "\n", *i);
		}
	}
	else
	{
		if (ft_strchr_nocomented(lst->info[*i - 1], '\n') == -1)
		{
			print_error(lst->path, ERROR_ENTER_END_FILE, *i + 1, MEDIUM);
			lst->info = ft_add_str_arr(lst->info, "\n", *i);
		}
	}
}

void	check_num_lines(lst_dir *lst, int num_lines, int i)
{
	if (num_lines > 25)
	{
		print_error_var(lst->path, ERROR_NUM_LINES, i + 1, LOW);
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
		empty = empty_line(lst->info[i]);
		!empty ? empty_lines = 0 , error = 0 : empty_lines++;
		if (empty_lines > 1 || lst->info[i] == NULL)
		{
			mark_empty_line(lst, i, error);
			error = true;
		}
		if (ft_strnstr(lst->info[i], "{", len))
		{
			num_lines = i;
			inside_function(var, lst, &i);
			num_lines = i - num_lines;
			check_num_lines(lst,num_lines - 2, i);	
			lst->num_functions++;
		}
		else
			i++;
	}
	if (lst->num_functions > 5)
	{
		print_error_var(lst->path, ERROR_NUM_FUNCTIONS, i + 1, LOW);
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