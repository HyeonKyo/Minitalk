#ifndef MINITALK_H
# define MINITALK_H
# define ADD_BIT 1
# define MASK8 128
# define MASK7 64
# define MASK6 32
# define MASK5 16
# define MASK4 8
# define MASK3 4
# define MASK2 2
# define MASK1 1
#include <signal.h>
#include <stdio.h>

typedef union u_info
{
	unsigned int	num;
	char	arr[4];
}			t_info;

int	g_str_len;
pid_t	g_client_pid;
pid_t	g_server_pid;

void	send_message(char *str, int len);

#endif