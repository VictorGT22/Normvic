/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:46:48 by vics              #+#    #+#             */
/*   Updated: 2023/07/11 19:20:16 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normez.h"

void	print_num_errors(s_variables *var, lst_dir *lst)
{
	if (!lst->no_error && var->flags->show_ok)
	{
		purple();
		printf("File:\t");
		green();
		printf("[%s] -> OK 😊\n", lst->path);
	}
	else if (lst->no_error)
	{
		purple();
		printf("NUM ERRORS:\t");
		green();
		printf("[%d]\n", lst->no_error);
		purple();
		printf("SOLVED:\t\t");
		green();
		printf("[%d]\n", lst->err_solved);
		purple();
		printf("NO SOLVED:\t");
		green();
		printf("[%d]\n\n\n", lst->err_nosolved);
	}
}

void	print_header_program(void)
{
	cyan();
	printf("╔═════════════════════════════════════════╗\n");
	printf("║		");
	blue();
	printf("NORMVIC  ");
	green();
	printf("(ALFA)");
	purple();
	printf("		  ║\n");
	printf("╚═══════════════╦═════════╦═══════════════╝\n");
	printf("		║  ");
	green();
	printf("VIC's");
	purple();
	printf("  ║\n");
	printf("		╚═════════╝\n");
}


void	line_help(char *letter, char *message)
{
	purple();
	printf("║   ");
	cyan();
	printf("%-4s:\t", letter);
	reset();
	printf("%-25s", message);
	purple();
	printf("%12s", "║");
	printf("\n");
	printf("║						  ║\n");
}

void	print_help(void)
{
	purple();
	printf("╔═════════════════════════════════════════════════╗\n");
	
	//RED
	purple();
	printf("║   ");
	red();
	printf("🔴\t  ");
	reset();
	printf("ERROR NO FIXABLE");
	purple();
	printf("	  		  ║\n");
	printf("║						  ║\n");

	//GREEN
	purple();
	printf("║   ");
	green();
	printf("🟢\t  ");
	reset();
	printf("ERROR FIXABLE");
	purple();
	printf("		  		  ║\n");
	printf("║						  ║\n");


	//YELLOW
	purple();
	printf("║   ");
	yellow();
	printf("🟡\t  ");
	reset();
	printf("WHY YOU MAKE THIS ERROR? :')");
	purple();
	printf("		  ║\n");
	printf("║						  ║\n");
	line_help("r", "Replace the errors");
	line_help("C", "Check only .c files");
	line_help("H", "Check only .h files");
	line_help("s/S", "Don't show ok files");
	line_help("R", "Rate the app");
	line_help("u/U", "Update latest version");
	printf("╚═════════════════════════════════════════════════╝\n");
}

