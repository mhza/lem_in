/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 17:05:45 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/16 11:48:43 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	set_path(t_bfs *bfs)
{
	int i;
	int deg_p;

	deg_p = bfs->deg[bfs->p];
	bfs->path = (int*)malloc(sizeof(int) * (deg_p + 1));
	bfs->path[deg_p] = bfs->p;
	i = deg_p;
	while (i)
	{
		bfs->path[i - 1] = bfs->prev[bfs->path[i]];
		i--;
	}
	return (1);
}

static int	init(t_bfs *bfs, int size, t_anthill *ah)
{
	int	i;

	if (!(bfs->deg = (int*)malloc(sizeof(int) * size)))
		return (0);
	if (!(bfs->prev = (int*)malloc(sizeof(int) * size)))
		return (0);
	if (!(bfs->mked = (int*)malloc(sizeof(int) * size)))
		return (0);
	if (!(bfs->tmp = (int*)malloc(sizeof(int) * size)))
		return (0);
	i = -1;
	while (++i < size)
	{
		bfs->deg[i] = -1;
		bfs->prev[i] = -1;
		bfs->mked[i] = -1;
		bfs->tmp[i] = 0;
	}
	bfs->s = ah->id_start;
	bfs->p = ah->id_end;
	bfs->deg[bfs->s] = 0;
	bfs->mked[bfs->s] = 0;
	bfs->tmp[bfs->s] = 1;
	bfs->path = NULL;
	return (1);
}

static int	get_top_tmp(t_bfs *bfs, int size)
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

int			*call_bfs(t_anthill *ah, t_bfs *bfs)
{
	int		i;
	int		j;

	if (!init(bfs, ah->nb_rooms, ah))
		return (NULL);
	print_debug(bfs, ah);
	while (!bfs->tmp[bfs->p] && (i = get_top_tmp(bfs, ah->nb_rooms)) != -1)
	{
		j = 0;
		while (j < ah->nb_rooms)
		{
			if (bfs->mked[j] == -1 && ah->adjacency[i][j] == 1)
			{
				bfs->mked[j] = 0;
				bfs->tmp[j] = 1;
				bfs->prev[j] = i;
				bfs->deg[j] = bfs->deg[i] + 1;
			}
			j++;
			bfs->mked[i] = 1;
		}
		bfs->tmp[i] = 0;
	}
	set_path(bfs);
	print_debug(bfs, ah);
	return (NULL);
}
