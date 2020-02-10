/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_commands4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:50:50 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/28 20:16:30 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

t_carriage		*copy_carriage(t_carriage *carriage, int new_pc)
{
	t_carriage		*new_car;
	int				id;

	new_car = new_carriage();
	id = new_car->id;
	ft_memcpy(new_car, carriage, sizeof(t_carriage));
	new_car->id = id;
	new_car->pc = new_pc % MEM_SIZE;
	return (new_car);
}

void			ft_oper_fork(t_carriage *carriage, t_vm *data)
{
	int const address = get_value(data, carriage, 0);
	int const pc = carriage->pc + address % IDX_MOD;

	lst_vm_push(&data->carriages, copy_carriage(carriage, pc));
	carriage->pc = (carriage->pc + carriage->offset) % MEM_SIZE;
}

void			ft_oper_lld(t_carriage *carriage, t_vm *data)
{
	int val;

	val = get_value(data, carriage, 0);
	carriage->regs[read_map(data->map, carriage->arg_place[1], 1)] = val;
	carriage->carry = !val;
	carriage->pc = (carriage->pc + carriage->offset) % MEM_SIZE;
}

void			ft_oper_lldi(t_carriage *carriage, t_vm *data)
{
	int first_op;
	int second_op;
	int pc;
	int val;

	first_op = get_value(data, carriage, 0);
	second_op = get_value(data, carriage, 1);
	pc = carriage->pc + first_op + second_op;
	val = read_map(data->map, pc, 4);
	carriage->regs[read_map(data->map, carriage->arg_place[2], 1)] = val;
	carriage->carry = !val;
	carriage->pc = (carriage->pc + carriage->offset) % MEM_SIZE;
}

void			ft_oper_lfork(t_carriage *carriage, t_vm *data)
{
	int address;
	int pc;

	address = get_value(data, carriage, 0);
	pc = carriage->pc + address;
	lst_vm_push(&(data->carriages), copy_carriage(carriage, pc));
	carriage->pc = (carriage->pc + carriage->offset) % MEM_SIZE;
}
