/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexic2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:26:32 by bkuksa            #+#    #+#             */
/*   Updated: 2019/09/27 16:26:36 by bkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

int		ft_if_instruction(t_cor *cor, int k)
{
	t_op	*op_t;
	int		i;

	i = -1;
	op_t = g_op_tab;
	while (op_t[++i].name != 0 && cor->slesh_tmp != cor->slesh_n)
	{
		if (ft_strcmp(op_t[i].name, cor->tmp) == 0)
		{
			cor->slesh_tmp = cor->slesh_n;
			cor->op = op_t[i];
			cor->byte++;
			if (k == 1)
			{
				cor->count1 = cor->byte;
				cor->code[cor->count++] = cor->op.opcode;
				cor->count2 = (cor->op.code_type) ? cor->count : 0;
				cor->count = (cor->count2) ? cor->count + 1 : cor->count;
			}
			ft_strdel(&cor->tmp);
			return (1);
		}
	}
	return (0);
}

void	ft_instruction(t_cor *cor)
{
	int		i;

	i = 0;
	cor->byte = (cor->op.code_type) ? cor->byte + 1 : cor->byte;
	while (cor->file[cor->i] && (cor->op.type[i] != 0 && i <= 2))
	{
		while (cor->file[cor->i] && ft_spec_2(cor->file[cor->i]))
			cor->i++;
		if (cor->file[cor->i] == 'r')
			ft_if_reg_error(cor, i);
		else if (cor->file[cor->i] == DIRECT_CHAR)
			ft_if_dir_error(cor, i);
		else if (ft_isdigit(cor->file[cor->i]) || cor->file[cor->i] == '-'
		|| cor->file[cor->i] == LABEL_CHAR)
			ft_if_ind_error(cor, i);
		else if ((cor->file[cor->i] != SEPARATOR_CHAR
							|| !cor->file[cor->i]) && (cor->op.type[i] != 0))
			ft_put_error(cor, 2);
		i++;
		if (cor->file[cor->i] && (i <= 2 && cor->op.type[i] != 0)
			&& cor->file[cor->i] != SEPARATOR_CHAR)
			ft_put_error(cor, 2);
		cor->i = (cor->file[cor->i] == SEPARATOR_CHAR && cor->op.type[i] != 0
				&& i <= 2) ? cor->i + 1 : cor->i;
	}
}

void	ft_if_reg_error(t_cor *cor, int i)
{
	int		t;

	cor->i++;
	if ((cor->op.type[i] & T_REG) == 1 && ft_isdigit(cor->file[cor->i]))
	{
		t = ft_atoi(&cor->file[cor->i]);
		if (t >= 0 && t <= 99)
		{
			while (cor->file[cor->i] && ft_isdigit(cor->file[cor->i]))
				cor->i++;
			while (cor->file[cor->i] && ft_spec_2(cor->file[cor->i]))
				cor->i++;
			cor->byte += 1;
			return ;
		}
	}
	ft_put_error(cor, 2);
}

void	ft_if_dir_error(t_cor *cor, int i)
{
	if ((cor->op.type[i] & T_DIR) == 2 && ++cor->i)
	{
		cor->byte = (cor->op.dir) ? cor->byte + 2 : cor->byte + 4;
		if (ft_isdigit(cor->file[cor->i])
			|| (cor->file[cor->i] == '-' && ft_isdigit(cor->file[cor->i + 1])))
		{
			cor->i = (cor->file[cor->i] == '-') ? cor->i + 1 : cor->i;
			while (cor->file[cor->i] && ft_isdigit(cor->file[cor->i]))
				cor->i++;
			while (cor->file[cor->i] && ft_spec_2(cor->file[cor->i]))
				cor->i++;
			return ;
		}
		if (cor->file[cor->i] && cor->file[cor->i] == ':'
			&& ft_strchr(LABEL_CHARS, cor->file[cor->i + 1]) && ++cor->i)
		{
			while (cor->file[cor->i]
			&& ft_strchr(LABEL_CHARS, cor->file[cor->i]))
				cor->i++;
			while (cor->file[cor->i] && ft_spec_2(cor->file[cor->i]))
				cor->i++;
			return ;
		}
	}
	ft_put_error(cor, 2);
}

void	ft_if_ind_error(t_cor *cor, int i)
{
	if ((cor->op.type[i] & T_IND) == 4)
	{
		cor->byte += 2;
		if (ft_isdigit(cor->file[cor->i])
		|| (cor->file[cor->i] == '-' && ft_isdigit(cor->file[cor->i + 1])))
		{
			cor->i = (cor->file[cor->i] == '-') ? cor->i + 1 : cor->i;
			while (cor->file[cor->i] && ft_isdigit(cor->file[cor->i]))
				cor->i++;
			while (cor->file[cor->i] && ft_spec_2(cor->file[cor->i]))
				cor->i++;
			return ;
		}
		if (cor->file[cor->i] && cor->file[cor->i] == ':'
		&& ft_strchr(LABEL_CHARS, cor->file[cor->i + 1]) && ++cor->i)
		{
			while (cor->file[cor->i]
			&& ft_strchr(LABEL_CHARS, cor->file[cor->i]))
				cor->i++;
			while (cor->file[cor->i] && ft_spec_2(cor->file[cor->i]))
				cor->i++;
			return ;
		}
	}
	ft_put_error(cor, 2);
}
