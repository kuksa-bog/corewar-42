/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data_players.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:18:52 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/26 19:05:05 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

unsigned		bytes_to_int(void const *buf)
{
	int			i;
	int			size;
	unsigned	result;

	i = 0;
	size = 4;
	result = 0;
	while (size)
	{
		result += ((unsigned char *)buf)[--size] << i;
		i += 8;
	}
	return (result);
}

void			read_player(int fd, t_player *player)
{
	char		header[2192];
	int			header_size;

	if ((header_size = read(fd, header, 2192)) != 2192)
		print_error("invalid file");
	if (bytes_to_int(header) != COREWAR_EXEC_MAGIC)
		print_error("no magic number");
	if (bytes_to_int(header + 132) != 0 || bytes_to_int(header + 2188) != 0)
		print_error("no null");
	if (!header[4])
		print_error("No player name");
	player->player_name = ft_strdup(header + 4);
	if ((player->prog_size = bytes_to_int(header + 136)) > CHAMP_MAX_SIZE)
		print_error("file size invalid");
	player->comment = ft_strdup(header + 140);
	player->execute_code = malloc(player->prog_size + 1);
	if (read(fd, player->execute_code, player->prog_size + 1)
													!= player->prog_size)
		print_error("exec_code invalid");
}

void			read_data_players(t_vm *data)
{
	t_lst_vm	*tmp;
	int			fd;

	tmp = data->players;
	while (tmp)
	{
		if ((fd = open(((t_player *)tmp->data)->file_name, O_RDONLY)) < 0)
			print_error("file not open");
		read_player(fd, tmp->data);
		close(fd);
		tmp = tmp->next;
	}
}
