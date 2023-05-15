/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:14:22 by vics              #+#    #+#             */
/*   Updated: 2023/05/11 15:59:56 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normez.h"
	
void print_linked(lst_dir *lst)
{
	lst_dir *temp;

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

void	print_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		write(1, arr[i], ft_strlen(arr[i]));
		write(1, "\n", 1);
		i++;
	}	
}

int main()
{
	lst_dir *tmp;
	lst_dir *node;
	s_variables *var;

	var = malloc(sizeof(s_variables) * 1);
	var->lst_dir = NULL;
	var->lst_files = NULL;
	var->var_type = NULL;
	var->var_bad_decl = NULL;
	
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
	var->keywords = ft_split(KEY_WORDS, ',');
	var->operators = ft_split(OPPERATORS_BOTH_SPACE, ',');
	var->operators_nospace = ft_split(OPPERATORS_NO_SPACE, ',');
	char **type_vars = ft_split(TYPE_VAR, ',');
	int i = 0;
	
	t_lst_arr *node2;
	while (type_vars[i])
	{
		node2 = new_node_arr(type_vars[i]);
		if (!node2)
			return (-1);
		lstadd_back_arr(&var->var_type, node2);
		i++;
	}
	/*printf("KEY_WORDS:\n");
	print_array(var->keywords);
	
	printf("OPPERATORS:\n");
	print_array(var->operators);
	
	printf("TYPE_VAR:\n");
	print_array(var->var_type);*/

	save_data_files(var);
	
	
	//get_type_var(var);
	//printf("DIRECTORIES:\n");
	//print_linked(var->lst_dir);
	//printf("FILES:\n");
	//print_linked(var->lst_files);
	
	tmp = var->lst_files;
	bool replace = true;
	int len;
	while (tmp)
	{
		int i = 0;
		if (get_postfix(tmp->path, ".h"))
			check_errors_h(var, tmp);
		else if (get_postfix(tmp->path, ".c"))
			check_errors(var, tmp);
		
		if (replace == true)
		{
			int fd = open(tmp->path, O_WRONLY | O_TRUNC);
			while (tmp->info[i])
			{
				//printf("%s\n", tmp->info[i]);
				len = ft_strlen(tmp->info[i]);
				//printf("str 2: #%s#, linea: %d\n", tmp->info[i], i + 1);
				if (ft_strcmp(tmp->info[i], "@#~#@\n") != 0)
					write (fd, tmp->info[i], len);
				i++;
			}
			close(fd);
		}
		tmp = tmp->next;
	}
	printf("entra?\n");
	t_lst_arr *tmp2 = var->var_bad_decl;
	while (tmp2)
	{
		printf("bad: %s\n", tmp2->str);
		tmp2 = tmp2->next;
	}
	return (0);
}