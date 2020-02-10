/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:49:23 by bkuksa            #+#    #+#             */
/*   Updated: 2019/09/10 16:49:26 by bkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

void	ft_lexic(t_cor *cor)
{
	cor->prog = ft_memalloc(sizeof(t_header));
	while (cor->file[cor->i] && (cor->name == 0 || cor->comm == 0))
	{
		ft_space(cor);
		if (cor->file[cor->i] != '.')
			ft_put_error(cor, 1);
		if (cor->name == 0 && cor->file[cor->i])
			ft_valid_lex(cor, NAME_CMD_STRING,
					PROG_NAME_LENGTH, cor->prog->prog_name);
		ft_space(cor);
		if (cor->comm == 0 && cor->file[cor->i])
			ft_valid_lex(cor, COMMENT_CMD_STRING,
					COMMENT_LENGTH, cor->prog->comment);
	}
	if (cor->name == 0 || cor->comm == 0 || !cor->file[cor->i])
		ft_put_error(cor, 1);
	ft_valid_lex_2(cor);
}

void	ft_valid_lex(t_cor *cor, char *str, int size, char *head)
{
	int		bt;

	bt = 0;
	if (size == 128 && !ft_strncmp(str, &cor->file[cor->i], 5) && ++cor->name)
		cor->i = cor->i + 5;
	if (size == 2048 && !ft_strncmp(str, &cor->file[cor->i], 8) && ++cor->comm)
		cor->i = cor->i + 8;
	if (cor->name == 0 && cor->comm == 0)
		return ;
	while (cor->file[cor->i] && ft_spec_2(cor->file[cor->i]))
		cor->i++;
	if (cor->file[cor->i] != '"')
		ft_put_error(cor, 1);
	ft_bzero(head, (size_t)size + 1);
	while (++cor->i && cor->file[cor->i]
								&& cor->file[cor->i] != '"' && bt < size)
	{
		head[bt++] = cor->file[cor->i];
		if (cor->file[cor->i] == '\n' && (cor->slesh_tmp = cor->slesh_n + 1))
			cor->slesh_n++;
	}
	if ((bt >= size) || !cor->file[cor->i])
		ft_put_error(cor, 1);
	cor->i++;
}

void	ft_valid_lex_2(t_cor *cor)
{
	int		k;

	k = cor->i;
	while (cor->file[cor->i])
	{
		ft_space(cor);
		ft_word(cor, 0, 0);
		ft_space(cor);
		if (cor->file[cor->i] && cor->file[cor->i] == SEPARATOR_CHAR)
			ft_put_error(cor, 1);
	}
	cor->i = k;
	ft_valid_lex_3(cor);
}

void	ft_word(t_cor *cor, int k, size_t p)
{
	int		c;

	k = cor->i;
	while (cor->file[cor->i] && ft_strchr(LABEL_CHARS, cor->file[cor->i])
		&& cor->i++)
		p++;
	if (!cor->file[cor->i] && (cor->num->name == NULL || p == 0))
		ft_put_error(cor, 1);
	cor->tmp = ft_strnew(p + 1);
	c = -1;
	while (cor->file[k] && cor->file[k] != ':' && p--)
		cor->tmp[++c] = cor->file[k++];
	cor->tmp[++c] = '\0';
	if (cor->file[k] && cor->file[k] == ':' && ++cor->i)
		ft_lebel(cor);
	else if (cor->file[k] && ft_if_instruction(cor, 0))
		ft_instruction(cor);
	else if (!ft_if_instruction(cor, 0))
		ft_put_error(cor, 2);
}

void	ft_lebel(t_cor *cor)
{
	t_n		*tmp;

	tmp = cor->num;
	if (tmp->name == NULL)
	{
		tmp->name = ft_strdup(cor->tmp);
		tmp->num_byte = cor->byte + 1;
		tmp->next = NULL;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = (t_n *)ft_memalloc(sizeof(t_n));
		tmp->next->next = NULL;
		tmp = tmp->next;
		tmp->name = ft_strdup(cor->tmp);
		tmp->num_byte = cor->byte + 1;
		tmp->next = NULL;
	}
}
