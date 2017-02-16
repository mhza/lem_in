/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacency.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 20:43:16 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/16 13:03:53 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	get_value_ij(t_power_m *datas)
{
	int k;
	int value;

	k = -1;
	value = 0;
	while (++k < datas->n)
		value += datas->m1[datas->i][k] * datas->m2[datas->j][k];
	return (value);
}

int	**power_adjacency(t_power_m *datas)
{
	int	**ret;

	if (!(ret = (int**)malloc(sizeof(int*) * datas->n)))
		return (NULL);
	datas->i = 0;
	while (datas->i < datas->n)
	{
		datas->j = 0;
		if (!(ret[datas->i] = (int*)malloc(sizeof(int) * datas->n)))
			return (NULL);
		while (datas->j < datas->n)
		{
			ret[datas->i][datas->j] = get_value_ij(datas);
			datas->j++;
		}
		datas->i++;
	}
	return (ret);
}

int	init_adjacency_map(t_anthill *ah)
{
	int	i;
	int	j;

	if (!(ah->adjacency = (int**)malloc(sizeof(int*) * (ah->nb_rooms + 1))))
		return (0);
	i = -1;
	while (++i < ah->nb_rooms)
	{
		j = -1;
		if (!(ah->adjacency[i] =
			(int*)malloc(sizeof(int) * (ah->nb_rooms + 1))))
			return (0);
		while (++j < ah->nb_rooms)
			ah->adjacency[i][j] = 0;
	}
	return (1);
}

int	**set_adjacency(int **map, int id1, int id2)
{
	map[id1][id2] = 1;
	map[id2][id1] = 1;
	return (map);
}
