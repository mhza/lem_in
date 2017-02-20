/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 11:54:40 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/20 16:07:55 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_info(t_anthill *ah, t_bfs *bfs)
{
	ft_putstr("------------------------------------------------\n");
	ft_putstr("Steps using the shortest path :\n");
	ft_putnbr(ah->ants + bfs->deg[bfs->p] - 1);
	ft_putstr("\n------------------------------------------------\n");
	ft_putstr("All parallel paths from start to finish :\n");
	print_path(ah, bfs);
}

void		print_info_distrib(t_distrib *distrib, int count)
{
	int	i;

	ft_putstr("------------------------------------------------\n");
	ft_putstr("Distribution of ants in each path :\n");
	i = -1;
	while (++i < count + 1)
	{
		ft_putnbr(distrib->ants[i]);
		ft_putchar('\n');
	}
	ft_putstr("------------------------------------------------\n");
	ft_putstr("Total amount of steps with this optimization :\n");
	ft_putnbr(global_cost(distrib, count));
	ft_putstr("\n------------------------------------------------\n");
}

static void	pattern_all(int power, int count)
{
	if (count < 0)
		ft_putstr("Bigger than MAXINT ");
	else
		ft_putnbr(count);
	ft_putstr(" paths of Length ");
	ft_putnbr(power);
	ft_putchar('\n');
}

void		print_all_info(t_anthill *ah)
{
	t_power_m	datas;
	int			power;
	int			count;
	int			i;

	datas.m1 = ah->adjacency;
	datas.m2 = ah->adjacency;
	datas.n = ah->nb_rooms;
	datas.i = 0;
	datas.j = 0;
	power = 0;
	ft_putstr("----------------------------------\n");
	while (++power < MIN(ah->nb_rooms, 100))
	{
		datas.m1 = power_adjacency(&datas, power - 1);
		count = datas.m1[ah->id_start][ah->id_end];
		pattern_all(power, count);
	}
	i = -1;
	while (power > 1 && datas.m1 && ++i < ah->nb_rooms)
		free(datas.m1[i]);
	free(datas.m1);
	ft_putstr("----------------------------------\n");
}

void		print_path(t_anthill *ah, t_bfs *bfs)
{
	int	i;

	i = -1;
	while (++i < bfs->deg[bfs->p])
	{
		ft_putstr(get_room_by_id(ah, bfs->path[i]));
		ft_putstr(" - ");
	}
	ft_putstr(get_room_by_id(ah, ah->id_end));
	ft_putchar('\n');
}
