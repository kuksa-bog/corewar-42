/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 11:09:31 by bkuksa            #+#    #+#             */
/*   Updated: 2019/09/30 11:09:35 by bkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

void	ft_reg_write(t_cor *cor, int i)
{
	cor->i++;
	if (cor->count2 != 0)
		cor->code[cor->count2] = (unsigned char)
									((1 | cor->code[cor->count2]) << 2);
	if ((cor->op.type[i] & T_REG) == 1)
	{
		cor->code[cor->count++] = (unsigned char)ft_atoi(&cor->file[cor->i]);
		while (cor->file[cor->i] && ft_isdigit(cor->file[cor->i]))
			cor->i++;
		while (cor->file[cor->i] && ft_spec_3(cor->file[cor->i]))
			cor->i++;
		cor->byte += 1;
		return ;
	}
}

void	ft_dir_ind_write(t_cor *cor)
{
	if (cor->count2 != 0 && cor->file[cor->i] == '%')
		cor->code[cor->count2] = (unsigned char)
									((2 | cor->code[cor->count2]) << 2);
	if (cor->count2 != 0 && cor->file[cor->i] != '%')
		cor->code[cor->count2] = (unsigned char)
									((3 | cor->code[cor->count2]) << 2);
	if ((cor->file[cor->i] == '%' && ++cor->i) || cor->file[cor->i])
	{
		if (ft_isdigit(cor->file[cor->i])
		|| (cor->file[cor->i] == '-' && ft_isdigit(cor->file[cor->i + 1])))
			ft_digit_write(cor);
		else if (cor->file[cor->i] && cor->file[cor->i] == ':'
		&& ft_strchr(LABEL_CHARS, cor->file[cor->i + 1]) && ++cor->i)
		{
			cor->i2 = cor->i - 1;
			ft_lebel_write(cor);
		}
	}
}

void	ft_digit_write(t_cor *cor)
{
	size_t	k;

	k = (size_t)ft_atoi(&cor->file[cor->i]);
	write_bytes(&cor->code[cor->count], &k,
			(cor->op.dir == 0 && cor->file[cor->i - 1] == '%') ? 4 : 2);
	cor->byte = (cor->op.dir == 0 && cor->file[cor->i - 1] == '%')
			? cor->byte + 4 : cor->byte + 2;
	cor->count = (cor->op.dir == 0 && cor->file[cor->i - 1] == '%')
			? cor->count + 4 : cor->count + 2;
	cor->i = (cor->file[cor->i] == '-') ? cor->i + 1 : cor->i;
	while (cor->file[cor->i] && ft_isdigit(cor->file[cor->i]))
		cor->i++;
	while (cor->file[cor->i] && ft_spec_3(cor->file[cor->i]))
		cor->i++;
}

void	ft_lebel_write(t_cor *cor)
{
	int		k;
	size_t	p;
	int		c;

	k = cor->i;
	p = 0;
	while (cor->file[cor->i]
	&& ft_strchr(LABEL_CHARS, cor->file[cor->i]) && ++cor->i)
		p++;
	cor->tmp = ft_strnew(p + 1);
	c = -1;
	while (cor->file[k] && p--)
		cor->tmp[++c] = cor->file[k++];
	cor->tmp[++c] = '\0';
	if (ft_if_lebel(cor) != 1)
		ft_put_error(cor, 2);
	cor->byte = (cor->op.dir == 0 && cor->file[cor->i2 - 1] == '%')
			? cor->byte + 4 : cor->byte + 2;
	cor->count = (cor->op.dir == 0 && cor->file[cor->i2 - 1] == '%')
			? cor->count + 4 : cor->count + 2;
	while (cor->file[cor->i] && ft_spec_3(cor->file[cor->i]))
		cor->i++;
}

int		ft_if_lebel(t_cor *cor)
{
	t_n		*s;
	int		k;

	s = cor->num;
	while (s)
	{
		if (!ft_strcmp(s->name, cor->tmp))
			break ;
		s = s->next;
	}
	if (!s)
		return (0);
	else
	{
		k = s->num_byte - cor->count1;
		write_bytes(&cor->code[cor->count], &k,
				(!cor->op.dir && cor->file[cor->i2 - 1] == '%') ? 4 : 2);
	}
	return (1);
}
