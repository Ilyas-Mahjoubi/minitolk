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
	int	res;
	int	sgin;
	int	i;

	res = 0;
	sgin = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sgin *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10 + (str[i] - '0'));
		i++;
	}
	return (res * sgin);
}

static void ft_to_bit(char c, int pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (c >> i & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		i--;
	}
}

static void	ft_str_to_bit(char *str, int pid)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_to_bit(str[i], pid);
		i++;
	}
}
int main(int ac, char **av)
{
	int pid;

	if (ac != 3)
	{
		ft_printf("wrong number of arguments\n");
		return (0);
	}
	pid = ft_atoi(av[1]);
	if (!pid)
	{
		ft_printf("Error : Wrong process ID !\n");
		exit (0);
	}
	ft_str_to_bit(av[2], pid);
}