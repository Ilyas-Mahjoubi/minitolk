/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:54:35 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/02/03 01:56:46 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void    take_signal(int sig, siginfo_t *info, void *content)
{
    static int  c = 0; // Holds the current received character
    static int  i = 0; // Counts the bits

    (void)content;  // Unused parameter

    // Shift the current character and set the bit based on the signal
    if (sig == SIGUSR2)
        c = c << 1;          // For SIGUSR2, the bit is 0
    else if (sig == SIGUSR1)
        c = c << 1 | 0b00000001;  // For SIGUSR1, the bit is 1

    i++;

    // When 8 bits are received, print the character
    if (i == 8)
    {
        write(1, &c, 1);   // Print the received character
        i = 0;             // Reset bit counter
        c = 0;             // Reset the character accumulator

        // Send acknowledgment signal back to client (if needed)
        if (kill(info->si_pid, SIGUSR1) == -1)
            perror("Unable to send acknowledgment SIGUSR1");
    }
}

int main(void)
{
    struct sigaction sa_sig;

    // Print server PID to be used by the client
    printf("Server PID: %d\n", getpid());
    // Initialize sigaction structure
    sa_sig = (struct sigaction){0};
    // Set up the signal handler function for SIGUSR1 and SIGUSR2
    sa_sig.sa_sigaction = &take_signal;
    sa_sig.sa_flags = SA_SIGINFO;  // Use SA_SIGINFO to get additional information
    // Register the signal handlers for SIGUSR1 and SIGUSR2
    if (sigaction(SIGUSR1, &sa_sig, NULL) == -1)
    {
        perror("Error registering SIGUSR1 handler");
        return 1;
    }
    if (sigaction(SIGUSR2, &sa_sig, NULL) == -1)
    {
        perror("Error registering SIGUSR2 handler");
        return 1;
    }
    // Infinite loop to keep the server running and listening for signals
    while (1)
        pause();  // Wait for signals to arrive

    return 0;
}