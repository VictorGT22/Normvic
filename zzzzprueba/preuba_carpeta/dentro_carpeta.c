/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dentro_carpeta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victgonz <victorgonzalez@42bcn.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 23:29:01 by victgonz          #+#    #+#             */
/*   Updated: 2023/07/08 23:29:01 by victgonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
	int i;
	int len;
	lst_dir *tmp;

	tmp = var->lst_files;
	while (tmp)
	{
		if (get_postfix(tmp->path, ".h"))
			while (tmp->info[i])
	{
		if (ft_strnstr(tmp->info[i], "{", len))
			tmp->num_key++;
		i++;
	}
	printf("%s\n", tmp->path);
	tmp = tmp->next;
}
*/

lst_dir	*new_node(char*filepath);

void	ft_striteri(char *str, void(*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		f(i, &str[i]);
		i++;
	}
}
