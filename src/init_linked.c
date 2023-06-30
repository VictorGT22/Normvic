/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_linked.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:28:24 by vics              #+#    #+#             */
/*   Updated: 2023/04/30 12:06:39 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normez.h"

lst_dir	*new_node(char *filepath)
{
	lst_dir	*node;

	node = malloc(sizeof(lst_dir) * 1);
	if (!node)
		return (NULL);
	node->path = filepath;
	node->next = NULL;
	return (node);
}

void	lstadd_back(lst_dir **lst, lst_dir *new)
{
	lst_dir	*temp;

	if (lst)
	{
		if (!(*lst))
		{
			*lst = new;
			(*lst)->prev = NULL;
		}
		else
		{
			temp = lstlast(*lst);
			temp->next = new;
			temp->next->prev = temp;
		}
	}
}

lst_dir	*lstlast(lst_dir *lst)
{
	lst_dir	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

t_lst_arr	*new_node_arr(char *line)
{
	t_lst_arr *node;

	node = malloc(sizeof(t_lst_arr) * 1);
	if (!node)
		return (NULL);
	node->str = line;
	node->next = NULL;
	return (node);
}

void	lstadd_back_arr(t_lst_arr **lst, t_lst_arr *new)
{
	t_lst_arr	*temp;

	if (lst)
	{
		if (!(*lst))
		{
			*lst = new;
			(*lst)->prev = NULL;
		}
		else
		{
			temp = lstlast_arr(*lst);
			temp->next = new;
			temp->next->prev = temp;
		}
	}
}

t_lst_arr	*lstlast_arr(t_lst_arr *lst)
{
	t_lst_arr	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}