/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distrib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 12:42:42 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/20 15:38:07 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		init_distrib(t_distrib *distrib, int size)
{
	int	i;

	if (!(distrib->deg = (int*)malloc(sizeof(int) * size)))
		return (0);
	if (!(distrib->cost = (int*)malloc(sizeof(int) * size)))
		return (0);
	if (!(distrib->ants = (int*)malloc(sizeof(int) * size)))
		return (0);
	i = -1;
	while (++i < size)
	{
		distrib->deg[i] = -1;
		distrib->cost[i] = -1;
		distrib->ants[i] = -1;
	}
	return (1);
}

int		global_cost(t_distrib *distrib, int count)
{
	int	i;
	int	max;

	i = -1;
	max = 0;
	while (++i < count)
		max = distrib->cost[i] > max ? distrib->cost[i] : max;
	return (max);
}

int		do_balancing(t_distrib *distrib, int count)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (++i < count)
	{
		tmp = (distrib->cost[i] - distrib->cost[0]);
		j = -1;
		while (++j < i && j < tmp)
		{
			distrib->ants[j] += 1;
			distrib->cost[j] += 1;
		}
		distrib->ants[j] -= j;
	}
	return (i);
}

int		do_distrib(t_distrib *distrib, int count, int ants)
{
	int i;
	int is_opti;

	i = -1;
	while (++i < count)
	{
		distrib->ants[i] = i == 0 ? ants / count + ants % count : ants / count;
		distrib->cost[i] = distrib->ants[i] + distrib->deg[i] - 1;
	}
	i = -1;
	is_opti = 1;
	while (++i < count - 1 && is_opti)
		if (MAX(ABS((distrib->cost[i] - distrib->cost[i + 1])), 1) > 1)
			is_opti = 0;
	if (is_opti)
		return (1);
	return (do_balancing(distrib, count));
}

void	get_opti(t_anthill *ah, t_bfs *bfs)
{
	t_distrib	distrib;
	int			n;
	int			count;

	print_info(ah, bfs);
	if ((n = is_optimisable(ah)))
	{
		init_distrib(&distrib, n);
		distrib.deg[0] = bfs->deg[bfs->p];
		distrib.deg[1] = remove_shorter(ah, bfs);
	}
	count = 1;
	while (is_optimisable(ah) && ++count)
		distrib.deg[count] = remove_shorter(ah, bfs);
	do_distrib(&distrib, count + 1, ah->ants);
	print_info_distrib(&distrib, count);
	free(distrib.ants);
	free(distrib.cost);
	free(distrib.deg);
}
