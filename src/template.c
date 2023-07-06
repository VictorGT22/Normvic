/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:14:22 by vics              #+#    #+#             */
/*   Updated: 2023/07/05 22:02:37 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normez.h"

void	print_linked(lst_dir *lst)
{
	lst_dir	*temp;

	temp = lst;
	while (temp)
	{
		printf("path: %s\n", temp->path);
		temp = temp->next;
	}
}

int	get_postfix(char *str, char *postfix)
{
	int i;
	int j;

	i = ft_strlen(str) - 1;
	j = ft_strlen(postfix) - 1;
	while (i >= 0 && j >= 0)
	{
		if (str[i] != postfix[j])
			return (0);
		j--;
		i--;
	}
	return (1);
}

int	get_directories(s_variables *var, char *filepath)
{
	DIR *dp;
	char *str;
	lst_dir *node;
	struct dirent *dirp;
	struct stat fileStat;

	dp = opendir(filepath);
	while ((dirp = readdir(dp)) != NULL)
	{
		str = ft_strjoin(filepath, dirp->d_name);
		node = new_node(str);
		if (!node)
			return (-1);
		stat(str, &fileStat);
		if (dirp->d_name[0] != '.' && dirp->d_name[1] != '.' && S_ISDIR(fileStat.st_mode))
			lstadd_back(&var->lst_dir, node);
		else if (dirp->d_name[0] != '.' && dirp->d_name[1] != '.'
		&& (get_postfix(dirp->d_name, ".c") || get_postfix(dirp->d_name, ".h")))
			lstadd_back(&var->lst_files, node);
	}
	closedir(dp);
	return (0);
}

int	get_number_lines_fd(char *filepath)
{
	int fd;
	char buffer;
	int bytesread;
	int lines;

	bytesread = 1;
	lines = 0;
	fd = open(filepath, O_RDONLY);
	while (bytesread)
	{
		bytesread = read(fd, &buffer, 1);
		if (bytesread && buffer == '\n')
			lines++;
	}
	close(fd);
	return (lines);
}

void	save_data_files(s_variables *var)
{
	int i;
	int lines;
	int fd;
	lst_dir *tmp;	

	tmp = var->lst_files;
	while (tmp)
	{
		lines = get_number_lines_fd(tmp->path);
		tmp->info = calloc(sizeof(char *), lines + 2);
		if (!tmp->info)
		{
			ft_printf("ERROR MALLOC\n");
			exit(0);
		}
		fd = open(tmp->path, O_RDONLY);
		i = 0;
		while (i <= lines)
		{
			tmp->info[i] = get_next_line(fd);
			i++;
		}
		tmp->info[i] = NULL;
		close(fd);
		tmp = tmp->next;	
	}	
}

void	print_header_program(void)
{
	purple();
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


void line_help(char *letter, char *message)
{
	purple();
	printf("║   ");
	blue();
	printf("-%s:\t\t", letter);
	reset();
	printf("%-25s", message);
	purple();
	printf("	  ║\n");
	printf("║						  ║\n");
}

void print_help(void)
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
	line_help("R", "Rate the app");
	printf("╚═════════════════════════════════════════════════╝\n");
}

void	check_flags(s_variables *var, char **arr)
{
	var->flags->all = true;
	var->flags->replace = false;
	var->flags->only_c = false;
	var->flags->only_h = false;
	var->flags->rate = false;
	
	
	if (ft_is_inarr(arr, "h"))
		var->flags->help = true;
	if (ft_is_inarr(arr, "r"))
		var->flags->replace = true;
	if (ft_is_inarr(arr, "C"))
	{
		var->flags->only_c = true;
		var->flags->all = false;
	}
	if (ft_is_inarr(arr, "H"))
	{
		var->flags->all = false;
		var->flags->only_h = true;
	}
	if (ft_is_inarr(arr, "R"))
		var->flags->rate = true;
}

void save_flags(s_variables *var, char **argv)
{
	int i;
	int j;
	char *str;
	int index;
	char **arr;

	i = 1;
	arr = malloc(sizeof(char *) * 3);
	arr[0] = NULL;
	while (argv[i])
	{
		index = ft_strchr_nocomented(argv[i], '-');
		if (index != -1)
		{
			j = 0;
			str = ft_substr(argv[i], index + 1, ft_strlen(argv[i]));
			while (str[j])
			{
				arr = ft_add_chr_arr(arr, str[j], 1);
				j++;
			}
			//free(str);
		}
		i++;
	}
	check_flags(var, arr);
}

void	check_path(lst_dir *lst)
{
	int i;

	i = 0;
	while (lst->path[i])
	{
		if (ft_isalpha(lst->path[i]) && lst->path[i] != ft_tolower(lst->path[i]))
			print_error(lst, ERROR_FILE_NAME, -1, NOSOLVABLE);
		i++;
			
	}
}

int	main(int argc, char **argv)
{
	lst_dir *tmp;
	lst_dir *node;
	s_variables *var;

	var = malloc(sizeof(s_variables) * 1);
	var->flags = malloc(sizeof(t_flags) * 1);

	/// checkear flags
	save_flags(var, argv);
	if (var->flags->help)
	{
		print_help();
	}
	else if (var->flags->rate)
			grade_the_app(var);
	else
	{
		var->lst_dir = NULL;
		var->lst_files = NULL;
		var->var_type = NULL;
		var->var_bad_decl = NULL;
		var->var_bad_line = NULL;
		node = new_node(".");
		if (!node)
			return (-1);
		lstadd_back(&var->lst_dir, node);
		tmp = var->lst_dir;
		while (tmp)
		{
			get_directories(var, ft_strjoin(tmp->path, "/"));
			tmp = tmp->next;
		}
		print_header_program();
		/*LINKEDS Y ARR*/
		var->keywords = ft_split(KEY_WORDS, ',');
		var->operators = ft_split(OPPERATORS_BOTH_SPACE, ',');
		var->operators = ft_add_chr_arr(var->operators, ',', 0);

		var->operators_nospace = ft_split(OPPERATORS_NO_SPACE, ',');
		int i = 0;
		t_lst_arr *node2;
		save_data_files(var);
		tmp = var->lst_files;
		if (var->flags->replace)
			confirmacion_replace(var);
		int len;
		while (tmp)
		{
			int i = 0;
			tmp->no_error = 0;
			tmp->err_solved = 0;
			tmp->err_nosolved = 0;
			if (get_postfix(tmp->path, ".h") && (var->flags->only_h || var->flags->all))
			{
				check_path(tmp);
				check_errors_h(var, tmp);
			}
			else if (get_postfix(tmp->path, ".c") && (var->flags->only_c || var->flags->all))
			{
				check_path(tmp);
				check_errors(var, tmp);
					
				if (!tmp->no_error)
				{
					purple();
					printf("File:\t");
					green();
					printf("[%s] -> OK 😊\n", tmp->path);
				}
				else
				{
					purple();
					printf("NUM ERRORS:\t");
					green();
					printf("[%d]\n", tmp->no_error);
					purple();
					printf("SOLVED:\t\t");
					green();
					printf("[%d]\n", tmp->err_solved);
					purple();
					printf("NO SOLVED:\t");
					green();
					printf("[%d]\n", tmp->err_nosolved);
				}
			}
			if (var->flags->replace)
			{
				int fd = open(tmp->path, O_WRONLY | O_TRUNC);
				while (tmp->info[i])
				{
					len = ft_strlen(tmp->info[i]);
					if (ft_strcmp(tmp->info[i], "@#~#@\n") != 0)
						write (fd, tmp->info[i], len);
					i++;
				}
				close(fd);
			}
			tmp = tmp->next;
		}
	}	
	return (0);
}