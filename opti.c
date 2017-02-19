/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 17:00:33 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/19 21:01:42 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void	remove_shorter(t_anthill *ah, t_bfs *bfs)
{
	int	i;
	int	j;

	i = 0;
	while (++i < bfs->deg[bfs->p])
	{
		j = 0;
		while (j < ah->nb_rooms)
		{
			ah->adjacency[j][bfs->path[i]] = 0;
			ah->adjacency[bfs->path[i]][j] = 0;
			j++;
		}
	}
	free(bfs->path);
	call_bfs(ah, bfs, 1);
	print_path(ah, bfs);
}

int		is_optimisable(t_anthill *ah)
{
	int	slink;
	int	plink;
	int	i;

	i = 0;
	slink = 0;
	plink = 0;
	while (i < ah->nb_rooms)
	{
		slink += ah->adjacency[ah->id_start][i];
		plink += ah->adjacency[ah->id_end][i];
		i++;
	}
	if (MIN(slink, plink) > 1)
		return (1);
	return (0);
}
