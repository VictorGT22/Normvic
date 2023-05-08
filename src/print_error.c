/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:37:15 by vics              #+#    #+#             */
/*   Updated: 2023/05/07 11:19:55 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normez.h"

void	red()
{
  printf("\033[1;31m");
}

void	yellow()
{
  printf("\033[1;33m");
}

void	reset() {
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
	}
}

void	print_error(char *path, char *msg_error, int line, int code_error)
{
	get_code_color(code_error);
	printf("[File: %12s -> Line: %3d]:", path, line);
	get_code_color(0);
	printf("\t%s\n", msg_error);
}