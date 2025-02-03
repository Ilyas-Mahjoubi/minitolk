/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:51:55 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/02/01 14:51:55 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
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

int	main(int argc, char **argv)
{
	int	pid;

	if (argc == 3)
	{
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
