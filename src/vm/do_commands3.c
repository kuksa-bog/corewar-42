/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_commands3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:48:07 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/28 19:15:27 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

void	ft_oper_or(t_carriage *carriage, t_vm *data)
{
	int		val;

	val = get_value(data, carriage, 0) | get_value(data, carriage, 1);
	carriage->regs[read_map(data->map, carriage->arg_place[2], 1)] = val;
	carriage->carry = !val;
	carriage->pc = (carriage->pc + carriage->offset) % MEM_SIZE;
}

void	ft_oper_xor(t_carriage *carriage, t_vm *data)
{
	int		val;

	val = get_value(data, carriage, 0) ^ get_value(data, carriage, 1);
	carriage->regs[read_map(data->map, carriage->arg_place[2], 1)] = val;
	carriage->carry = !val;
	carriage->pc = (carriage->pc + carriage->offset) % MEM_SIZE;
}

void	ft_oper_zjmp(t_carriage *carriage, t_vm *data)
{
	int val;

	val = get_value(data, carriage, 0);
	if (carriage->carry)
		carriage->pc = (unsigned)(carriage->pc + val % IDX_MOD) % MEM_SIZE;
	else
		carriage->pc = (carriage->pc + carriage->offset) % MEM_SIZE;
}

void	ft_oper_ldi(t_carriage *carriage, t_vm *data)
{
	int				first_op;
	int				second_op;
	int				pc;
	int				val;

	first_op = get_value(data, carriage, 0);
	second_op = get_value(data, carriage, 1);
	pc = carriage->pc + (first_op + second_op) % IDX_MOD;
	val = read_map(data->map, pc, 4);
	carriage->regs[read_map(data->map, carriage->arg_place[2], 1)] = val;
	carriage->pc = (carriage->pc + carriage->offset) % MEM_SIZE;
}

void	ft_oper_sti(t_carriage *carriage, t_vm *data)
{
	int val;
	int address;

	val = carriage->regs[read_map(data->map, carriage->arg_place[0], 1)];
	address = (get_value(data, carriage, 1) +
		get_value(data, carriage, 2)) % IDX_MOD;
	write_map(data->map, carriage, address, val);
	carriage->pc = (carriage->pc + carriage->offset) % MEM_SIZE;
}
