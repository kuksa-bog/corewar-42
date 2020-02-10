/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_players_to_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 20:19:08 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/27 21:20:02 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

t_lst_vm		*add_player_to_list_crn(t_lst_vm **players, char *argv)
{
	t_lst_vm *tmp;
	t_lst_vm *new_player_lst;
	t_player *player;

	tmp = *players;
	while (tmp->next)
		tmp = tmp->next;
	new_player_lst = (t_lst_vm *)malloc(sizeof(t_lst_vm));
	player = (t_player *)malloc(sizeof(t_player));
	player->comment = NULL;
	player->execute_code = NULL;
	player->file_name = argv;
	player->id = 0;
	player->player_name = NULL;
	player->prog_size = 0;
	new_player_lst->data = player;
	new_player_lst->next = NULL;
	tmp->next = new_player_lst;
	return (new_player_lst);
}

t_lst_vm		*add_player_to_list(t_lst_vm **players, char *argv)
{
	t_player *player;

	if (*players == NULL)
	{
		(*players) = (t_lst_vm *)malloc(sizeof(t_lst_vm));
		player = (t_player *)malloc(sizeof(t_player));
		player->comment = NULL;
		player->execute_code = NULL;
		player->file_name = argv;
		player->id = 0;
		player->player_name = NULL;
		player->prog_size = 0;
		(*players)->data = player;
		(*players)->next = NULL;
		return (*players);
	}
	else
		return (add_player_to_list_crn(players, argv));
}
