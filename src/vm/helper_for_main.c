/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_for_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:25:51 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/27 22:14:25 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

t_player		*get_player_by_id(t_lst_vm *players, int id)
{
	t_lst_vm	*tmp;
	t_player	*player;

	tmp = players;
	while (tmp)
	{
		player = tmp->data;
		if (player->id == id)
			return (player);
		tmp = tmp->next;
	}
	return (NULL);
}

void			print_player_info(t_player *crn)
{
	ft_putstr("* Player ");
	ft_putnbr(crn->id);
	ft_putstr(", weighing ");
	ft_putnbr(crn->prog_size);
	ft_putstr(" bytes, \"");
	ft_putstr(crn->player_name);
	ft_putstr("\" (\"");
	ft_putstr(crn->comment);
	ft_putstr("\") !\n");
}

t_carriage		*new_carriage(void)
{
	static int	id_carriage = 0;
	t_carriage	*carriage;

	carriage = ft_memalloc(sizeof(t_carriage));
	id_carriage++;
	carriage->id = id_carriage;
	return (carriage);
}

void			lst_vm_push(t_lst_vm **old_lst, void *data)
{
	t_lst_vm		*new_lst;

	new_lst = malloc(sizeof(t_lst_vm));
	new_lst->data = data;
	new_lst->next = *old_lst;
	*old_lst = new_lst;
}

void			load_players(t_vm *data)
{
	int const	step = MEM_SIZE / data->count_player;
	int			player_id;
	t_carriage	*carriage;
	t_lst_vm	*players;
	t_player	*player;

	players = data->players;
	ft_putstr("Introducing contestants...\n");
	player_id = 1;
	while (player_id <= data->count_player)
	{
		player = get_player_by_id(data->players, player_id);
		print_player_info(player);
		ft_memcpy(data->map + step * (player_id - 1),
			player->execute_code, player->prog_size);
		carriage = new_carriage();
		carriage->player_id = player_id;
		carriage->regs[1] = -player_id;
		carriage->pc = step * (player_id - 1);
		lst_vm_push(&data->carriages, carriage);
		player_id++;
	}
}
