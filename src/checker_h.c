/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_h.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:00:33 by vics              #+#    #+#             */
/*   Updated: 2023/07/18 12:48:11 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normez.h"

/*void	get_type_var(s_variables *var)
{
	int i;
	int len;
	lst_dir *tmp;

	tmp = var->lst_files;
	while (tmp)
	{
		if (get_postfix(tmp->path, ".h"))
			while (tmp->info[i])
	{
		if (ft_strnstr(tmp->info[i], "{", len))
			tmp->num_key++;
		i++;
	}
	printf("%s\n", tmp->path);
	tmp = tmp->next;
}

*/

bool	remove_space_pos(s_variables *var, lst_dir *lst, int i, int pos)
{
	int j;
	int	x;
	bool error;
	char *str;
	
	j = 0;
	x = 0;
	str = malloc(sizeof(char) * ft_strlen(lst->info[i]) + 1);
	ft_bzero(str, ft_strlen(lst->info[i]) + 1);
	while (lst->info[i][j] && j < pos)
		str[x++] = lst->info[i][j++];
	while (lst->info[i][j])
	{
		if ((lst->info[i][j] != ' ' && lst->info[i][j] != '\t')
		|| (lst->info[i][j + 1] != ' ' && lst->info[i][j + 1] != '\t'))
			str[x++] = lst->info[i][j];
		j++;
	}
	error = false;
	if (strcmp(lst->info[i], str) != 0)
		error = true;
	free(lst->info[i]);
	lst->info[i] = str;
	return (error);
}

void	mark_empty_line(lst_dir *lst, int i, bool error)
{
	if (!error)
		print_error(lst, ERROR_CONSECUTIVE_NEWLINES, i + 1, SOLVABLE);
	if (lst->info[i])
		free(lst->info[i]);
	lst->info[i] = ft_strdup("@#~#@\n");
}

char	*check_name_include(lst_dir *lst, int *i, char *str)
{
	int 	n;
	int		x;
	char	*name;

	x = 0;
	n = ft_chr_index(lst->info[*i], '"');
	if (!lst->info[*i][n])
		n = ft_chr_index(lst->info[*i], '<');
	name = malloc(sizeof(char) * (ft_strlen(lst->info[*i]) - n) + 2);
	while (lst->info[*i][n])
	{
		name[x++] = lst->info[*i][n];
		n++;
	}
	name[x] = '\0';
	return (ft_strjoin(str, name));	
}

void	check_include(s_variables *var, lst_dir *lst, int *i)
{
	int		j;
	char	*str;

	ft_replace_chrchr(lst->info[*i], '\t', ' ');
	j = ft_strstr_index_nocommented(lst->info[*i], "include", 0) + 7;
	if (remove_space_pos(var, lst, *i, j))
		print_error(lst, ERROR_MULTIPLE_SPACES, *i + 1, SOLVABLE);
	str = check_name_include(lst, i, "# include ");
	if (ft_strcmp(str, lst->info[*i]) != 0)
	{
		free(lst->info[*i]);
		lst->info[*i] = ft_strdup(str);
		print_error(lst, ERROR_SPACE_HASH, *i + 1, SOLVABLE);
		free(str);
	}
}

int check_name(lst_dir *lst, int i, int j, char *type)
{
	char *str;
	char *spaces;
	char *name;

	str = ft_strdup(type);
	spaces = malloc(sizeof(char) * lst->header_level + 1);
	ft_bzero(spaces, lst->header_level + 1);
	ft_memset(spaces, ' ', lst->header_level);
	str = ft_strjoin_accurate(str, spaces, 1);
	name = ft_substr(lst->info[i], 0, j);
	if (ft_strcmp(str, name) != 0)
	{
		printf("&%s&, &%s&\n", str, name);
		ft_strpop_interval(lst->info[i], 0, j - 1);
		lst->info[i] = new_old_str(ft_strjoin_accurate(lst->info[i], str, 0), lst->info[i]);
		return (1);
	}
	return (0);
}

void	check_define(s_variables *var, lst_dir *lst, int *i)
{
	int	j;
	int x;
	char *str;

	if (ft_replace_chrchr(lst->info[*i], '\t', ' '))
		print_error(lst, ERROR_WRONG_TAB, *i + 1, SOLVABLE);
	j = ft_strstr_index_nocommented(lst->info[*i], "define", 0) + 6;
	if (check_name(lst, *i, j, "#define"))
		print_error(lst, ERROR_SPACE_HASH, *i + 1, SOLVABLE);
	j = ft_strstr_index_nocommented(lst->info[*i], "define", 0) + 6;
	x = j + 1;
	while (lst->info[*i][x] && lst->info[*i][x] != ' '  && lst->info[*i][x] != '(')
		x++;
	str = ft_substr(lst->info[*i], j + 1, x - j - 1);
	if (!ft_str_isupper(str))
	{
		print_error(lst, ERROR_NAME_MACRO, *i + 1, SOLVABLE);
		ft_str_toupper(str);
		ft_strpop_interval(lst->info[*i], j + 1, x - 1);
		lst->info[*i] = new_old_str(ft_strjoin_accurate(lst->info[*i], str, j + 1), lst->info[*i]);
	}
	check_keywords(var, lst, i);
	check_operators(var, lst, i, false);
	if (remove_space_pos(var, lst, *i, j))
		print_error(lst, ERROR_MULTIPLE_SPACES, *i + 1, SOLVABLE);
}

void	check_endif(s_variables *var, lst_dir *lst, int *i)
{
	int j;

	j = ft_strstr_index(lst->info[*i], "endif") + 5;
	if (lst->header_level == 1 && ft_strcmp("#endif\n", lst->info[*i]) != 0)
	{
		free(lst->info[*i]);
		lst->info[*i] = ft_strdup("#endif");
		print_error(lst, ERROR_ENDIF, *i + 1, SOLVABLE);
		lst->header_level--;
	}
	else
	{
		lst->header_level--;
		if (check_name(lst, *i, j, "#endif"))
			print_error(lst, ERROR_ENDIF, *i + 1, SOLVABLE);
	}
}

void	check_ifdef(s_variables *var, lst_dir *lst, int *i)
{
	int j;

	j = ft_strstr_index(lst->info[*i], "ifdef") + 5;
	if (check_name(lst, *i, j, "#ifdef"))
		print_error(lst, ERROR_ENDIF, *i + 1, SOLVABLE);
	lst->header_level++;
}

void	check_else(s_variables *var, lst_dir *lst, int *i)
{
	int j;

	lst->header_level--;
	j = ft_strstr_index(lst->info[*i], "else") + 4;
	if (check_name(lst, *i, j, "#else"))
		print_error(lst, ERROR_ENDIF, *i + 1, SOLVABLE);
	lst->header_level++;
}

char	*check_name_header(lst_dir *lst, int *i, char *str)
{
	int 	n;
	int		x;
	char	*name;

	x = 0;
	n = ft_last_chr_index(lst->path, '/') + 1;
	name = malloc(sizeof(char) * (ft_strlen(lst->path) - n) + 2);
	while (lst->path[n])
	{
		if (lst->path[n] == '.')
			name[x++] = '_';
		else
			name[x++] = ft_toupper(lst->path[n]);
		n++;
	}
	name[x++] = '\n';
	name[x] = '\0';
	return (ft_strjoin(str, name));
}

void	check_indef(s_variables *var, lst_dir *lst, int *i)
{
	int j;
	char *str;

	if (ft_replace_chrchr(lst->info[*i], '\t', ' '))
		print_error(lst, ERROR_WRONG_TAB, *i + 1, SOLVABLE);
	if (lst->header_level == 0)
	{
		if (ft_replace_chrchr(lst->info[*i], '\t', ' '))
			print_error(lst, ERROR_WRONG_TAB, *i + 1, SOLVABLE);
		str = check_name_header(lst, i, "#ifndef ");
		if (ft_strcmp(str, lst->info[*i]) != 0)
		{
			lst->info[*i] = new_old_str(str, lst->info[*i]);
			print_error(lst, ERROR_HEADER_FILE, *i + 1, SOLVABLE);
		}
		*i += 1;
		if (ft_replace_chrchr(lst->info[*i], '\t', ' '))
			print_error(lst, ERROR_WRONG_TAB, *i + 1, SOLVABLE);
		str = check_name_header(lst, i, "# define ");
		if (ft_strcmp(str, lst->info[*i]) != 0)
		{
			lst->info[*i] = new_old_str(str, lst->info[*i]);
			print_error(lst, ERROR_HEADER_FILE, *i + 1, SOLVABLE);
		}
	}
	else
	{
		j = ft_strstr_index(lst->info[*i], "ifndef") + 6;
		if (check_name(lst, *i, j, "#ifndef"))
			print_error(lst, ERROR_INDEF, *i + 1, SOLVABLE);
		int x = j + 1;												//mejorar esto, es bastante estandar
		while (lst->info[*i][x] && lst->info[*i][x] != ' '  && lst->info[*i][x] != '(')
			x++;
		str = ft_substr(lst->info[*i], j + 1, x - j - 1);
		if (!ft_str_isupper(str))
		{
			print_error(lst, ERROR_INDEF_NAME, *i + 1, SOLVABLE);
			ft_str_toupper(str);
			ft_strpop_interval(lst->info[*i], j + 1, x - 1);
			lst->info[*i] = new_old_str(ft_strjoin_accurate(lst->info[*i], str, j + 1), lst->info[*i]);
		}
	}
		
	lst->header_level++;
}

int	get_real_hor_pos(char *str)
{
	int	i;
	int spaces;

	i = 0;
	spaces = 0;
	while (str[i] && str[i] == '\t')
	{
		spaces += 4;
		i++;
	}
	while (str[i] && str[i] != '\t')
	{
		spaces++;
		i++;
	}
	if (spaces % TAB_SIZE)
		i++;
	while (spaces % TAB_SIZE)
		spaces++;
	while (str[i] && str[i] == '\t')
	{
		spaces += 4;
		i++;
	}
	return (spaces);
}

int	get_max(int num_1, int num_2)
{
	if (num_1 > num_2)
		return (num_1);
	return (num_2);
}

void	correct_misaligned(lst_dir *lst, int i, int max, int num_tabs)
{
	char *result;
	char *str;

	num_tabs = (max - num_tabs) / 4;
	str = calloc(sizeof(char), num_tabs + 1);
	ft_bzero(str, num_tabs + 1);
	ft_memset(str, '\t', num_tabs);
	lst->info[i] = new_old_str(ft_strjoin_accurate(lst->info[i], str,
	ft_last_chr_index(lst->info[i], '\t')), lst->info[i]);
}

void	check_misaligned_prototipes(lst_dir *lst, int max_indent, int start)
{
	int num_misaligned;
	bool	empty;
	int	empty_lines;
	bool error;
	char *str;

	error = false;
	empty_lines = 0;
	int i = 0;
	while (lst->info[i] && lst->info[i][0] != '\0')
	{
		if (ft_strrchr(lst->info[i], ';') && ft_strrchr(lst->info[i], ')'))
		{
			num_misaligned =  get_real_hor_pos(lst->info[i]);
			if (max_indent > num_misaligned)
				correct_misaligned(lst, i, max_indent, num_misaligned);
		}
		empty = ft_empty_line(lst->info[i]);
		!empty ? empty_lines = 0 , error = 0 : empty_lines++;
		if (empty_lines > 1 || lst->info[i] == NULL)
		{
			mark_empty_line(lst, i, error);
			error = true;
		}
		i++;
	}
}

int	correct_var(s_variables *var, lst_dir *lst, int *i, int prev_aligment)
{
	int j;
	int n;
	int aligment;

	n = 0;
	remove_last_spaces(var, lst, *i);
	while (lst->info[*i][n] &&
	(lst->info[*i][n] == '\t' || lst->info[*i][n] == ' '))
	{
		if (lst->info[*i][n] == ' ')
			lst->info[*i][n] = '\t';
		n++;
	}
	if (n == 0)
	{
		lst->info[*i] = new_old_str(ft_strjoin_accurate(lst->info[*i], "\t", 0), lst->info[*i]);
		print_error(lst, ERROR_NO_TAB_START_VAR, *i + 1, SOLVABLE);
	}
	int index = ft_strchr_nocomented(lst->info[*i], '=');
	j = (index == -1) ? ft_strlen(lst->info[*i]) - 3 : index - 2;
	index = ft_strchr_nocomented(lst->info[*i], '(');
	if (index != -1 && index < j)
		j = ft_strchr_nocomented(lst->info[*i], '(') + 1;
	if (ft_replace_chrchr(&lst->info[*i][j], '\t', ' '))
		print_error(lst, ERROR_WRONG_TAB, *i + 1, SOLVABLE);
	while (j >= 0 && (lst->info[*i][j] == ' ' || lst->info[*i][j] == '\t'))
	{
		ft_strpop_pos(lst->info[*i], j);
		j--;
	}
	while (j >= 0 && lst->info[*i][j] != ' ' && lst->info[*i][j] != '\t')
		j--;
	while (j >= 0 &&
	(lst->info[*i][j] == '\t' || lst->info[*i][j] == ' ')) // esto mejorar
	{
		if (lst->info[*i][j] == ' ')
		{
			print_error(lst, ERROR_WRONG_SPACE, *i + 1, SOLVABLE);
			lst->info[*i][j] = '\t';
		}
		j--; 
	}
	while (j >= 0 && lst->info[*i][j] != ' ' && lst->info[*i][j] != '\t')
		j--;
	if (j != n - 1 && lst->info[*i][j] != ' ')
	{
		lst->info[*i][j] = ' ';
		print_error(lst, ERROR_WRONG_SPACE, *i + 1, SOLVABLE);
	}
	aligment = get_real_hor_pos(lst->info[*i]);
	if (aligment != prev_aligment && prev_aligment != -1)
		print_error(lst, ERROR_MISALIGNED, *i + 1, SOLVABLE);
	remove_extra_spaces_2(var, lst, *i);	
	remove_mid_spaces_2(var, lst, *i);
	return (aligment);
}

void	check_strcture(s_variables *var, lst_dir *lst, int *i)
{
	int j;
	int start;
	int max;
	int num_misaligned;
	char *new;
	t_lst_arr *node2;

	max = 0;
	start = *i + 1;
	remove_extra_spaces(var, lst, *i);
	remove_extra_spaces(var, lst, *i - 1);
	if (ft_replace_chrchr(lst->info[*i - 1], '\t', ' ')) // cabecera struct
		print_error(lst, ERROR_WRONG_SPACE, *i, 1);
	node2 = new_node_arr(ft_strtrim(lst->info[*i - 1], "\n; {"));
	lstadd_back_arr(&var->var_type, node2);
	if (!ft_empty_line(lst->info[*i - 2]))
	{
		remove_last_spaces(var, lst, *i);
		print_error(lst, ERROR_NO_EMPTY_LINE, *i - 1, SOLVABLE);
		new = ft_strjoin(lst->info[*i - 2], "\n");
		free(lst->info[*i - 2]);
		lst->info[*i - 2] = ft_strdup(new);
	}
	max = 0;
	*i += 1;
	int prev_aligment = -1;
	while (!ft_strrchr(lst->info[*i], '}'))///var inside struct
	{
		remove_last_spaces(var, lst, *i);
		if (ft_strrchr(lst->info[*i], ';'))
		{
			prev_aligment = correct_var(var, lst, i, prev_aligment);
			max = get_max(max, get_real_hor_pos(lst->info[*i]));
		}
		*i += 1;
	}
	while (!ft_strrchr(lst->info[start], '}'))// correct var inside struct
	{
		num_misaligned =  get_real_hor_pos(lst->info[start]);
		if (max > num_misaligned)
			correct_misaligned(lst, start, max, num_misaligned);
		if (ft_empty_line(lst->info[start]))
			mark_empty_line(lst, start, true);
		start += 1;
	}
	if (ft_strrchr(lst->info[*i], '}'))
	{
		remove_last_spaces(var, lst, *i);
		if (!ft_strstr(lst->info[*i], "\tt_"))
			print_error(lst, ERROR_STRUCT_NAME, *i + 1, NOSOLVABLE);
		if (ft_replace_chrchr(lst->info[*i], ' ', '\t'))
			print_error(lst, ERROR_WRONG_TAB, *i + 1, SOLVABLE);
		j = ft_strlen(lst->info[*i]) - 2;
		while (j >= 0 && lst->info[*i][j] != ' ' && lst->info[*i][j] != '\t')
			j--;
		node2 = new_node_arr(ft_strtrim(&lst->info[*i][j + 1], "\n;"));
		lstadd_back_arr(&var->var_type, node2);
	}
	j = ft_strchr_nocomented(lst->info[*i], '}');
	if (lst->info[*i][j + 1] != '\t')
	{
		print_error(lst, ERROR_TAB_NAME_STRUCT, *i + 1, SOLVABLE);	
		if (lst->info[*i][j + 1] == ' ')
			lst->info[*i][j + 1] = '\t';
		else
			lst->info[*i] = new_old_str(ft_strjoin_accurate(lst->info[*i], "\t", j + 1), lst->info[*i]);
	}
}

void	read_lines_h(s_variables *var, lst_dir *lst, int *add_i)
{
	int i;
	int	first_prototipe;
	int	prev_aligment;
	int	max_aligned_proto;
	
	i = *add_i;
	prev_aligment = -1;
	first_prototipe = 0;
	max_aligned_proto = 0;
	lst->header_level = 0;
	while (lst->info[i])
	{
		remove_last_spaces(var, lst, i);
		if (ft_strchr_nocomented(lst->info[i], '#') != -1)
		{
			if (ft_strstr_index_nocommented(lst->info[i], "ifndef", 0) != -1)
				check_indef(var, lst, &i);
			else if (ft_strstr_index_nocommented(lst->info[i], "include", 0) != -1)
				check_include(var, lst, &i);
			else if (ft_strstr_index_nocommented(lst->info[i], "define", 0) != -1)
				check_define(var, lst, &i);
			else if (ft_strstr_index_nocommented(lst->info[i], "endif", 0) != -1)
				check_endif(var, lst, &i);
			else if (ft_strstr_index_nocommented(lst->info[i], "else", 0) != -1)
				check_else(var, lst, &i);
			else if (ft_strstr_index_nocommented(lst->info[i], "ifdef", 0) != -1)
				check_ifdef(var, lst, &i);
		}
		if (ft_strchr_nocomented(lst->info[i], ';') != -1)
		{
			if (ft_strchr_nocomented(lst->info[i], ')') != -1)
			{
				if (!first_prototipe)
					first_prototipe = i;
				prev_aligment = check_prototipe_func(var, lst, i, true, prev_aligment);
				remove_extra_spaces(var, lst, i);
				remove_btw_semicolon(var, lst, i);
				max_aligned_proto = get_max(max_aligned_proto, get_real_hor_pos(lst->info[i]));
			}
		}
		else if (ft_strchr_nocomented(lst->info[i], '{') != -1)
			check_strcture(var, lst, &i);
		i++;
	}
	check_misaligned_prototipes(lst, max_aligned_proto, first_prototipe);
}

void	check_errors_h(s_variables *var, lst_dir *lst)
{
	int i;

	i = 0;
	check_header(var, lst, &i);
	read_lines_h(var, lst, &i);
}