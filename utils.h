#ifndef UTILS_H
# define UTILS_H
#include <unistd.h>
#include <stdlib.h>

typedef struct sigaction t_act;

int	ft_isdigit(int c);
void	ft_putnbr(unsigned int n);
void	print_char(char c);
void	*ft_memset(void *ptr, int value, size_t num);
size_t	ft_strlen(const char *str);
int	mt_atoi(const char *str);
void	sigerror(void);
void	error(char *str);
void	setup_act(t_act *act, void (*handler)(int, siginfo_t *, void *));

#endif