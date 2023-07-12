/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normez.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 23:43:48 by victgonz          #+#    #+#             */
/*   Updated: 2023/07/11 21:46:43 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORMEZ_H
# define NORMEZ_H

# include  "libft.h"
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

# define    PATH_UPDATE "bin/install/update.sh"

//MACROS
# define TAB_SIZE 4
# define TYPE_VAR "short,int,long,char,void,unsigned"
# define KEY_WORDS "return,break,else if,do,else,for,if,switch,while"
# define KEY_WORDS_INDENT "case,default,do,else,for,if,switch,while"
# define OPPERATORS_BOTH_SPACE "==,||,++,--,&&,//,/*,*/,+=,*=,-=,%=,/=,!=,->,<=,>=,<,>,=,/,%,.,(,),;,[,]"
# define OPPERATORS_DIVIDE "&&,||,!=,==,<=,>="

//MACROS ERROR COLOR
# define SOLVABLE 3
# define WTF 2
# define NOSOLVABLE 1
# define COMMENT 4

//MACROS ERRORS
# define ERROR_MSG "Error\n"
# define ERROR_HEADER "Header corrupted, try to verify\n"
# define ERROR_TRALING_SPACE "Traling spaces at the end of the line\n"
# define ERROR_WRONG_TAB "There is a Tab, where needs to be a Space\n"
# define ERROR_WRONG_SPACE "There is a Space, where needs to be a Tab\n"
# define ERROR_SPACE_NAME_FUNC "Space between function name and brakets\n"
# define ERROR_CONSECUTIVE_NEWLINES "Two o more consecutive new lines\n"
# define ERROR_HEADER_FILE "Corrupted initialization header file\n"
# define ERROR_INCLUDE_HEADER_FILE "Error Include in header file\n"
# define ERROR_INDEF_NAME "Error name ifndef must be in uppercase\n"
# define ERROR_INDEF "Error ifndef\n"
# define ERROR_SPACE_HASH "Wrong num spaces after #\n"
# define ERROR_NO_EMPTY_LINE "Error no empty line\n"
# define ERROR_WRONG_EMPTY_LINE "Error wrong empty line\n"
# define ERROR_STRUCT_NAME "Struct abreviation needs to start with 't_'\n"
# define ERROR_SEMICOLON "Space/Tab before semicolon at the endo of the line\n"
# define ERROR_ENDIF "Error at the ENDIF\n"
# define ERROR_VAR_ASIGNATION "Variable inicialitzation and asignation in the same line\n"
# define ERROR_MANY_VAR "To many variables inside a function\n"
# define ERROR_NO_SPACE_KEYWORD "Needs to be a space after a keyword\n"
# define ERROR_SPACE_BEFORE_INCREMENTAL "Space before a incremental operator\n"
# define ERROR_SPACE_AFTER_INCREMENTAL "Space after a incremental operator\n"
# define ERROR_NO_SPACE_BEFORE_OPERATOR "Need to be a Space before a operator\n"
# define ERROR_NO_SPACE_AFTER_OPERATOR "Need to be a Space after a operator\n"
# define ERROR_SPACE_BEFORE_STRUCT_OPERATOR "Space before a struct operator\n"
# define ERROR_SPACE_AFTER_STRUCT_OPERATOR "Space after a struct operator\n"
# define ERROR_TO_LONG_LINE "Line to long, more than 80 columns. "
# define ERROR_VARIBALES_FOLLOWED "Variable declaration must be at the start of the function\n"
# define ERROR_INDENTATION "Wrong Indentation\n"
# define ERROR_COMMENT_FUNCTION "Comment inside a function\n"
# define ERROR_NO_EMPTY_LINE_VAR "Error no empty line between Variables and your code\n"
# define ERROR_OPPERATOR_END "Operator at the end of the line\n"
# define ERROR_BRACKET_KEYWORD "Curly bracket in the same line than a keyword or prototipe function\n"
# define ERROR_BRACKET_NOEMPTY "Curly bracket must be alone in the line\n"
# define ERROR_CLOSE_BRACKET_NOEMPTY "No empty line after a close curly bracket\n"
# define ERROR_ENTER_FUNCTIONS "Need to be a empty line between functions\n"
# define ERROR_ENTER_END_FILE "Need to be a empty line at the end of the file\n"
# define ERROR_NAME_MACRO "Macros needs to be named with all letters uppercase\n"
# define ERROR_NUM_FUNCTIONS "Too many functions inside a file "
# define ERROR_NUM_LINES "Too many lines in a function "
# define ERROR_FILE_NAME "Files and folders names must be in lowercase\n"
# define ERROR_SPACE_BEFORE_COMMA "Must be no space before a comma\n"
# define ERROR_SPACE_AFTER_COMMA "Must be a space after a comma\n"
# define ERROR_TERNARIAN "Ternarians are forbiden, it sucks but it is what it is\n"
# define ERROR_SPACE_AFTER_PARENTHESIS "Space after parenthesis\n"
# define ERROR_SPACE_BEFORE_PARENTHESIS "Space before parenthesis\n"
# define ERROR_SPACE_BEFORE_SEMICOLON "Space before semicolon\n"
# define ERROR_SPACE_FUNCTION "Space before name function and parenthesis\n"
# define ERROR_SPACE_AFTER_BRACKETS "Space after square brackets\n"
# define ERROR_SPACE_BEFORE_BRACKETS "Space before square brackets\n"
# define ERROR_VOID "If a function does not receive anything, it must have the type void\n"
# define ERROR_NO_TAB_START_VAR "No tab before var, cmon be focus when you code\n"
# define ERROR_MISALIGNED "Variable misaligned\n"
# define ERROR_MISALIGNED_PROTO "Prototype misaligned\n"
# define ERROR_MULTIPLE_SPACES "Unecesary multiple space elements followed\n"
# define ERROR_MAKEFILE "Wrong Makefile name\n"
# define ERROR_REPO "You only can execute the NORMVIC inside a repo for security\n"

//PROTOTIPES
lst_dir			*new_node(char *filepath);
void			lstadd_back(lst_dir **lst, lst_dir *new);
lst_dir			*lstlast(lst_dir *lst);
t_lst_arr		*new_node_arr(char *line);
void			lstadd_back_arr(t_lst_arr **lst, t_lst_arr *new);
t_lst_arr		*lstlast_arr(t_lst_arr *lst);
int				get_real_hor_pos(char *str);
int				correct_var(s_variables *var, lst_dir *lst, int *i, int max);

//CHECKER
unsigned int	check_header(s_variables *var, lst_dir *lst, int *add_i);
void			check_errors(s_variables *var, lst_dir *lst);
void			remove_extra_spaces(s_variables *var, lst_dir *lst, int i);
void			remove_last_spaces(s_variables *var, lst_dir *lst, int i);
bool			remove_mid_spaces(s_variables *var, lst_dir *lst, int i);
void			remove_extra_spaces_2(s_variables *var, lst_dir *lst, int i);
void			remove_btw_semicolon(s_variables *var, lst_dir *lst, int i);
int				check_name_prototipe(s_variables *var, lst_dir *lst, int j, int i);
void			check_prototipe_func(s_variables *var, lst_dir *lst, int i, bool proto);
void			correct_misaligned(lst_dir *lst, int i, int max, int num_tabs);
void			mark_empty_line(lst_dir *lst, int i, bool error);
bool			ft_empty_line(char *line);
int				ft_strchr_nocomented(char *str, char c);
char			*new_old_str(char *new, char *old);

//FUNCIONES UTILES
int				count_indentations(char *str);

void			check_operators(s_variables *var, lst_dir *lst, int *i);
void			check_keywords(s_variables *var, lst_dir *lst, int *i);

int				is_keyword(s_variables *var, lst_dir *lst, int i, char **keywords);
int				type_keyword(s_variables *var, lst_dir *lst, int i, char **keywords);

//CHECKER _H
void			check_errors_h(s_variables *var, lst_dir *lst);

//PRINT ERROR
void			print_error(lst_dir *lst, char *msg_error, int line, int code_error);
void			print_error_var(lst_dir *lst, char *msg_error, int line, int code_error);
void			print_error_nopath(char *msg_error, int code_error);

void			confirmacion_replace(s_variables *var);
void			grade_the_app(s_variables *var);

//PRINT INFORMATION
void			print_num_errors(s_variables *var, lst_dir *lst);
void			print_header_program(void);
void			line_help(char *letter, char *message);
void			print_help(void);

#endif

