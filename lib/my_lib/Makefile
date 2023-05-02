NAME = libft.a

BONUS = .bonus

CFLAGS = -Wall -Wextra -Werror

SRCS = 	ft_fd_func/ft_putchar_fd.c		\
		ft_fd_func/ft_putstr_fd.c		\
		ft_fd_func/ft_putnbr_fd.c		\
		ft_fd_func/ft_putendl_fd.c		\
		ft_fd_func/ft_putptr.c			\
		ft_is_func/ft_isalnum.c			\
		ft_is_func/ft_isalpha.c			\
		ft_is_func/ft_isascii.c			\
		ft_is_func/ft_isdigit.c			\
		ft_is_func/ft_isprint.c			\
		ft_is_func/ft_isspace.c			\
		ft_is_func/ft_str_isdigit.c		\
		ft_len_func/ft_nbrlen.c			\
		ft_len_func/ft_strlen.c			\
		ft_len_func/ft_ptrlen.c			\
		ft_mem_func/ft_bzero.c			\
		ft_mem_func/ft_calloc.c			\
		ft_mem_func/ft_memchr.c			\
		ft_mem_func/ft_memcmp.c			\
		ft_mem_func/ft_memcpy.c			\
		ft_mem_func/ft_memmove.c		\
		ft_mem_func/ft_memset.c			\
		ft_nbr_func/ft_itoa.c			\
		ft_str_func/ft_add_in_str.c		\
		ft_str_func/ft_instr.c			\
		ft_str_func/ft_split.c			\
		ft_str_func/ft_strcat.c			\
		ft_str_func/ft_strchr.c			\
		ft_str_func/ft_strdup.c			\
		ft_str_func/ft_striteri.c		\
		ft_str_func/ft_strjoin.c		\
		ft_str_func/ft_strlcat.c		\
		ft_str_func/ft_strlcpy.c		\
		ft_str_func/ft_strmap.c			\
		ft_str_func/ft_strrchr.c		\
		ft_str_func/ft_strtrim.c		\
		ft_str_func/ft_substr.c			\
		ft_str_func/ft_tolower.c		\
		ft_str_func/ft_toupper.c		\
		ft_str_func/ft_strncmp.c		\
		ft_str_func/ft_strnstr.c		\
		ft_str_func/ft_atoi.c			\
		ft_str_func/ft_strcmp.c			\
		ft_free_func/free.c				\
		ft_arr_func/ft_arrset.c			\
		ft_arr_func/ft_add_in_arr.c		\
		ft_arr_func/ft_is_inarr.c		\
		get_next_line/get_next_line.c	\
		get_next_line/get_next_line_utils.c


SRCSBONUS = ft_lst_func/ft_lstadd_back.c 	\
			ft_lst_func/ft_lstadd_front.c 	\
			ft_lst_func/ft_lstclear.c 		\
			ft_lst_func/ft_lstdelone.c 		\
			ft_lst_func/ft_lstiter.c 		\
			ft_lst_func/ft_lstlast.c 		\
			ft_lst_func/ft_lstmap.c 		\
			ft_lst_func/ft_lstnew.c 		\
			ft_lst_func/ft_lstsize.c

OBJS = $(SRCS:.c=.o)

OBJSBONUS = $(SRCSBONUS:.c=.o)

INCLUDE = -I ./include

RM = rm -f

DEPS = $(SRCS:.c=.d)

DEPS_BONUS = $(SRCSBONUS:.c=.d)

%.o: %.c
	${CC} ${CFLAGS} -MMD $(INCLUDE) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)

	ar -rcs $(NAME) $(OBJS)

-include $(DEPS)

bonus: $(BONUS)

$(BONUS) : $(OBJS) $(OBJSBONUS)

	ar -rcs $(NAME) $(OBJS) $(OBJSBONUS)

-include $(DEPS_BONUS)

clean:
	$(RM) $(OBJS) $(OBJSBONUS) $(DEPS) $(DEPS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
.PHONY: all bonus clean fclean re
