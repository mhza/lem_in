/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 17:35:24 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/16 13:11:49 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_debug(t_bfs *bfs, t_anthill *ah)
{
	ft_putstr("------------------------\n");
	ft_putstr("DEGRES");
	ft_putchar('\n');
	ft_putints(bfs->deg, ah->nb_rooms);
	ft_putchar('\n');
	ft_putstr("PREVIOUS NODE");
	ft_putchar('\n');
	ft_putints(bfs->prev, ah->nb_rooms);
	ft_putchar('\n');
	ft_putstr("MARKED");
	ft_putchar('\n');
	ft_putints(bfs->mked, ah->nb_rooms);
	ft_putchar('\n');
	ft_putstr("TEMP");
	ft_putchar('\n');
	ft_putints(bfs->tmp, ah->nb_rooms);
	if (bfs->path)
	{
		printf("degre p : %i\n", bfs->deg[bfs->p]);
		ft_putstr("\n>>>>PATH<<<<\n");
		ft_putints(bfs->path, bfs->deg[bfs->p] + 1);
	}
	ft_putstr("\n------------------------\n");
}

void	debug_input(t_anthill *ah)
{
	printf("\n\nah->ants %i\nah->rooms %i\n", ah->ants, ah->nb_rooms);
	printf("ah->tubes %i\n", ah->nb_tubes);
	printf("ah->id_start %i, start name %s\n",
	ah->id_start, ah->rooms[ah->id_start]);
	printf("ah->id_end   %i,   end name %s\n",
	ah->id_end, ah->rooms[ah->id_end]);
	printf(">>>   ROOMS\n");
	ft_puttab_str(ah->rooms);
	printf(">>>   TUBES\n");
	ft_puttab_str(ah->tubes);
	printf(">>>   ADJACENCY MAP\n");
	ft_puttab_int(ah->adjacency, ah->nb_rooms, ah->nb_rooms);
}

void 	print_power(t_anthill *ah)
{
	t_power_m datas;

	datas.m1 = ah->adjacency;
	datas.m2 = ah->adjacency;
	datas.n =  ah->nb_rooms;
	datas.i = 0;
	datas.j = 0;
	printf(">>>   ADJACENCY MAP POWER 2\n");
	datas.m1 = power_adjacency(&datas);
	ft_puttab_int(datas.m1, ah->nb_rooms, ah->nb_rooms);
	printf(">>>   ADJACENCY MAP POWER 3\n");
	datas.m1 = power_adjacency(&datas);
	ft_puttab_int(datas.m1, ah->nb_rooms, ah->nb_rooms);
	printf(">>>   ADJACENCY MAP POWER 4\n");
	datas.m1 = power_adjacency(&datas);
	ft_puttab_int(datas.m1, ah->nb_rooms, ah->nb_rooms);
}
