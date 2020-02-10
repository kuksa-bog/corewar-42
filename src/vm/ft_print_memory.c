/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:17:12 by tbondare          #+#    #+#             */
/*   Updated: 2019/10/22 17:48:01 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftcorewar.h"

void	print_address(int i)
{
	char	str[4];
	int		j;

	j = 3;
	ft_memset(str, '0', 4);
	write(1, "0", 1);
	write(1, "x", 1);
	while (j >= 0 && i)
	{
		if (i % 16 > 9)
			str[j] = i % 16 + 'a' - 10;
		else
			str[j] = i % 16 + '0';
		i = i / 16;
		j--;
	}
	write(1, str, 4);
	write(1, " : ", 3);
}

void	next_line_and_print_add(int i, int size)
{
	if (!(i % 32) && size != 0)
	{
		write(1, "\n", 1);
		print_address(i);
	}
}

void	ft_print_memory(const unsigned char *var, size_t size)
{
	int				i;
	char			c;
	unsigned char	prev;

	i = 0;
	print_address(i);
	while (size--)
	{
		prev = var[i];
		prev = prev / 16;
		if (prev % 16 > 9)
			c = prev % 16 - 10 + 'a';
		else
			c = prev % 16 + '0';
		write(1, &c, 1);
		prev = var[i];
		if (prev % 16 > 9)
			c = prev % 16 - 10 + 'a';
		else
			c = prev % 16 + '0';
		write(1, &c, 1);
		i++;
		write(1, " ", 1);
		next_line_and_print_add(i, size);
	}
}
