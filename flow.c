/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 15:06:03 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/18 21:47:23 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	sample(t_anthill *a, int *p, int ant, int room)
{
	if (p[room] != a->id_start)
	{
		ft_putstr("L");
		ft_putnbr(ant);
		ft_putstr("-");
		ft_putstr(get_room_by_id(a, p[room]));
		ft_putstr(" ");
	}
}

static void	print_in(t_anthill *a, int *p, int d)
{
	int	i;
	int	j;

	i = 0;
	while (++i <= d + 1)
	{
		j = -1;
		while (++j < MIN(i, a->ants))
			sample(a, p, j + 1, i - j - 1);
		ft_putstr("\n");
	}
}

static void	print_flowing(t_anthill *a, int *p, int d)
{
	int	j;
	int i;

	i = 1;
	while (++i <= a->ants - d)
	{
		j = -1;
		while (++j < d + 1)
			sample(a, p, j + i, d - j);
		ft_putstr("\n");
	}
}

static void	print_out(t_anthill *a, int *p, int d)
{
	int i;
	int	j;

	i = 0;
	while (++i <= MIN(d, a->ants))
	{
		j = 0;
		while (++j + i < MIN(d + 1, a->ants) + 1)
			sample(a, p, MAX(a->ants - d - 1, 0) + j + i, d - j + 1);
		ft_putstr("\n");
	}
}

void		print_flow(t_anthill *a, int *p, int d)
{
	ft_putchar('\n');
	print_in(a, p, d);
	if (a->ants - d - 1 > 0)
		print_flowing(a, p, d);
	print_out(a, p, d);
}
