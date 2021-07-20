#ifndef UTILS_H
# define UTILS_H
#include <unistd.h>
#include <stdlib.h>

int	ft_isdigit(int c);
void	ft_putnbr(unsigned int n);
void	print_char(char c);
void	*ft_memset(void *ptr, int value, size_t num);
size_t	ft_strlen(const char *str);
int	ft_atoi(const char *str);
void	sigerror(void);

#endif