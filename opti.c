/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 17:00:33 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/18 15:19:34 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		shorter_path_size(t_anthill *ah)
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
	return (power);
}

int		count_shorter_path(t_anthill *ah, int power_path)
{
	t_power_m	datas;
	int			power;

	datas.m1 = ah->adjacency;
	datas.m2 = ah->adjacency;
	datas.n = ah->nb_rooms;
	datas.i = 0;
	datas.j = 0;
	power = 0;
	while (++power < power_path)
		datas.m1 = power_adjacency(&datas);
	return (datas.m1[ah->id_start][ah->id_end]);
}

int		get_id_room(char **ids, char *name)
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

char	*get_room_by_id(t_anthill *ah, int id)
{
	if (ah && ah->rooms && id < ah->nb_rooms)
		return (ah->rooms[id]);
	return (NULL);
}
