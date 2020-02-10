/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_solution_vm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:56:17 by vgrynish          #+#    #+#             */
/*   Updated: 2019/10/27 21:03:57 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

void			print_winner(t_vm *data)
{
	ft_putstr("Player ");
	ft_putnbr(data->last_live_id);
	ft_putstr(" (");
	ft_putstr(get_player_by_id(data->players, data->last_live_id)->player_name);
	ft_putstr(") won\n");
}

unsigned		read_map(unsigned char *map, unsigned place, int size)
{
	unsigned		val;

	val = 0;
	while (size--)
	{
		place %= MEM_SIZE;
		val |= (unsigned)map[place] << (size << 3);
		++place;
	}
	return (val);
}

int				arg_size(t_carriage *carriage, int arg)
{
	int				type;

	type = carriage->argum_types[arg];
	if (type == T_DIR)
		return (g_tab_op[carriage->opcode].trash ? 2 : 4);
	if (type == T_IND)
		return (IND_SIZE);
	if (type == T_REG)
		return (1);
	return (0);
}

int				fill_carriage(t_vm *data, t_carriage *carriage)
{
	unsigned char	cod;
	unsigned		offset;
	int				i;
	int				valid;

	valid = 1;
	cod = read_map(data->map, carriage->pc + 1, 1);
	offset = 2;
	i = 0;
	while (i < carriage->arg_amount)
	{
		carriage->argum_types[i] = 1 << (cod >> 6) >> 1;
		if (!(carriage->argum_types[i]
							& g_tab_op[carriage->opcode].argum_types[i]))
			valid = 0;
		carriage->arg_place[i] = (carriage->pc + offset) % MEM_SIZE;
		cod <<= 2;
		offset += arg_size(carriage, i);
		i++;
	}
	carriage->offset = offset;
	return (valid);
}

int				fill_registers(t_vm *data, t_carriage *carriage)
{
	int				i;
	unsigned char	registers;

	i = 0;
	while (i < carriage->arg_amount)
	{
		if (carriage->argum_types[i] == T_REG)
		{
			registers = read_map(data->map, carriage->arg_place[i], 1);
			if (registers > 16 || registers < 1)
				return (0);
		}
		++i;
	}
	return (1);
}
