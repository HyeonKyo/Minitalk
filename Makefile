CC = gcc
CFLAGS = -g
SEV_SRCS = server.c ft_utils.c
CLT_SRCS = client.c ft_utils.c
SRCS = $(SEV_SRCS) $(CLT_SRCS)
SEV_OBJS = $(SEV_SRCS:.c=.o)
CLT_OBJS = $(CLT_SRCS:.c=.o)
INC_DIR = ./
NAME = server
CLT_NAME = client
RM = rm -rf

all	:	$(NAME) $(CLT_NAME)

$(NAME)	:	$(SEV_OBJS)
			$(CC) $(CFLAGS) -o $@ $^

$(CLT_NAME)	:	$(CLT_OBJS)
				$(CC) $(CFLAGS) -o $@ $^

.c.o	:
			$(CC) $(CFLAGS) -c $(SRCS) -I$(INC_DIR)

clean	:
			$(RM) $(SEV_OBJS) $(CLT_OBJS)

fclean	:	clean
			$(RM) $(NAME) $(CLT_NAME)

re	:	fclean all

bonus	:	re

.PHONY	:	all clean fclean re bonus