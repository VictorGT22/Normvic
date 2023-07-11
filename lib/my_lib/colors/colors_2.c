/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:51:21 by vics              #+#    #+#             */
/*   Updated: 2023/07/11 13:20:40 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	purple(void)
{
	printf("\033[1;35m");
}

void	cyan(void)
{
	printf("\033[1;36m");
}

void	white(void)
{
	printf("\033[1;37m");
}

void	reset()
{
	printf("\033[0m");
}