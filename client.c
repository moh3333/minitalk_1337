/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:37:40 by mthamir           #+#    #+#             */
/*   Updated: 2024/03/16 15:59:54 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_atoi(char *str)
{
	int	result;

	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + *str - 48;
		str++;
		if (result > 99998)
		{
			write (2, "Invalid PID\n", 12);
			exit (1);
		}
	}
	return (result);
}

static void	send_sig(char c, pid_t pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & 128)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(500);
		c <<= 1;
		i++;
	}
}

static void	send_msg(char *msg, pid_t pid)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		send_sig(msg[i], pid);
		i++;
	}
	send_sig('\0', pid);
	send_sig('\n', pid);
}

int	main(int ac, char **av)
{
	pid_t	pid;

	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (pid <= 0)
		{
			write (2, "Invalid PID\n", 12);
			return (1);
		}
		send_msg(av[2], pid);
	}
	else
		write (2, "The Correct Usage is : ./client [PID] [Your Message]\n", 53);
	return (1);
}
