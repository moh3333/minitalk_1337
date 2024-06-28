/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:21:44 by mthamir           #+#    #+#             */
/*   Updated: 2024/03/16 15:48:20 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	ft_putchr(char c)
{
	write(1, &c, 1);
}

static void	putnbr(int nb)
{
	if (nb < 0)
	{
		ft_putchr('-');
		nb = -nb;
	}
	if (nb >= 0 && nb <= 9)
		ft_putchr(nb + 48);
	if (nb > 9)
	{
		putnbr(nb / 10);
		ft_putchr((nb % 10) + 48);
	}
}

static void	print_char(char *c, pid_t s_id, int *i)
{
	if (*c == '\n')
	{
		ft_putchr('\n');
		kill (s_id, SIGUSR2);
		return ;
	}
	ft_putchr(*c);
	*c = 0;
	*i = 0;
}

static void	handle_signal(int s, siginfo_t *sender, void *context)
{
	static int	i;
	static char	c;
	static int	client_pid;

	context = NULL;
	if ((sender->si_pid != client_pid) && client_pid != 0)
	{
		i = 0;
		c = 0;
		client_pid = sender->si_pid;
	}
	client_pid = sender->si_pid;
	c += (s == SIGUSR2);
	i++;
	if (i == 8)
		print_char(&c, sender->si_pid, &i);
	c <<= 1;
}

int	main(void)
{
	struct sigaction	act;

	write (1, "The server PID : ", 17);
	putnbr(getpid());
	ft_putchr ('\n');
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = handle_signal;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
}
