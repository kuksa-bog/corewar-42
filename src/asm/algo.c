/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:55:15 by bkuksa            #+#    #+#             */
/*   Updated: 2019/09/06 14:55:18 by bkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

void	ft_valid_lex_3(t_cor *cor)
{
	size_t	k;
	int		fd;

	cor->code = (unsigned char *)ft_memalloc(sizeof(char) * (cor->byte + 1));
	ft_bzero(cor->code, (size_t)cor->byte + 1);
	k = (size_t)cor->byte;
	write_bytes(&cor->prog->prog_size, &k, 4);
	cor->byte = 0;
	k = COREWAR_EXEC_MAGIC;
	write_bytes(&(cor->prog->magic), &k, 4);
	if (ft_alg(cor)
		&& (fd = open(cor->rname, O_CREAT | O_TRUNC | O_WRONLY, 0666)) >= 0)
	{
		write(fd, cor->prog, sizeof(t_header));
		write(fd, cor->code, (size_t)cor->byte);
		close(fd);
		ft_putstr("Writing output program to ");
		ft_putstr(cor->rname);
		ft_putchar('\n');
		return ;
	}
	ft_error("ERROR");
}

int		ft_alg(t_cor *cor)
{
	while (cor->file[cor->i])
	{
		ft_space(cor);
		ft_word_2(cor, 0, 0);
		ft_space(cor);
	}
	cor->i--;
	while (cor->file[cor->i] == ' ' || cor->file[cor->i] == '\t'
											|| cor->file[cor->i] == '\n')
	{
		if (cor->file[cor->i] == '\n')
			return (1);
		cor->i--;
	}
	return (0);
}

void	ft_word_2(t_cor *cor, int k, size_t p)
{
	int		c;

	k = cor->i;
	while (cor->file[cor->i] && ft_strchr(LABEL_CHARS, cor->file[cor->i])
	&& cor->i++)
		p++;
	if (cor->tmp)
		ft_strdel(&cor->tmp);
	cor->tmp = ft_strnew(p);
	c = -1;
	while (cor->file[k] && cor->file[k] != ':' && p--)
		cor->tmp[++c] = cor->file[k++];
	if (cor->file[k] && cor->file[cor->i] != ':' && ft_if_instruction(cor, 1))
		ft_instruction_2(cor);
	cor->i = (cor->file[cor->i] == ':') ? cor->i + 1 : cor->i;
}

void	ft_instruction_2(t_cor *cor)
{
	int		i;

	i = 0;
	cor->byte = (cor->op.code_type) ? cor->byte + 1 : cor->byte;
	while (cor->file[cor->i] && cor->op.type[i] != 0 && i <= 2)
	{
		while (cor->file[cor->i] && ft_spec_2(cor->file[cor->i]))
			cor->i++;
		if (cor->file[cor->i] == 'r')
			ft_reg_write(cor, i);
		else if (cor->file[cor->i] == DIRECT_CHAR
		|| (ft_isdigit(cor->file[cor->i]) || cor->file[cor->i] == '-'
		|| cor->file[cor->i] == LABEL_CHAR))
			ft_dir_ind_write(cor);
		while (cor->file[cor->i] && ft_spec_3(cor->file[cor->i]))
			cor->i++;
		i++;
	}
	while (cor->count2 != 0 && i != 3)
	{
		cor->code[cor->count2] = cor->code[cor->count2] << 2;
		i++;
	}
}

int		ft_spec_3(char c)
{
	return (c == ' ' || c == '\t' || c == ',');
}
