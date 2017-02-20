/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 11:54:40 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/20 14:54:34 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


void		print_info(t_anthill *ah, t_bfs *bfs)
{
	t_distrib	distrib;
	int			n;
	int			count;

	ft_putstr("------------------------------------------------\n");
	ft_putstr("Cost using only the shortest path is : ");
	ft_putnbr(ah->ants + bfs->deg[bfs->p] - 1);
	ft_putstr("\n------------------------------------------------\n");
	ft_putstr("All separated paths from ");
	ft_putstr(get_room_by_id(ah, ah->id_start));
	ft_putstr(" to ");
	ft_putstr(get_room_by_id(ah, ah->id_end));
	ft_putstr(" are :\n");
	print_path(ah, bfs);

	if ((n = is_optimisable(ah)))
	{
		init_distrib(&distrib, n);
		distrib.deg[0] = bfs->deg[bfs->p];
		distrib.deg[1] = remove_shorter(ah, bfs);
	}
	count = 1;
	while (is_optimisable(ah) && ++count)
		distrib.deg[count] = remove_shorter(ah, bfs);

printf("\n count max (malloc) %i count %i\n", n , count);
ft_putstr("distrib.deg\n");
	ft_putints(distrib.deg, count + 1 );
	do_distrib(&distrib, count + 1, ah->ants);
	ft_putstr("------------------------------------------------\n");
	ft_putstr("Respective amount of ants to put in each path : \n");
	n = -1;
	while (++n < count + 1)
	{
		ft_putnbr(distrib.ants[n]);
		ft_putchar('\n');
	}
	ft_putstr("------------------------------------------------\n");
	ft_putstr("Cost using this distribution is : ");
	ft_putnbr(global_cost(&distrib, count));
	// printf("\nAn optimisation is to put %i ants in first, %i in 2nd, %i in 3rd\n", distrib.ants[0], distrib.ants[1], distrib.ants[2]);
	// printf("new cost is %i\n", global_cost(&distrib, count));
	ft_putstr("\n------------------------------------------------\n");
	free(distrib.ants);
	free(distrib.cost);
	free(distrib.deg);
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
