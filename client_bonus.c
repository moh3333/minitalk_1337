/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:21:50 by mthamir           #+#    #+#             */
/*   Updated: 2024/03/16 16:09:52 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

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
	static int	x;

	x = 0;
	while (x < 8)
	{
		if (c & 128)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(500);
		c <<= 1;
		x++;
	}
}

static void	send_msg(char *msg, pid_t pid)
{
	static int	i;

	while (msg[i])
	{
		send_sig(msg[i], pid);
		i++;
	}
	send_sig('\0', pid);
	send_sig('\n', pid);
}

static void	recived(int sig)
{
	if (sig == SIGUSR2)
		write(1, "Message received successfully ✅\n", 34);
}

int	main(int ac, char **av)
{
	pid_t	pid ;

	signal(SIGUSR2, recived);
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (pid <= 0)
		{
			write (2, "Invalid PID\n", 12);
			exit(1);
		}
		send_msg(av[2], pid);
	}
	else
		write (2, "The Correct Usage is : ./client [PID] [Your Message]\n", 53);
}
