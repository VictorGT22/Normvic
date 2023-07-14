/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:14:22 by vics              #+#    #+#             */
/*   Updated: 2023/07/14 13:19:14 by vics             ###   ########.fr       */
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

void	replace_name_file(char *to_find, char *to_replace)
{
	if (rename(to_find, to_replace))
		printf("Error changing the name");
}

int	check_repo(s_variables *var)
{
	DIR *dp;
	char *str;
	struct dirent *dirp;
	struct stat fileStat;

	dp = opendir(".");
	while ((dirp = readdir(dp)) != NULL)
	{
		str = ft_strdup(dirp->d_name);
		stat(str, &fileStat);
		ft_str_toupper(str);
		if (dirp->d_name[0] != '.' && dirp->d_name[1] != '.' && !ft_strcmp(str, "MAKEFILE"))
		{
			closedir(dp);
			return (1);
		}
	}
	closedir(dp);
	return (0);
}

int	get_directories(s_variables *var, char *filepath)
{
	DIR *dp;
	char *str;
	char *str2;
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
		str2 = ft_strdup(dirp->d_name);
		ft_str_toupper(str2);
		if (dirp->d_name[0] != '.' && dirp->d_name[1] != '.' && S_ISDIR(fileStat.st_mode))
			lstadd_back(&var->lst_dir, node);
		else if (dirp->d_name[0] != '.' && dirp->d_name[1] != '.'
		&& (get_postfix(dirp->d_name, ".c") || get_postfix(dirp->d_name, ".h") || !ft_strcmp(str2, "MAKEFILE")))
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
			printf("ERROR MALLOC\n");
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

void	check_flags(s_variables *var, char **arr)
{
	var->flags->all = true;
	var->flags->replace = false;
	var->flags->only_c = false;
	var->flags->only_h = false;
	var->flags->rate = false;
	var->flags->update = false;
	var->flags->show_ok = true;
	
	
	if (ft_is_inarr(arr, "i") || ft_is_inarr(arr, "I"))
		var->flags->help = true;
	if (ft_is_inarr(arr, "r") || ft_is_inarr(arr, "R"))
		var->flags->replace = true;
	if (ft_is_inarr(arr, "c") || ft_is_inarr(arr, "C"))
	{
		var->flags->only_c = true;
		var->flags->all = false;
	}
	if (ft_is_inarr(arr, "h") || ft_is_inarr(arr, "H"))
	{
		var->flags->all = false;
		var->flags->only_h = true;
	}
	if (ft_is_inarr(arr, "g") || ft_is_inarr(arr, "G"))
		var->flags->rate = true;
	if (ft_is_inarr(arr, "u") || ft_is_inarr(arr, "U"))
		var->flags->update = true;
	if (ft_is_inarr(arr, "s") || ft_is_inarr(arr, "S"))
		var->flags->show_ok = false;
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
				arr = ft_add_chr_arr(arr, str[j], 0);
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

void	update_normvic(s_variables *var)
{
	int res;
	char path[256];


	if (var->home_path != NULL) {
        strcpy(path, var->home_path);
        strcat(path, PATH_UPDATE);
	}
	printf("PATH: %s\n", path);
	res = system(path);
    if (res == -1)
        printf("Can not execute update.sh\n");
	else
        printf("Archivo update.sh ejecutado exitosamente\n");
}

void	save_header(s_variables *var)
{
	var->header = malloc(sizeof(char *) * 12);
	var->header[0] = "/* ************************************************************************** */\n";
	var->header[1] = "/*                                                                            */\n";
	var->header[2] = "/*                                                        :::      ::::::::   */\n";
	var->header[3] = "/*                                                      :+:      :+:    :+:   */\n";
	var->header[4] = "/*                                                    +:+ +:+         +:+     */\n";
	var->header[5] = "/*   By:                                            +#+  +:+       +#+        */\n";
	var->header[6] = "/*                                                +#+#+#+#+#+   +#+           */\n";
	var->header[7] = "/*   Created:                                          #+#    #+#             */\n";
	var->header[8] = "/*   Updated:                                         ###   ########.fr       */\n";
	var->header[9] = "/*                                                                            */\n";
	var->header[10] = "/* ************************************************************************** */\n";
	var->header[11] = NULL;
}

void	save_user_data(s_variables *var)
{
	int fd;
	int start;
	char *str;
    char path[256];

	
    if (var->home_path != NULL) {
        strcpy(path, var->home_path);
        strcat(path, "/Normvic/settings/config_user");
	}
	fd = open(path, O_RDONLY);
	if (fd != -1)
	{
		printf("USER DATA SAVED\n");
		str = get_next_line(fd);
		start = ft_strchr_nocomented(str, ':');
		var->user = ft_substr(str, start, ft_strlen(str) - start);
		var->user = new_old_str(ft_strtrim(var->user, " \t\n:"), var->user);
		free(str);
		str = get_next_line(fd);
		start = ft_strchr_nocomented(str, ':');
		var->user_email = ft_substr(str, start, ft_strlen(str) - start);
		var->user_email = new_old_str(ft_strtrim(var->user_email, " \t\n:"), var->user_email);
		free(str);
	}
	else
		printf("ERROR OPEN SETTINGS\n");
	close(fd);
}

int	main(int argc, char **argv)
{
	lst_dir *tmp;
	lst_dir *node;
	s_variables *var;

	var = calloc(sizeof(s_variables), 1);
	var->flags = calloc(sizeof(t_flags), 1);

	save_flags(var, argv);
	print_logo();
	print_header_program();
	var->home_path = getenv("HOME");
	if (var->flags->update)
		update_normvic(var);
	else if (var->flags->help)
		print_help();
	else if (var->flags->rate)
			grade_the_app(var);
	else
	{
		var->lst_dir = NULL;
		var->lst_files = NULL;
		var->var_type = NULL;
		var->var_bad_decl = NULL;
		var->var_bad_line = NULL;
		var->user = "username";
		var->user_email = "username@email.42";
		var->keywords = ft_split(KEY_WORDS, ',');
		var->keywords_indent = ft_split(KEY_WORDS_INDENT, ',');
		var->operators = ft_split(OPPERATORS_BOTH_SPACE, ',');
		var->operators = ft_add_chr_arr(var->operators, ',', 0);
		var->op_divide = ft_split(OPPERATORS_DIVIDE, ',');

		if (check_repo(var))
		{
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
			
			/*LINKEDS Y ARR*/
			
			save_header(var);
			save_user_data(var);
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
				char *str;
				char *str2;

				tmp->no_error = 0;
				tmp->err_solved = 0;
				tmp->err_nosolved = 0;
				tmp->line_compensation = 0;
				int index = ft_strrchr_index(tmp->path, '/') + 1;
				str = ft_substr(tmp->path, index, ft_strlen(tmp->path) - index);
				str2 = strdup(str);
				ft_str_toupper(str2);
				if (get_postfix(tmp->path, ".h") && (var->flags->only_h || var->flags->all))
				{
					check_path(tmp);
					check_errors_h(var, tmp);
					print_num_errors(var, tmp);
				}
				else if (get_postfix(tmp->path, ".c") && (var->flags->only_c || var->flags->all))
				{
					check_path(tmp);
					check_errors(var, tmp);
					print_num_errors(var, tmp);
				}
				else if (!ft_strcmp(str2, "MAKEFILE") && (!ft_str_islower(&str[1]) || !ft_isupper(str[0])))
				{
					print_error(tmp, ERROR_MAKEFILE, 0, SOLVABLE);
					if (var->flags->replace)
						replace_name_file(str, "Makefile");
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
		else
			print_error_nopath(ERROR_REPO, NOSOLVABLE);
	}	
	return (0);
}