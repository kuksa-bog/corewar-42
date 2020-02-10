/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_commands2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:44:40 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/28 20:15:31 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

void	write_map(unsigned char *map, t_carriage *carriage, int address,
	unsigned value)
{
	unsigned	pc;
	int			size;

	pc = carriage->pc + address;
	size = 4;
	while (size--)
	{
		pc %= MEM_SIZE;
		map[pc] = (unsigned char)(value >> (size << 3));
		pc++;
	}
}

void	ft_oper_st(t_carriage *carriage, t_vm *data)
{
	int val;
	int address;

	val = carriage->regs[read_map(data->map, carriage->arg_place[0], 1)];
	if (carriage->argum_types[1] == T_REG)
		carriage->regs[read_map(data->map, carriage->arg_place[1], 1)] = val;
	else
	{
		address = (short)read_map(data->map, carriage->arg_place[1], IND_SIZE);
		write_map(data->map, carriage, address % IDX_MOD, val);
	}
	carriage->pc = (carriage->pc + carriage->offset) % MEM_SIZE;
}

void	ft_oper_add(t_carriage *carriage, t_vm *data)
{
	int		val;

	val = carriage->regs[read_map(data->map, carriage->arg_place[0], 1)]
	+ carriage->regs[read_map(data->map, carriage->arg_place[1], 1)];
	carriage->regs[read_map(data->map, carriage->arg_place[2], 1)] = val;
	carriage->carry = !val;
	carriage->pc = (carriage->pc + carriage->offset) % MEM_SIZE;
}

void	ft_oper_sub(t_carriage *carriage, t_vm *data)
{
	int		val;

	val = carriage->regs[read_map(data->map, carriage->arg_place[0], 1)]
	- carriage->regs[read_map(data->map, carriage->arg_place[1], 1)];
	carriage->regs[read_map(data->map, carriage->arg_place[2], 1)] = val;
	carriage->carry = !val;
	carriage->pc = (carriage->pc + carriage->offset) % MEM_SIZE;
}

void	ft_oper_and(t_carriage *carriage, t_vm *data)
{
	int		val;

	val = get_value(data, carriage, 0) & get_value(data, carriage, 1);
	carriage->regs[read_map(data->map, carriage->arg_place[2], 1)] = val;
	carriage->carry = !val;
	carriage->pc = (carriage->pc + carriage->offset) % MEM_SIZE;
}
