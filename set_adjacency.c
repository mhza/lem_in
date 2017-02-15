/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_adjacency.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 20:43:16 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/15 15:19:59 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


int			get_id_room(char **ids, char *name)
{
	int	i;

	i = 0;
	while (ids && ids[i])
	{
		if (!ft_strcmp(ids[i], name))
			return (i);
		i++;
	}
	return (-1);
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
		if (!(ah->adjacency[i] = (int*)malloc(sizeof(int) * (ah->nb_rooms + 1))))
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
