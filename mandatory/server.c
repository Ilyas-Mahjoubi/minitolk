/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:53:23 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/02/03 01:57:56 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void    signal_handler(int sig)
{
    static int  bit_position = 0;
    static char received_char = 0;

    if (sig == SIGUSR1)
        received_char |= (1 << (7 - bit_position));
    bit_position++;

    if (bit_position == 8)
    {
        write(1, &received_char, 1);
        bit_position = 0;
        received_char = 0;
    }
}

int main(void)
{
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);

    printf("Server PID: %d\n", getpid());

    while (1)
        pause();
}
