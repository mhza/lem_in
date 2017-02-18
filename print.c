/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 11:54:40 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/18 15:45:57 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_info(t_anthill *ah)
{
	t_power_m	datas;
	int			power;

	datas.m1 = ah->adjacency;
	datas.m2 = ah->adjacency;
	datas.n = ah->nb_rooms;
	datas.i = 0;
	datas.j = 0;
	power = 1;
	while (!datas.m1[ah->id_start][ah->id_end])
	{
		datas.m1 = power_adjacency(&datas);
		power++;
	}
	power++;
	ft_putstr("----------------------------------\n");
	ft_putstr("Length of shorter path       ");
	ft_putnbr(power);
	ft_putstr("\nNumber of shorter paths      ");
	ft_putnbr(datas.m1[ah->id_start][ah->id_end]);
	ft_putchar('\n');
}

void	print_all_info(t_anthill *ah)
{
	t_power_m	datas;
	int			power;
	int			count;

	datas.m1 = ah->adjacency;
	datas.m2 = ah->adjacency;
	datas.n = ah->nb_rooms;
	datas.i = 0;
	datas.j = 0;
	power = 0;
	ft_putstr("----------------------------------\n");
	while (++power < ah->nb_rooms)
	{
		count = count_shorter_path(ah, power);
		if (count < 0)
			ft_putstr("Bigger than MAXINT ");
		else
			ft_putnbr(count);
		ft_putstr(" paths of Length ");
		ft_putnbr(power + 1);
		ft_putchar('\n');
		datas.m1 = power_adjacency(&datas);
	}
}

void	print_path(t_anthill *ah, t_bfs *bfs)
{
	int	i;

	i = -1;
	ft_putstr("----------------------------------\n");
	ft_putstr("The shortest path is :\n");
	while (++i < bfs->deg[bfs->p])
	{
		ft_putstr(get_room_by_id(ah, bfs->path[i]));
		ft_putstr(" - ");
	}
	ft_putstr(get_room_by_id(ah, ah->id_end));
	ft_putchar('\n');
}
