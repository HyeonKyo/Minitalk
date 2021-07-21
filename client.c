#include "minitalk.h"
#include "utils.h"
int g_flag = 0;

int	check_pid(char *argv1)
{
	int	i;

	i = -1;
	while (argv1[++i])
	{
		if (!ft_isdigit(argv1[i]))
			exit(1);
	}
	//음수는 예외처리하는 아토이로 변경
	return (ft_atoi(argv1));
}

void	send_len(unsigned int str_len)
{
	t_info	info;
	
	ft_memset(&info, 0, sizeof(t_info));
	info.num = str_len;
	send_message(info.arr, 4);
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

void	catch_signal(int sig, siginfo_t *info, void *context)
{
	if (info->si_pid != g_server_pid)
		sigerror();
	if (g_flag == 0)
	{
		if (sig == SIGUSR1)
			sigerror();
	}
	else
	{
		if (sig == SIGUSR2)
			write(1, "Send message complete!\n", 24);
		else
			write(1, "Send error!\n", 13);
		g_server_pid = 0;
		usleep(50);
		exit(0);
	}
}

void	send_bit(char c, int mask_num)
{
	int	ret;
	int	bit_mask;

	bit_mask = return_mask_number(mask_num);
	if (c & bit_mask)
		ret = kill(g_server_pid, SIGUSR2);
	else
		ret = kill(g_server_pid, SIGUSR1);
	if (ret < 0)
		sigerror();
}

void	send_all_bits(char c)
{
	int	i;

	i = 8;
	while (i > 0)
	{
		send_bit(c, i--);
		pause();
	}
}

void	send_message(char *str, int len)
{
	int		i;

	i = -1;
	while (++i < len)
	{
		send_all_bits(str[i]);
	}
}

int	main(int ac, char **argv)
{
	char	*str;
	unsigned int	str_len;
	t_act	act;

	if (ac < 2)
		return (1);
	setup_act(&act, catch_signal);
	g_server_pid = check_pid(argv[1]);
	str = argv[2];
	str_len = (unsigned int)ft_strlen(str);
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	send_len(str_len);
	send_message(str, str_len);
	g_flag = 1;
	while (1)
		pause();
	return (0);
}
