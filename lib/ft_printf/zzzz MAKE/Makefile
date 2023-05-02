# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: victgonz <victgonz@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 15:37:53 by victgonz          #+#    #+#              #
#    Updated: 2023/02/10 01:09:36 by victgonz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####	VARIABLES	####
CC = gcc

CFLAGS = -std=c99

SRC_DIR = src/

OBJ_DIR = obj/

SRC_FILES	=	ft_printf 				\
				func_ptr				\
				func_putnbr 			\
				utils_1					\
				utils_2					\
				std_func 				\
				main					\
				func_conv/func_s_c 		\
				func_conv/func_e_f		\
				func_conv/func_p		\
				func_conv/func_u		\
				func_conv/func_x		\
				func_conv/func_o		\
				func_conv/func_d_i		\
				func_conv/func_b		\
				func_conv/func_g		\
				func_conv/func_n		\
				get_info/get_info	 	\
				get_info/get_info_2		\
				free_info/free_1

SOURCES = 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))

OBJECTS = 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF		=	.cache_exists

EXECUTABLE = libftprintf.a

INCLUDES = -I./includes/include/

LIB_DIR = lib/my

LIB = -L./$(LIB_DIR) -lft

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

all: libft $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) $(LIB) -o $(EXECUTABLE) ## este es ejecutable

##	ar -rcs $(EXECUTABLE) $(INCLUDES) $(OBJECTS) $(LIB)
	@echo "$(MAGENTA)======>$(GREEN)$(EXECUTABLE) compiled! $(MAGENTA)<======$(DEF_COLOR)"
##

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	@echo "$(MAGENTA)======>$(GREEN)Compiling: $(YELLOW)$< $(DEF_COLOR)"
##	${CC} ${CFLAGS} -MMD -I $(LIB) -c $< -o $@
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJF):
		@mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJECTS)
	make -C $(LIB_DIR) clean
	@echo "$(MAGENTA)======>$(BLUE)$(EXECUTABLE) object files cleaned!$(DEF_COLOR)"

fclean: clean
	rm -f $(EXECUTABLE)
	make -C $(LIB_DIR) fclean	
	@echo "$(MAGENTA)======>$(CYAN)$(EXECUTABLE)executable files cleaned!$(DEF_COLOR)"

re: fclean all

libft:
	make -C $(LIB_DIR)

.PHONY: all clean fclean re