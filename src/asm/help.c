/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 14:38:29 by bkuksa            #+#    #+#             */
/*   Updated: 2019/09/11 14:38:31 by bkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

void	ft_space(t_cor *cor)
{
	while (cor->file[cor->i] && (cor->file[cor->i] == '\n'
	|| cor->file[cor->i] == ' ' || cor->file[cor->i] == COMMENT_CHAR
	|| cor->file[cor->i] == ALT_COMMENT_CHAR
	|| cor->file[cor->i] == '\t'))
	{
		if (cor->file[cor->i] == '\n')
			cor->slesh_n++;
		if (cor->file[cor->i] == COMMENT_CHAR
			|| cor->file[cor->i] == ALT_COMMENT_CHAR)
			cor->i = ft_comm(cor, cor->i + 1);
		cor->i = (cor->file[cor->i]) ? cor->i + 1 : cor->i;
	}
}

int		ft_comm(t_cor *cor, int i)
{
	while (cor->file[i] && cor->file[i] != '\n')
		i++;
	if (cor->file[i] == '\n')
		cor->slesh_n++;
	return (i);
}

int		ft_spec_2(char c)
{
	return (c == ' ' || c == '\t');
}

int		ft_error(char *er)
{
	ft_putstr(er);
	ft_putchar('\n');
	return (1);
}

void	ft_put_error(t_cor *cor, int i)
{
	if (i == 1)
		ft_putstr("\033[31mSyntax error -> line N-");
	if (i == 2)
		ft_putstr("\033[31mLexical error -> line N-");
	ft_putnbr(cor->slesh_n);
	ft_putstr("\033[0m\n");
	exit(1);
}
