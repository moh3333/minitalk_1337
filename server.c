/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:10:14 by mthamir           #+#    #+#             */
/*   Updated: 2024/03/16 15:32:54 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_putchr(char a)
{
	write(1, &a, 1);
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

static void	handle_signal(int s, siginfo_t *sender, void *context)
{
	static int	i = 0;
	static char	c = 0;
	static int	client_pid;

	context = NULL;
	if (client_pid == 0)
		client_pid = sender->si_pid;
	if (sender->si_pid != client_pid)
	{
		i = 0;
		c = 0;
		client_pid = sender->si_pid;
	}
	c += (s == SIGUSR2);
	i++;
	if (i == 8)
	{
		ft_putchr(c);
		i = 0;
		c = 0;
	}
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
	if (sigaction(SIGUSR1, &act, NULL) == -1)
	{
		write (2, "SIGACTION FUNC FAILS", 20);
		return (1);
	}
	if (sigaction(SIGUSR2, &act, NULL) == -1)
	{
		write (2, "SIGACTION FUNC FAILS", 20);
		return (1);
	}
	while (1)
		pause();
}
