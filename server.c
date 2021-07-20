#include "minitalk.h"
#include "utils.h"

void	bit_masking(char *c, int check)
{
	*c = *c << 1;
	if (check == 2)
		*c |= ADD_BIT;
}

void	handler(int signo)
{
	static char	c;
	static int	len;//static변수는 초기화하지 않아도 0으로 초기화됨.

	if (len == 0)
		c = 0;
	len++;
	if (signo == SIGUSR1)
		bit_masking(&c, 1);
	else
		bit_masking(&c, 2);
	if (len == 8)
	{
		print_char(c);
		len = 0;
		c = 0;
		return ;
	}
}

int	main(void)
{
	//pid_t는 언사인드 인트 32비트
	//클라이언트에서 처음 4바이트를 클라이언트 pid값을 보내면
	//서버에서는 최초 클라이언트의 pid값을 알 수 있다.
	pid_t	pid;
	struct sigaction	act;

	pid = getpid();
	ft_putnbr(pid);
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);
	act.sa_handler = handler;
	act.sa_flags = 0;
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	while (1)
		pause();
	return (0);
}