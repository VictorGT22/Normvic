#ifndef STRUCT_H
# define STRUCT_H

#include <stdarg.h>

typedef struct t_list
{
	char			*parameter;
	char			**flag;
	int				num_flags;
	char			*width;
	char			*precision;
	char			conv;
	int				len;
	int				no_val_prec;
	int				index;
	int				current_total;
	struct t_list	*prev;
	struct t_list	*next;
}	t_list;

typedef struct s_func_ptr
{
    char op;
    int (*ptr)(va_list list, t_list *info);
} s_fnc_ptr;

typedef struct s_Main
{
	char		**flags;
	char		*conv;
	int 		num_conv;
	t_list		*first_ptr;
	t_list		*current_ptr;
	s_fnc_ptr	*arr_func;
	int			total_len;
}s_Main;


#endif