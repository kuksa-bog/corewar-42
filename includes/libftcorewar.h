/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftcorewar.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 20:36:53 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/28 20:14:02 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTCOREWAR_H
# define LIBFTCOREWAR_H

# include "libft.h"
# include <fcntl.h>

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

typedef char					t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

static char						g_code2t[4] = {0, T_REG, T_DIR, T_IND};
static int						g_t2size[5] = {0, 1, DIR_SIZE, 0, IND_SIZE};

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		s_carriage
{
	int				id;
	int				player_id;
	int				regs[REG_NUMBER + 1];
	int				carry;
	unsigned		pc;
	int				cycle_last_live;
	int				opcode;
	int				arg_amount;
	int				argum_types[3];
	int				arg_place[3];
	unsigned		offset;
	int				loop_to_wait_do;
}					t_carriage;

typedef struct		s_player
{
	int				id;
	char			*file_name;
	char			*player_name;
	char			*comment;
	int				prog_size;
	char			*execute_code;
}					t_player;

typedef struct		s_lst_vm
{
	void			*data;
	struct s_lst_vm	*next;
}					t_lst_vm;

typedef struct		s_vm
{
	int				count_player;
	int				show_leak;
	int				show_without_live;
	int				show_verbose;
	t_lst_vm		*players;
	int				last_live_id;
	unsigned char	*map;
	t_lst_vm		*carriages;
	int				loop;
	int				cycle_to_die;
	int				num_checks;
	int				num_live;
	int				dump_loop;
}					t_vm;

typedef struct		s_op
{
	char			*name;
	int				argum_nums;
	char			argum_types[3];
	int				oper_code;
	int				num_cycle;
	char			*comment;
	int				cod_of_type_args;
	int				trash;
	void			(*fun)(t_carriage *crnt_carr, t_vm *data);
}					t_op;

void				ft_oper_live(t_carriage *crnt_carr, t_vm *data);
void				ft_oper_ld(t_carriage *crnt_carr, t_vm *data);
void				ft_oper_st(t_carriage *crnt_carr, t_vm *data);
void				ft_oper_add(t_carriage *crnt_carr, t_vm *data);
void				ft_oper_sub(t_carriage *crnt_carr, t_vm *data);
void				ft_oper_and(t_carriage *crnt_carr, t_vm *data);
void				ft_oper_or(t_carriage *crnt_carr, t_vm *data);
void				ft_oper_xor(t_carriage *crnt_carr, t_vm *data);
void				ft_oper_zjmp(t_carriage *crnt_carr, t_vm *data);
void				ft_oper_ldi(t_carriage *crnt_carr, t_vm *data);
void				ft_oper_sti(t_carriage *crnt_carr, t_vm *data);
void				ft_oper_fork(t_carriage *crnt_carr, t_vm *data);
void				ft_oper_lld(t_carriage *crnt_carr, t_vm *data);
void				ft_oper_lldi(t_carriage *crnt_carr, t_vm *data);
void				ft_oper_lfork(t_carriage *crnt_carr, t_vm *data);
void				ft_oper_aff(t_carriage *crnt_carr, t_vm *data);

static t_op						g_tab_op[17] =
{
	{0, 0, {0}, 0, 0, 0, 0, 0, 0},
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, ft_oper_live},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, ft_oper_ld},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, ft_oper_st},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, ft_oper_add},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, ft_oper_sub},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, ft_oper_and},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, ft_oper_or},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, ft_oper_xor},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, ft_oper_zjmp},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, ft_oper_ldi},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, ft_oper_sti},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, ft_oper_fork},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, ft_oper_lld},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, ft_oper_lldi},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, ft_oper_lfork},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, ft_oper_aff}
};

int					main(int argc, char **argv);
unsigned char		*create_mem_map();
void				sorting_list_carriage(t_carriage **frst);
void				swap_list_items(t_carriage **frst, t_carriage *crnt,
					t_carriage *mem[4]);
void				write_introduction(t_carriage *frst);
void				read_data_players(t_vm *data);
void				read_data_players3(t_carriage *crn, int *fd,
					unsigned char *map, int *cnt_plr);
void				read_data_players2(t_carriage *crn, int *fd);
int					ft_read_data_bytes(int fd);
int					ft_bytes_to_int(unsigned char *bytes, int num_bytes);
void				ft_print_memory(const unsigned char *var, size_t size);
void				next_line_and_print_add(int i, int size);
void				print_address(int i);
int					read_inp_str(int argc, char **argv, t_vm *data);
int					define_next_unic_num(t_lst_vm *players, int cnt_plr);
void				found_flg_min_n(char **argv, int *j, t_lst_vm **players);
int					found_same_unic_num(t_lst_vm *player, int id);
int					found_point_cor(char *file_name);
t_lst_vm			*add_player_to_list(t_lst_vm **players, char *argv);
t_lst_vm			*add_player_to_list_crn(t_lst_vm **players, char *argv);
int					get_arg_value(t_carriage *crnt_carr, int index_arg,
					unsigned char *map);
int					read_bytes(int start_address, unsigned char *map,
					int num_bytes);
void				write_bytes_from_int(int start_address, unsigned char *map,
					unsigned int val);
void				change_carry(t_carriage *crnt_carr, int ind);
void				do_check(t_carriage *crnt_carr);
void				check_alive(t_carriage *crnt_carr);
int					read_command_frome_byte_code(t_carriage *crnt_carr,
					unsigned char *map);
void				read_arg_types(t_carriage *crnt_carr, unsigned char *map);
int					is_val_arg_tapes(t_op *info_com, t_carriage *crnt_carr);
int					read_com_argums(t_op *info_com, t_carriage *crnt_carr,
					unsigned char *map);
void				read_command_argum(t_carriage *crnt_carr,
					unsigned char *map, int i_argum);
int					is_val_command_oper_code(int crnt_oper_code);
int					is_argum_type(t_op *info_com, t_carriage *crnt_carr);
void				print_error(char *error);
int					ft_atoi_strict(char const *str);
t_player			*get_player_by_id(t_lst_vm *players, int id);
void				print_player_info(t_player *crn);
t_carriage			*new_carriage(void);
void				lst_vm_push(t_lst_vm **old_lst, void *content);
void				load_players(t_vm *data);
void				ft_corewar(t_vm *data);
void				work_with_data(t_vm *data);
void				check(t_vm *data);
void				*lst_vm_pop(t_lst_vm **head);
void				option_loop(t_vm *data);
void				do_car(t_vm *data, t_carriage *carriage);
void				do_op(t_vm *data, t_carriage *carriage);
int					fill_registers(t_vm *data, t_carriage *carriage);
int					fill_carriage(t_vm *data, t_carriage *carriage);
int					arg_size(t_carriage *carriage, int arg);
unsigned			read_map(unsigned char *map, unsigned place, int size);
void				print_winner(t_vm *data);
int					get_value(t_vm *data, t_carriage *carriage, int i);
void				write_map(unsigned char *map,
					t_carriage *carriage, int address, unsigned value);
void				do_op(t_vm *data, t_carriage *carriage);
void				do_car(t_vm *data, t_carriage *carriage);
void				ft_read_inp_help(char **argv, int argc, t_vm *data, int *j);
int					choose_champ_id(t_lst_vm *players);

#endif
