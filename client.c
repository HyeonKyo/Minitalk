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

void	send_all_bits(pid_t serv_pid, char c)
{
	int	i;

	i = 8;
	while (i > 0)
	{
		send_bit(serv_pid, c, i--);
		usleep(50);
	}
}

void	send_message(pid_t serv_pid, char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		send_all_bits(serv_pid, str[i]);
		usleep(50);
	}
}

int	main(int ac, char **argv)
{
	pid_t	serv_pid;
	char	*str;

	if (ac < 2)
		return (1);
	serv_pid = check_pid(argv[1]);
	str = argv[2];
	send_message(serv_pid, str);
	return (0);
}

/*
1. argv[1]은 server의 pid넘버 ⇒ atoi로 pid저장
2. argv[2]문자열을 str에 복사
3. str을 1비트씩 접근 → 비트연산?
4. 이 문자열을 pid를 통해 서버로 정보전달
--------send-------
1. 문자열의 각 문자를 c에 저장
2. 맨 앞 비트부터 차례로 비트마스킹으로 검사
3. 비트값이 1이면 kill로 sigusr2을 0이면 sigusr1을 보내줌
4. 다음 문자를 c에 저장
5. c == 0일 때까지 반복.
*/