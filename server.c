#include "minitalk.h"
#include "utils.h"

void	bit_masking(char *c, int check)
{
	*(int *)c = *c << 1;
	if (check == 2)
		*c |= ADD_BIT;
}

void	len_handler(int sig, siginfo_t *info, void *context)
{
	static t_info	len;
	static int		i;
	static int		cnt;

	if (i == 0)
		g_client_pid = info->si_pid;
	if (info->si_pid != g_client_pid)
	{
		kill(g_client_pid, SIGUSR1);
		sigerror();
	}
	cnt++;
	if (sig == SIGUSR1)
		bit_masking(&(len.arr[i]), 1);
	else
		bit_masking(&(len.arr[i]), 2);
	if (cnt == 8)
	{
		if (i == 3)
		{
			g_str_len = len.num;
			printf("strlen : %d\n", g_str_len);
		}
		i++;
		cnt = 0;
	}
	kill(g_client_pid, SIGUSR2);
}

void	str_handler(int sig, siginfo_t *info, void *context)
{
	static char	c;
	static int	len;//static변수는 초기화하지 않아도 0으로 초기화됨.

	//printf("str_len : %d\n", g_str_len);
	if (info->si_pid != g_client_pid)
	{
		kill(g_client_pid, SIGUSR1);
		sigerror();
	}
	if (len == 0)
		c = 0;
	len++;
	if (sig == SIGUSR1)
		bit_masking(&c, 1);
	else
		bit_masking(&c, 2);
	if (len == 8)
	{
		print_char(c);
		len = 0;
		c = 0;
	}
	kill(g_client_pid, SIGUSR2);
}

int	main(void)
{
	//pid_t는 언사인드 인트 32비트
	//클라이언트에서 처음 4바이트를 클라이언트 pid값을 보내면
	//서버에서는 최초 클라이언트의 pid값을 알 수 있다.
	pid_t	pid;
	struct sigaction	act;

	g_str_len = 0;
	g_client_pid = 0;
	pid = getpid();
	ft_putnbr(pid);
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);
	act.sa_flags = SA_SIGINFO;
	if (g_str_len == 0)
		act.sa_sigaction = len_handler;
	else
		act.sa_sigaction = str_handler;
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	while (1)
		pause();
	return (0);
}