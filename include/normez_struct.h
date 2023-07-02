/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normez_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:43:01 by vics              #+#    #+#             */
/*   Updated: 2023/07/02 00:49:10 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORMEZ_STRUCT_H
# define NORMEZ_STRUCT_H

# include <stdbool.h>

typedef struct lst_dir
{
	char			*path;
	char			**info;
	int				num_functions;
	int				num_bracket;
	int				indent;
	int				no_error;
	int				inside_comment;
	int				header_level;
	struct lst_dir	*next;
	struct lst_dir	*prev;
}	lst_dir;

typedef struct lst_array
{
	char				*str;
	struct lst_array	*next;
	struct lst_array	*prev;
}	t_lst_arr;

typedef struct flags
{
	bool	all;
	bool	brackets;
	bool	comments;
	bool	indents;
	bool	replace;
	bool	only_c;
	bool	only_h;
	bool	help;
}	t_flags;

typedef struct s_variables
{
	lst_dir		*lst_dir;
	lst_dir		*lst_files;
	t_lst_arr	*var_type;
	t_lst_arr	*var_bad_decl;
	t_lst_arr	*var_bad_line;
	t_flags		*flags;
	char		**keywords_indent;
	char		**keywords;
	char		**operators;
	char		**operators_nospace;
}	s_variables;

#endif
