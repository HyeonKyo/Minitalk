#include "minitalk.h"
#include "utils.h"

void	bit_masking(char *c, int signo)
{
	*c = *c << 1;
	if (signo == SIGUSR2)
		*c |= ADD_BIT;
}

void	get_client_pid(siginfo_t *info)
{
	if (g_client_pid <= 0)
		g_client_pid = info->si_pid;
}

void	check_incorrect_pid(siginfo_t *info)
{
	if (info->si_pid != g_client_pid)
	{
		kill(g_client_pid, SIGUSR1);
		kill(info->si_pid, SIGUSR1);
		g_client_pid = 0;
		sigerror();
	}
}

void	len_handler(int sig, siginfo_t *info, void *context)
{
	static t_info	len;
	static int		i;
	static char		c;
	static int		cnt;
	static int		fg;

	get_client_pid(info);
	check_incorrect_pid(info);
	if (fg == 0)
		bit_masking(&(len.arr[i]), sig);
	else
		bit_masking(&c, sig);
	cnt++;
	if (fg == 0 && cnt % 8 == 0)
	{
		i++;
		if (i == 4)
			fg = 1;
		cnt = 0;
	}
	else if (cnt % 8 == 0)
	{
		print_char(c);
		c = 0;
		if (cnt / 8 == len.num)
		{
			write(1, "\n", 1);
			kill(g_client_pid, SIGUSR2);
			usleep(500);
			kill(g_client_pid, SIGUSR2);
			g_client_pid = -1;
			len.num = 0;
			cnt = 0;
			fg = 0;
			i = 0;
			return ;
		}
	}
	usleep(120);
	kill(g_client_pid, SIGUSR2);
}

int	main(void)
{
	//pid_t는 언사인드 인트 32비트
	//클라이언트에서 처음 4바이트를 클라이언트 pid값을 보내면
	//서버에서는 최초 클라이언트의 pid값을 알 수 있다.
	pid_t	pid;
	t_act	act;

	g_str_len = 0;
	g_client_pid = 0;
	pid = getpid();
	ft_putnbr(pid);
	setup_act(&act, len_handler);
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	while (1)
		pause();
	return (0);
}
