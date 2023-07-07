/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:43:01 by vics              #+#    #+#             */
/*   Updated: 2023/07/07 17:47:37 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <ctype.h>

# define WRONG 4
# define SOLVABLE 3

# ifndef BUFFER_SIZE
#  define WHAT 1000
# endif

int		ft_isalpha(char c);
int		ft_strlen(const char *str);
int		ft_arrlen(char **arr);
void	*ft_memchr(const void *str, int c, size_t n);

typedef struct lst_dir
{
	char			*path;
	char			**info;
	int				num_functions;
	struct lst_dir	*next;
	struct lst_dir	*prev;
}	lst_dir;

#endif
