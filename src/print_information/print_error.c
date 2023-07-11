/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:56:06 by vics              #+#    #+#             */
/*   Updated: 2023/07/11 13:41:16 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normez.h"

void	get_code_color(int code)
{
	switch (code)
	{
		case 0:
			reset();
			break;	
		case 1:
			red();
			break;
		case 2:
			yellow();
			break;
		case 3:
			green();
			break;
	}
}

void	print_error_nopath(char *msg_error, int code_error)
{
	purple();
	printf("Error:\t");
	get_code_color(code_error);
	printf("%s\n", msg_error);
	get_code_color(0);
}

void	print_error(lst_dir *lst, char *msg_error, int line, int code_error)
{
	lst->no_error++;
	if (code_error == SOLVABLE)
		lst->err_solved++;
	else if (code_error == NOSOLVABLE)
		lst->err_nosolved++;
	purple();
	printf("File:\t");
	get_code_color(code_error);
	printf("[%-12s -> Line: %3d]:", lst->path, line - lst->line_compensation);
	get_code_color(0);
	printf("\t%s\n", msg_error);
}

void	print_error_var(lst_dir *lst, char *msg_error, int line, int code_error)
{
	lst->no_error++;
	if (code_error == SOLVABLE)
		lst->err_solved++;
	else if (code_error == NOSOLVABLE)
		lst->err_nosolved++;
	purple();
	printf("File:\t");
	get_code_color(code_error);
	printf("[%-12s -> Line: %3d]:", lst->path, line - lst->line_compensation);
	get_code_color(0);
	printf("\t%s", msg_error);
}
