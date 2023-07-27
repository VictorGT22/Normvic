/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dentro_carpetA.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vics <vics@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:14:22 by vics              #+#    #+#             */
/*   Updated: 2023/07/27 14:59:03 by vics             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "template.h"
#include <time.h>

t_variables *global_var = NULL;

void 	signalhandler(int signal)
{
	global_var->error_reciving = 1;
}

void 	signalhandler_2(int signal)
{
	global_var->error_reciving = 0;
}

int	send_bit(char str, int i)
{
	if (str & (1 < < i))
	{
		kill(global_var->pid, SIGUSR1);
		return (1);
	}
	else
	{
		kill(global_var->pid, SIGUSR2);
		return (0);
	}
	return (-1);
}

void	stringtobits(char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (0x01 < < bit)))
			kill(global_var->pid, SIGUSR1);
		else
			kill(global_var->pid, SIGUSR2);
		usleep(500);
		bit++;
	}
}

int	main(int argc, char **argv)
{
	int			i;
	const char	*texto;
	int			peticion;

	global_var = malloc(sizeof(t_variables));
	global_var->bauds_pause = 5000;
	global_var->personal_pid = getpid();
	global_var->pid = ft_atoi(argv[1]);
	global_var->error_reciving = false;
	printf("PID CLIENTE: %d\n", global_var->personal_pid);
	printf("PID SERVER: %d\n", global_var->pid);
	printf("vel: %d\n", global_var->bauds_pause);
	signal(SIGUSR1, &signalHandler);
	signal(SIGUSR2, &signalHandler_2);
	peticion = 1;
	printf("Peticion conexion: %d\n", peticion);
	printf("\nENVIANDO TEXTO\n");
	texto = argv[2];
	if (peticion)
	{
		i = 0;
		while (texto[i])
		{
			stringtobits(texto[i]);
			i++;
		}
	}
}
