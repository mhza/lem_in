/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 17:05:45 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/16 10:23:26 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


int	get_top_tmp(t_bfs *bfs, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (bfs->tmp[i])
			return (i);
		i++;
	}
	return (-1);
}

int *bfs(t_anthill *ah)
{
	t_bfs	bfs;
	int		i;
	int		j;

	if (!init(&bfs, ah->nb_rooms, ah))
		return (NULL);
	ft_putstr("DEGRES");
	ft_putchar('\n');
	ft_putints(bfs.deg, ah->nb_rooms);
	ft_putchar('\n');
	ft_putstr("PREVIOUS NODE");
	ft_putchar('\n');
	ft_putints(bfs.prev, ah->nb_rooms);
	ft_putchar('\n');
	ft_putstr("MARKED");
	ft_putchar('\n');
	ft_putints(bfs.mked, ah->nb_rooms);
	ft_putchar('\n');
	ft_putstr("TEMP");
	ft_putchar('\n');
	ft_putints(bfs.tmp, ah->nb_rooms);
	ft_putstr("------------------------");
	ft_putchar('\n');
	while (!bfs.tmp[bfs.p] && (i = get_top_tmp(&bfs, ah->nb_rooms)) != -1)
	{
		printf("nouvea sommet id= %i    nom= %s \n",i, get_room_by_id(ah, i));
		j = 0;
		while (j < ah->nb_rooms)
		{
			printf("while ligne - room is %i\n", j);
			if (bfs.mked[j] == -1 && ah->adjacency[i][j] == 1)
			{
				set_mked(&bfs, 0, j);
				set_tmp(&bfs, 1, j);
				set_prev(&bfs, i, j);
				set_deg(&bfs, bfs.deg[i] + 1, j);
			}
			j++;
			set_mked(&bfs, 1, i);
		}
		set_tmp(&bfs, 0, i);
	}
	ft_putstr("DEGRES");
	ft_putchar('\n');
	ft_putints(bfs.deg, ah->nb_rooms);
	ft_putchar('\n');
	ft_putstr("PREVIOUS NODE");
	ft_putchar('\n');
	ft_putints(bfs.prev, ah->nb_rooms);
	ft_putchar('\n');
	ft_putstr("MARKED");
	ft_putchar('\n');
	ft_putints(bfs.mked, ah->nb_rooms);
	ft_putchar('\n');
	ft_putstr("TEMP");
	ft_putchar('\n');
	ft_putints(bfs.tmp, ah->nb_rooms);
	set_path(&bfs);
	ft_putstr("\n>>>>PATH<<<<\n");
	ft_putints(bfs.path, bfs.deg[bfs.p] + 1);
	return (NULL);
}
