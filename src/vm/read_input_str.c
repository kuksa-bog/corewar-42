/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 20:08:14 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/28 19:44:07 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

void	print_error(char *error)
{
	ft_putendl(error);
	exit(1);
}

int		found_point_cor(char *file_name)
{
	char	*point_str;

	point_str = ft_strrchr(file_name, '.');
	if (point_str)
	{
		if (ft_strequ(point_str + 1, "cor"))
			return (1);
	}
	return (0);
}

int		found_same_unic_num(t_lst_vm *player, int id)
{
	t_lst_vm	*tmp;

	tmp = player;
	while (tmp)
	{
		if (((t_player *)tmp->data)->id == id)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	found_flg_min_n(char **argv, int *j, t_lst_vm **players)
{
	t_lst_vm	*player;

	if (argv[*j] && ft_atoi_strict(argv[*j]) &&
			ft_atoi(argv[*j]) <= MAX_PLAYERS && ft_atoi(argv[*j]) >= 1)
	{
		if (argv[(*j) + 1] && found_point_cor(argv[++(*j)])
			&& !found_same_unic_num(*players, ft_atoi(argv[(*j) - 1])))
		{
			player = add_player_to_list(players, argv[*j]);
			((t_player *)player->data)->id = ft_atoi(argv[(*j) - 1]);
			return ;
		}
	}
	print_error("Invalid champion id for option -n");
}

int		choose_champ_id(t_lst_vm *players)
{
	int			id;

	id = 1;
	while (found_same_unic_num(players, id))
	{
		++id;
	}
	return (id);
}
