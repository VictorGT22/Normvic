/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:37:15 by vics              #+#    #+#             */
/*   Updated: 2023/07/08 03:47:45 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normez.h"

void	gray(void)
{
	printf("\033[1;30m");
}

void	red(void)
{
	printf("\033[1;31m");
}

void	green(void)
{
	printf("\033[1;32m");
}

void	yellow(void)
{
	printf("\033[1;33m");
}

void	blue(void)
{
	printf("\033[1;34m");
}

void	purple(void)
{
	printf("\033[1;35m");
}

void	cyan(void)
{
	printf("\033[1;36m");
}

void	blanco(void)
{
	printf("\033[1;37m");
}

void	reset()
{
	printf("\033[0m");
}

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
