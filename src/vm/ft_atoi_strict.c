/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_strict.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 19:37:12 by vgrynish          #+#    #+#             */
/*   Updated: 2019/10/26 17:51:46 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

int		ft_atoi_strict(char const *str)
{
	int		abs;

	if (*str == '-' || *str == '+')
		++str;
	if (*str == '\0')
		return (0);
	abs = 0;
	while ('0' <= *str && *str <= '9')
	{
		abs = abs * 10 + (int)(*(str++) - '0');
		if (abs < 0 && !(abs == -2147483648 && *str == '\0'))
			return (0);
	}
	if (*str)
		return (0);
	return (1);
}

int		define_next_unic_num(t_lst_vm *players, int cnt_plr)
{
	int			i;
	t_lst_vm	*players_tmp;

	i = 0;
	players_tmp = players;
	while (players_tmp)
	{
		if (((t_player *)players_tmp->data)->id > cnt_plr)
			print_error("Invalid player number");
		players_tmp = players_tmp->next;
	}
	players_tmp = players;
	while (players_tmp)
	{
		if (((t_player *)players_tmp->data)->id == 0)
			((t_player *)players_tmp->data)->id = choose_champ_id(players);
		i++;
		players_tmp = players_tmp->next;
	}
	return (i);
}

void	get_dump(int *j, char **argv, int argc, t_vm *data)
{
	if (*j + 1 == argc || !ft_atoi_strict(argv[*j + 1])
								|| ft_atoi(argv[*j + 1]) < 0)
		print_error("Invalid champion id for option -dump");
	data->dump_loop = ft_atoi(argv[++(*j)]);
}

void	get_n(int *j, char **argv, int *cnt_plr, t_lst_vm **player)
{
	(*j)++;
	found_flg_min_n(argv, j, player);
	(*cnt_plr)++;
}

int		read_inp_str(int argc, char **argv, t_vm *data)
{
	int		j;
	int		cnt_plr;

	j = 1;
	cnt_plr = 0;
	while (j < argc && cnt_plr < MAX_PLAYERS)
	{
		if (ft_strequ(argv[j], "-dump"))
			get_dump(&j, argv, argc, data);
		else if (ft_strequ(argv[j], "-n"))
			get_n(&j, argv, &cnt_plr, &data->players);
		else if (found_point_cor(argv[j]))
		{
			add_player_to_list(&data->players, argv[j]);
			cnt_plr++;
		}
		else if (ft_strequ(argv[j], "-leak"))
			data->show_leak = 1;
		else if (ft_strequ(argv[j], "-s"))
			data->show_without_live = 1;
		else
			print_error("error input");
		j++;
	}
	return (define_next_unic_num(data->players, cnt_plr));
}
