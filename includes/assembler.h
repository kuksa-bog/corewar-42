/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 13:04:16 by bkuksa            #+#    #+#             */
/*   Updated: 2019/10/28 20:13:59 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H

# include "libft.h"
# include "op.h"

typedef struct		s_n
{
	char			*name;
	int				num_byte;
	struct s_n		*next;
}					t_n;

typedef struct		s_cor
{
	t_header		*prog;
	int				count;
	int				count1;
	int				count2;
	unsigned char	*code;
	t_op			op;
	t_n				*num;
	char			*file;
	char			*rname;
	int				slesh_n;
	int				slesh_tmp;
	int				name;
	int				comm;
	int				i;
	int				i2;
	int				byte;
	char			*tmp;
}					t_cor;

char				*ft_check_name(char *name);
t_cor				*ft_init(void);
void				ft_read_file(t_cor *cor, char *str);
void				write_bytes(void *dst, void *src, size_t n);

void				ft_lexic(t_cor *cor);
void				ft_valid_lex(t_cor *cor, char *s, int size, char *file);
void				ft_valid_lex_2(t_cor *cor);
void				ft_word(t_cor *cor, int k, size_t p);
void				ft_lebel(t_cor *cor);

int					ft_if_instruction(t_cor *cor, int k);
void				ft_instruction(t_cor *cor);
void				ft_if_reg_error(t_cor *cor, int i);
void				ft_if_dir_error(t_cor *cor, int i);
void				ft_if_ind_error(t_cor *cor, int i);

int					ft_comm(t_cor *cor, int i);
int					ft_error(char *er);
void				ft_put_error(t_cor *cor, int i);
void				ft_space(t_cor *cor);
int					ft_spec_2(char c);

int					ft_spec_3(char c);
void				ft_valid_lex_3(t_cor *cor);
int					ft_alg(t_cor *cor);
void				ft_word_2(t_cor *cor, int k, size_t p);
void				ft_instruction_2(t_cor *cor);

void				ft_reg_write(t_cor *cor, int i);
void				ft_dir_ind_write(t_cor *cor);
void				ft_digit_write(t_cor *cor);
void				ft_lebel_write(t_cor *cor);
int					ft_if_lebel(t_cor *cor);

#endif
