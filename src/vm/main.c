/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 20:23:30 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/27 22:20:56 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

unsigned char	*create_mem_map(void)
{
	unsigned char *map;

	map = (unsigned char*)malloc(sizeof(unsigned char) * MEM_SIZE);
	ft_bzero(map, MEM_SIZE);
	return (map);
}

void			default_value(t_vm *data)
{
	(*data).players = NULL;
	(*data).dump_loop = -1;
	(*data).carriages = NULL;
	(*data).count_player = 0;
	(*data).cycle_to_die = CYCLE_TO_DIE;
	(*data).last_live_id = 0;
	(*data).loop = 0;
	(*data).map = create_mem_map();
	(*data).num_checks = 0;
	(*data).num_live = 0;
	(*data).show_leak = 0;
	(*data).show_verbose = 0;
	(*data).show_without_live = 0;
}

int				main(int argc, char **argv)
{
	t_vm			data;

	default_value(&data);
	data.count_player = read_inp_str(argc, argv, &data);
	data.last_live_id = data.count_player;
	if (!data.players)
		print_error("invalid input str");
	read_data_players(&data);
	load_players(&data);
	ft_corewar(&data);
	if (!data.carriages && data.last_live_id)
		print_winner(&data);
	if (data.loop == data.dump_loop)
	{
		ft_print_memory(data.map, MEM_SIZE);
		ft_putchar('\n');
	}
	if (data.show_leak)
		system("leaks -q corewar >&2");
	return (0);
}
