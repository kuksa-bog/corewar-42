/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_corewar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 19:54:48 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/28 19:15:13 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

void			do_operation(t_vm *data, t_carriage *carriage)
{
	carriage->loop_to_wait_do--;
	if (!carriage->loop_to_wait_do)
	{
		carriage->arg_amount = g_tab_op[carriage->opcode].argum_nums;
		if (g_tab_op[carriage->opcode].cod_of_type_args)
		{
			if (!fill_carriage(data, carriage)
										|| !fill_registers(data, carriage))
			{
				carriage->pc = (carriage->pc + carriage->offset) % MEM_SIZE;
				return ;
			}
		}
		else
		{
			carriage->argum_types[0] = T_DIR;
			carriage->arg_place[0] = (carriage->pc + 1) % MEM_SIZE;
			carriage->offset = 1 + arg_size(carriage, 0);
		}
		g_tab_op[carriage->opcode].fun(carriage, data);
	}
}

void			option_loop(t_vm *data)
{
	t_lst_vm		*carriage;
	t_carriage		*car;
	int				check_opcode;

	data->loop++;
	carriage = data->carriages;
	while (carriage)
	{
		car = carriage->data;
		check_opcode = 1;
		if (!car->loop_to_wait_do)
		{
			car->opcode = read_map(data->map, car->pc, 1);
			if (car->opcode < 1 || car->opcode > 16)
			{
				car->pc = (car->pc + 1) % MEM_SIZE;
				check_opcode = 0;
			}
			else
				car->loop_to_wait_do = g_tab_op[car->opcode].num_cycle;
		}
		if (check_opcode)
			do_operation(data, car);
		carriage = carriage->next;
	}
}

void			*lst_vm_pop(t_lst_vm **head)
{
	t_lst_vm	*item;
	void		*data;

	item = *head;
	*head = item->next;
	data = item->data;
	free(item);
	return (data);
}

void			check_and_free_data(t_vm *data)
{
	int				old_cycle;
	t_lst_vm		**lst_main;
	t_carriage		*carriage;

	old_cycle = data->loop - data->cycle_to_die;
	data->num_checks++;
	lst_main = &data->carriages;
	while (*lst_main)
	{
		carriage = (*lst_main)->data;
		if (carriage->cycle_last_live <= old_cycle)
			free(lst_vm_pop(lst_main));
		else
			lst_main = &(*lst_main)->next;
	}
	if (data->num_checks == MAX_CHECKS || data->num_live >= NBR_LIVE)
	{
		data->cycle_to_die -= CYCLE_DELTA;
		data->num_checks = 0;
	}
}

void			ft_corewar(t_vm *data)
{
	int last_loop;
	int check_equal;

	while (data->dump_loop != data->loop && data->carriages)
	{
		check_equal = 1;
		last_loop = (data->cycle_to_die > 0 ? data->cycle_to_die : 1) +
		data->loop;
		data->num_live = 0;
		while (data->loop < last_loop)
		{
			if (data->loop == data->dump_loop)
			{
				check_equal = 0;
				break ;
			}
			else
				option_loop(data);
		}
		if (check_equal)
			check_and_free_data(data);
	}
}
