/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_commands1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:41:32 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/27 21:42:13 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

int				get_t_ind(t_vm *data, t_carriage *carriage, int place)
{
	int			address;

	address = (short)read_map(data->map, place, IND_SIZE);
	if (carriage->opcode != 13)
		address %= IDX_MOD;
	place = (carriage->pc + address) % MEM_SIZE;
	return ((int)read_map(data->map, place, 4));
}

int				get_value(t_vm *data, t_carriage *carriage, int i)
{
	int type;
	int pc;

	type = carriage->argum_types[i];
	pc = carriage->arg_place[i];
	if (type == T_DIR)
	{
		return (g_tab_op[carriage->opcode].trash ?
		((short)read_map(data->map, pc, 2)) :
		((int)read_map(data->map, pc, 4)));
	}
	if (type == T_REG)
		return (carriage->regs[read_map(data->map, pc, 1)]);
	if (type == T_IND)
		return (get_t_ind(data, carriage, pc));
	return (0);
}

void			ft_oper_live(t_carriage *carriage, t_vm *data)
{
	int val;

	val = get_value(data, carriage, 0);
	data->num_live++;
	carriage->cycle_last_live = data->loop;
	if (val < 0 && -val <= data->count_player)
	{
		data->last_live_id = -val;
		if (!data->show_without_live)
		{
			ft_putstr("A process shows that player ");
			ft_putnbr(-val);
			ft_putstr(" (");
			ft_putstr(get_player_by_id(data->players, -val)->player_name);
			ft_putendl(") is alive");
		}
	}
	carriage->pc = (carriage->pc + carriage->offset) % MEM_SIZE;
}

void			ft_oper_ld(t_carriage *carriage, t_vm *data)
{
	int val;

	val = get_value(data, carriage, 0);
	carriage->regs[read_map(data->map, carriage->arg_place[1], 1)] = val;
	carriage->carry = !val;
	carriage->pc = (carriage->pc + carriage->offset) % MEM_SIZE;
}

void			ft_oper_aff(t_carriage *carriage, t_vm *data)
{
	(void)data;
	carriage->pc = (carriage->pc + carriage->offset) % MEM_SIZE;
}
