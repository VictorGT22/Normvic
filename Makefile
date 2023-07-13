# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vics <vics@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 15:37:53 by victgonz          #+#    #+#              #
#    Updated: 2023/07/13 14:17:28 by vics             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####	VARIABLES	####

PROJECT = NORMEZ

CC = gcc

CFLAGS = -g ##-Wall -Wextra -Werror -std=c99

SRC_DIR = src/

OBJ_DIR = obj/

SRC_FILES	=	print_information/print_error		\
				print_information/print_info		\
				template							\
				init_linked							\
				checker_h							\
				checker

SOURCES = 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))

OBJECTS = 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF		=	.cache_exists

EXECUTABLE = normez

## INCLUDES

INCLUDES = -I./include

LIB_DIR = lib/my_lib

INCLUDES_MY_LIB = -I./$(LIB_DIR)/include

FT_PRINTF_DIR = lib/ft_printf

INCLUDES_FT_PRINTF = -I./$(FT_PRINTF_DIR)/include

LIB = -L./$(LIB_DIR) -lft

FT_LIB = -L./$(FT_PRINTF_DIR) -lft

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

all: save_previous libft $(EXECUTABLE) write_name
	cp normez zzzzprueba

$(EXECUTABLE): $(OBJECTS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(INCLUDES_MY_LIB) $(OBJECTS) $(LIB) -o $(EXECUTABLE)
	@echo "$(MAGENTA)======>$(GREEN)$(EXECUTABLE) compiled! $(MAGENTA)<======$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	@echo "$(MAGENTA)======>$(GREEN)Compiling: $(YELLOW)$< $(DEF_COLOR)"
	$(CC) $(CFLAGS) $(INCLUDES) $(INCLUDES_MY_LIB) -c $< -o $@

$(OBJF):
		@mkdir -p $(OBJ_DIR)

write_name:
		@echo "$(MAGENTA)╔═════════════════════════════════════════╗$(DEF_COLOR)"
		@echo "$(MAGENTA)║                 $(CYAN)$(PROJECT)$(MAGENTA)                  ║$(DEF_COLOR)"
		@echo "$(MAGENTA)╚═══════════════╦═════════╦═══════════════╝$(DEF_COLOR)"
		@echo "$(MAGENTA)                ║  $(GREEN)VIC'S$(MAGENTA)  ║$(DEF_COLOR)"
		@echo "$(MAGENTA)                ╚═════════╝     $(DEF_COLOR)"

clean:
	rm -f $(OBJECTS)
	@echo "$(MAGENTA)======>$(BLUE)$(EXECUTABLE) object files cleaned!$(DEF_COLOR)"

fclean: clean
	rm -f $(EXECUTABLE)
	@echo "$(MAGENTA)======>$(CYAN)$(EXECUTABLE)executable files cleaned!$(DEF_COLOR)"
	make -C $(LIB_DIR) fclean

re: fclean all

libft:
	make -C $(LIB_DIR)

save_previous:
	rm -rf /home/vics/Documents/Copia_Seguridad
	cp -r /home/vics/Documents/normez_rest /home/vics/Documents/Copia_Seguridad