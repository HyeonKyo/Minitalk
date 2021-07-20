#include "minitalk.h"
#include "utils.h"

int	check_pid(char *argv1)
{
	int	i;

	i = -1;
	while (argv1[++i])
	{
		if (!ft_isdigit(argv1[i]))
			exit(1);
	}
	return (ft_atoi(argv1));
}

void	send_len(pid_t serv_pid, unsigned int str_len, struct sigaction *act)
{
	t_info	info;
	
	ft_memset(&info, 0, sizeof(t_info));
	info.num = str_len;
	send_message(serv_pid, info.arr, act, 4);
}

int		return_mask_number(int mask_num)
{
	if (mask_num == 8)
		return (MASK8);
	else if (mask_num == 7)
		return (MASK7);
	else if (mask_num == 6)
		return (MASK6);
	else if (mask_num == 5)
		return (MASK5);
	else if (mask_num == 4)
		return (MASK4);
	else if (mask_num == 3)
		return (MASK3);
	else if (mask_num == 2)
		return (MASK2);
	else if (mask_num == 1)
		return (MASK1);
	else
		return (0);
}

// void	check_transmission(int signo)
// {
// 	if (signo == SIGUSR1)

// }

void	next(int signo)
{
	if (signo == SIGUSR1)
		sigerror();
	return ;
}

void	send_bit(pid_t serv_pid, char c, int mask_num)
{
	int	ret;
	int	bit_mask;

	bit_mask = return_mask_number(mask_num);
	if (c & bit_mask)
		ret = kill(serv_pid, SIGUSR2);
	else
		ret = kill(serv_pid, SIGUSR1);
	if (ret < 0)
		sigerror();
	
}

void	send_all_bits(pid_t serv_pid, char c, struct sigaction *act)
{
	int	i;

	i = 8;
	while (i > 0)
	{
		sigaction(SIGUSR1, act, 0);
		sigaction(SIGUSR2, act, 0);
		send_bit(serv_pid, c, i--);
		pause();
	}
}

void	send_message(pid_t serv_pid, char *str, struct sigaction *act, int len)
{
	int		i;

	i = -1;
	while (++i < len)
	{
		send_all_bits(serv_pid, str[i], act);
		//usleep(50);
	}
}

int	main(int ac, char **argv)
{
	pid_t	serv_pid;
	char	*str;
	unsigned int	str_len;
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);
	act.sa_handler = next;
	act.sa_flags = 0;
	if (ac < 2)
		return (1);
	serv_pid = check_pid(argv[1]);
	str = argv[2];
	str_len = (unsigned int)ft_strlen(str);
	send_len(serv_pid, str_len, &act);
	send_message(serv_pid, str, &act, str_len);
	return (0);
}
