#include "utils.h"
#include "minitalk.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	error(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(1);
}

void	print_num(unsigned int n, int *flag)
{
	char	c;

	if (n == 0 && *flag == 0)
	{
		write(1, "0", 1);
		return ;
	}
	if (n == 0)
		return ;
	*flag = 1;
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	print_num(n / 10, flag);
	c = n % 10 + '0';
	write(1, &c, 1);
}

void	ft_putnbr(unsigned int n)
{
	int	flag;

	flag = 0;
	print_num(n, &flag);
	write(1, "\n", 1);
}

void	print_char(char c)
{
	write(1, &c, 1);
}

void	*ft_memset(void *ptr, int value, size_t num)
{
	char	*str;
	size_t	i;

	i = 0;
	str = ptr;
	while (i < num)
		str[i++] = value;
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	mt_atoi(const char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - '0');
	return (num);
}

void	sigerror(void)
{
	write(2, "\nSignal error\n", 14);
	exit(1);
}

void	setup_act(t_act *act, void (*handler)(int, siginfo_t *, void *))
{
	sigemptyset(&(act->sa_mask));
	sigaddset(&(act->sa_mask), SIGUSR1);
	sigaddset(&(act->sa_mask), SIGUSR2);
	act->sa_sigaction = handler;
	act->sa_flags = SA_SIGINFO;
}