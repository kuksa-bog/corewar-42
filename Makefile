# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/15 11:08:54 by bkuksa            #+#    #+#              #
#    Updated: 2019/10/27 23:09:25 by vgrynish         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAME_ASM = asm.c \
			op.c \
			algo.c \
			algo_2.c \
			lexic.c \
			lexic2.c \
			help.c \

SRC_NAME_VM = add_players_to_list.c \
			do_commands1.c \
			do_commands2.c \
			do_commands3.c \
			do_commands4.c \
			ft_corewar.c \
			main.c \
			read_input_str.c \
			ft_atoi_strict.c \
			read_data_players.c \
			helper_for_main.c \
			ft_print_memory.c \
			helper_solution_vm.c \

OBJ_NAME_ASM = $(SRC_NAME_ASM:.c=.o)
OBJ_NAME_VM = $(SRC_NAME_VM:.c=.o)

NAME_ASM = asm
NAME_COREWAR = corewar

SRC_PATH_ASM = ./src/asm/
SRC_PATH_VM = ./src/vm/
OBJ_PATH_ASM = ./objects/asm/
OBJ_PATH_VM = ./objects/vm/
INC_PATH = ./includes/ ./libft/

CC = gcc
CFLAGS = -Wall -Werror -Wextra
CLIBS = -L libft/ -lft

LIBSDIR = libft/
LIBFT = $(LIBSDIR)libft.a

CHECK_PATH=./unitest/
CHECK=check.sh

DEBUG_BASIC = -g -fsanitize=address
DEBUG_PROF = -pg

ifeq ($(DEBUG), basic)
	CFLAGS += $(DEBUG_BASIC)
endif
ifeq ($(DEBUG), prof)
	CFLAGS += $(DEBUG_PROF)
endif

SRC_ASM = $(addprefix $(SRC_PATH_ASM),$(SRC_NAME_ASM))
OBJ_ASM = $(addprefix $(OBJ_PATH_ASM),$(OBJ_NAME_ASM))


SRC_VM = $(addprefix $(SRC_PATH_VM),$(SRC_NAME_VM))
OBJ_VM = $(addprefix $(OBJ_PATH_VM),$(OBJ_NAME_VM))

INC = $(addprefix -I,$(INC_PATH))

all: $(NAME_COREWAR) $(NAME_ASM)

$(NAME_ASM): $(LIBFT) $(OBJ_ASM)
	$(CC) $(CFLAGS) $(INC) -o $(NAME_ASM) $(OBJ_ASM) $(CLIBS)

$(NAME_COREWAR): $(LIBFT) $(OBJ_VM)
	$(CC) $(CFLAGS) $(INC) -o $(NAME_COREWAR) $(OBJ_VM) $(CLIBS)

$(OBJ_PATH_VM)%.o: $(SRC_PATH_VM)%.c
	@mkdir -p $(OBJ_PATH_VM) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	
$(OBJ_PATH_ASM)%.o: $(SRC_PATH_ASM)%.c
	@mkdir -p $(OBJ_PATH_ASM) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(LIBFT):
	make -C $(LIBSDIR)

check:
	@./$(CHECK_PATH)$(CHECK)

clean:
	rm -f $(OBJ_VM) $(OBJ_ASM)
ifneq ($(OBJ_PATH_ASM), ./)
	rm -rf $(OBJ_PATH_ASM)
endif
ifneq ($(OBJ_PATH_VM), ./)
	rm -rf $(OBJ_PATH_VM)
endif

fclean: clean
	rm -f $(NAME_ASM) $(NAME_COREWAR)
	make -C $(LIBSDIR) fclean

mrproper: fclean
	rm -f check.log
	rm -f compilation.log

re: fclean all

.PHONY: all clean fclean mrproper re
