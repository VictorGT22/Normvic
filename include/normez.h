/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normez.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:43:48 by victgonz          #+#    #+#             */
/*   Updated: 2023/04/30 12:03:52 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORMEZ_H
# define NORMEZ_H

# include "libft.h"
# include "ft_printf.h"
# include "normez_struct.h"
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <ctype.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <string.h>
# include <stdbool.h>

//MACROS
# define TAB_SIZE 4
# define TYPE_VAR "short,int,long,char,void,unsigned"
# define KEY_WORDS "auto,break,case,char,const,continue,default,do,double,else,enum,extern,float,for,goto,if,int,long,register,return,short,signed,sizeof,static,struct,switch,typedef,union,unsigned,void,volatile,while"
# define OPPERATORS "+,-,=,|,<,>,%,!,&,/"

//MACROS ERRORS
# define ERROR_MSG "Error\n"
# define ERROR_HEADER "Header corrupted, try to verify\n"
# define ERROR_TRALING_SPACE "Traling spaces at the end of the line\n"
# define ERROR_WRONG_TAB "There is a Tab, where needs to be a Space\n"
# define ERROR_WRONG_SPACE "There is a Space, where needs to be a Tab\n"
# define ERROR_SPACE_NAME_FUNC "Space between function name and brakets\n"
# define ERROR_CONSECUTIVE_TABS "Two o more consecutive new lines\n"
# define ERROR_HEADER_FILE "Corrupted initialization header file\n"
# define ERROR_INCLUDE_HEADER_FILE "Error Include in header file\n"
# define ERROR_NO_EMPTY_LINE "Error no empty line\n"
# define ERROR_STRUCT_NAME "Struct abreviation needs to start with 't_'\n"


//PROTOTIPES
lst_dir *new_node(char *filepath);
void	lstadd_back(lst_dir **lst, lst_dir *new);
lst_dir	*lstlast(lst_dir *lst);
t_lst_arr *new_node_arr(char *line);
void	lstadd_back_arr(t_lst_arr **lst, t_lst_arr *new);
t_lst_arr	*lstlast_arr(t_lst_arr *lst);

//CHECKER
unsigned int	check_header(s_variables *var, lst_dir *lst, int *add_i);
void	check_errors(s_variables *var, lst_dir *lst);
void	remove_extra_spaces(s_variables *var, lst_dir *lst, int i);
void	remove_last_spaces(s_variables *var, lst_dir *lst, int i);
void	remove_extra_spaces_2(s_variables *var, lst_dir *lst, int i);
void	remove_mid_spaces(s_variables *var, lst_dir *lst, int i);
void	check_prototipe_func(s_variables *var, lst_dir *lst, int i);
int		check_name_prototipe(s_variables *var, lst_dir *lst, int j, int i);

//CHECKER _H
void	check_errors_h(s_variables *var, lst_dir *lst);

//PRINT ERROR
void	print_error(char *path, char *msg_error, int line, int code_error);

#endif

