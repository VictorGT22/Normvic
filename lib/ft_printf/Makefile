# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: victgonz <victgonz@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/21 23:08:02 by efrre-m           #+#    #+#              #
#    Updated: 2023/02/12 23:29:59 by victgonz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT = PRINTF

LIBS_DIR = ../my_lib

INCLUDES = ./include/

INCLUDES_LIB = ./../my_lib/include/

NAME = libft.a

CC = gcc

RM = rm -f

CFLAGS = 

SRC_DIR = src/

SRCS_FILES =	ft_printf.c 			\
				func_ptr.c				\
				func_putnbr.c 			\
				utils_1.c				\
				utils_2.c				\
				std_func.c 				\
				func_conv/func_s_c.c 	\
				func_conv/func_e_f.c	\
				func_conv/func_p.c		\
				func_conv/func_u.c		\
				func_conv/func_x.c		\
				func_conv/func_o.c		\
				func_conv/func_d_i.c	\
				func_conv/func_b.c		\
				func_conv/func_g.c		\
				func_conv/func_n.c		\
				get_info/get_info.c	 	\
				get_info/get_info_2.c	\
				free_info/free_1.c

SRCS = $(addprefix $(SRC_DIR), $(SRCS_FILES))

OBJS = ${SRCS:.c=.o}

OBJBONUS = $(SRCS:.c=.o)

####	COLORS	####

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

#### COMMANDS ####

%.o: %.c  $(INCLUDES)
	$(CC) $(CFLAGS) -I $(INCLUDES) -I $(INCLUDES_LIB) -c $< -o $@

all: 	make_libs ${NAME} write_name

make_libs:
		@make -C $(LIBS_DIR)
			
${NAME}:	${OBJS} ../my_lib/libft.a
			cp ../my_lib/libft.a ${NAME}
			ar rcs ${NAME} ${OBJS} 
			ranlib ${NAME}

write_name:
		@echo "$(MAGENTA)╔═════════════════════════════════════════╗$(DEF_COLOR)"
		@echo "$(MAGENTA)║                  $(CYAN)$(PROJECT)$(MAGENTA)                 ║$(DEF_COLOR)"
		@echo "$(MAGENTA)╚═══════════════╦═════════╦═══════════════╝$(DEF_COLOR)"
		@echo "$(MAGENTA)                ║  $(GREEN)VIC'S$(MAGENTA)  ║$(DEF_COLOR)"
		@echo "$(MAGENTA)                ╚═════════╝     $(DEF_COLOR)"

bonus: $(BONUS)

$(BONUS) : $(OBJSBONUS) ../my_lib/libft.a
			cp ../my_lib/libft.a ${NAME}
			ar rcs ${NAME} ${OBJSBONUS} 
			ranlib ${NAME}
			
clean: 		
			${RM} ${OBJS} ${OBJSBONUS} 
			make clean -C $(LIBS_DIR)

fclean: 	clean
			${RM} ${NAME}
			make fclean -C $(LIBS_DIR)

re:			fclean all

.PHONY: all clean fclean re