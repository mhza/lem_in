/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distrib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 12:42:42 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/20 15:02:09 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			init_distrib(t_distrib *distrib, int size)
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

int			global_cost(t_distrib *distrib, int count)
{
	int	i;
	int	max;

	i = -1;
	max = 0;
	while (++i < count)
		max = distrib->cost[i] > max ? distrib->cost[i] : max;
	return (max);
}

int			do_balancing(t_distrib *distrib, int count)
{
	ft_putstr(">> do_balancing\n");
	int	i;
	int	j;
	int	tmp;

	i = -1;
	while (++i < count)
	{
		tmp = (distrib->cost[i] - distrib->cost[0]) / i;
		j = -1;
		while (++j < i)
		{
			distrib->ants[j] += tmp;
			distrib->cost[j] += tmp;
		}
		distrib->ants[j] -= (i - 1) * tmp;
		distrib->cost[j] -= (i - 1) * tmp;
	}
	ft_putstr("distrib.ants  ");
	ft_putints(distrib->ants, count);
	ft_putstr("\ndistrib.cost  ");
	ft_putints(distrib->cost, count);
	ft_putstr("\n");
	return (i);
}

int			do_distrib(t_distrib *distrib, int count, int ants)
{
	ft_putstr(">> do_distrib\n");

	int i;
	int is_opti;

	i = -1;
	// while (!count / ants)
	// 	count -= 1;
	while (++i < count)
	{
		distrib->ants[i] = i == 0 ? ants / count + ants % count : ants / count;
		distrib->cost[i] = distrib->ants[i] + distrib->deg[i] - 1;
	}
	ft_putstr("distrib.ants  ");
	ft_putints(distrib->ants, count);
	ft_putstr("\ndistrib.cost  ");
	ft_putints(distrib->cost, count);
	i = -1;
	is_opti = 1;
	while (++i < count - 1 && is_opti)
		if (MAX(ABS((distrib->cost[i] - distrib->cost[i + 1])), 1) > 1)
				is_opti = 0;
	printf("\n>>>>>> is_opti <<<<<      %i\n", is_opti);
	if (is_opti)
		return (1);
	return (do_balancing(distrib, count));
}
