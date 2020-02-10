/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 11:06:34 by bkuksa            #+#    #+#             */
/*   Updated: 2019/08/15 11:06:38 by bkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

int		main(int ac, char **av)
{
	t_cor	*cor;

	if (ac < 2 || ac > 2)
		return (ft_error("usage: ./asm champion.s"));
	cor = ft_init();
	if (!(cor->rname = ft_check_name(av[1])))
		return (ft_error("usage: ./asm champion.s"));
	ft_read_file(cor, av[1]);
	ft_lexic(cor);
	return (0);
}

void	write_bytes(void *s1, void *s2, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		((unsigned char *)s1)[i] = ((unsigned char *)s2)[size - i - 1];
		i++;
	}
}

char	*ft_check_name(char *name)
{
	char	*exten;
	char	*rname;

	exten = ft_strrchr(name, '.');
	if (!exten)
		return (NULL);
	if (ft_strcmp(exten, ".s"))
		return (NULL);
	rname = ft_strnew(exten - name + 4);
	ft_strncpy(rname, name, exten - name + 1);
	ft_strncpy(ft_strrchr(rname, '.') + 1, "cor", 3);
	return (rname);
}

t_cor	*ft_init(void)
{
	t_cor	*cor;

	cor = (t_cor *)ft_memalloc(sizeof(t_cor));
	cor->count = 0;
	cor->num = (t_n *)ft_memalloc(sizeof(t_n));
	cor->num->next = NULL;
	cor->i = 0;
	cor->name = 0;
	cor->comm = 0;
	cor->slesh_n = 1;
	cor->slesh_tmp = 0;
	cor->file = NULL;
	cor->byte = 0;
	return (cor);
}

void	ft_read_file(t_cor *cor, char *str)
{
	size_t	len;
	int		fd;

	if ((fd = open(str, O_RDONLY, 0)) < 0)
		ft_error("ERROR");
	len = (size_t)lseek(fd, 0, SEEK_END);
	if ((len < 1) || !(cor->file = ft_memalloc(len + 1)))
		ft_error("ERROR");
	lseek(fd, 0, SEEK_SET);
	read(fd, cor->file, len);
	if (!cor->file)
		ft_error("ERROR");
	close(fd);
}
