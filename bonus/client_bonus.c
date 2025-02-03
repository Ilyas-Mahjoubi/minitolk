/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:38:03 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/02/01 20:38:03 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r')))
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

static void	ft_ascii_to_bit(char c, int pid)
{
	int	mask;

	mask = 0b10000000;
	while (mask)
	{
		if (c & mask)
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				ft_printf("Unable to send Message\n");
				exit(1);
			}
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				ft_printf("Unable to send Message\n");
				exit(1);
			}
		}
		usleep(800);
		mask >>= 1;
	}
}

static void	ft_str_to_bit(char *str, int pid)
{
	while (*str)
	{
		ft_ascii_to_bit(*str, pid);
		str++;
	}
}

static void	signal_handler(int sig)
{
	static int	message_received;

	if (!message_received)
	{
		if (sig == SIGUSR1)
		{
			ft_printf("Message received by server\n");
			message_received = 1;
		}
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;

	sa = (struct sigaction){0};
	if (argc == 3)
	{
		sa.sa_handler = &signal_handler;
		sa.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pid = ft_atoi(argv[1]);
		if (!pid || pid < 0)
		{
			printf("Error : Wrong process ID !\n");
			exit (0);
		}
		ft_str_to_bit(argv[2], pid);
	}
	else
		printf("Error : Too few or too many arguments !\n");
}
