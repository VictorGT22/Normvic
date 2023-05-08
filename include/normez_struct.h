/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normez_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:43:01 by vics              #+#    #+#             */
/*   Updated: 2023/05/02 15:59:43 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORMEZ_STRUCT_H
# define NORMEZ_STRUCT_H

typedef struct lst_dir
{
    char			*path;
    char			**info;
    int				num_functions;
    int				num_key;
    int				no_error;
    struct lst_dir	*next;
    struct lst_dir	*prev;
}	lst_dir;

typedef struct lst_array
{
	char				*str;
	struct lst_array	*next;
	struct lst_array	*prev;
}	t_lst_arr;

typedef struct s_variables
{
    lst_dir	*lst_dir;
    lst_dir	*lst_files;
    t_lst_arr *var_type;
    char	**keywords;
    char	**operators;
}	s_variables;

#endif