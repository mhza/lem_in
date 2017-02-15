/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 17:35:24 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/15 18:53:37 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"



void	set_deg(t_bfs *bfs, int value, int id)
{
	bfs->deg[id] = value;
}

void	set_prev(t_bfs *bfs, int id_prev, int id)
{
	bfs->prev[id] = id_prev;
}

void	set_mked(t_bfs *bfs, int value, int id)
{
	bfs->mked[id] = value;
}

void	set_tmp(t_bfs *bfs, int value, int id)
{
	bfs->tmp[id] = value;
}

int		init(t_bfs *bfs, int size, t_anthill *ah)
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
	if (!(bfs->path = (int*)malloc(sizeof(int) * size)))
		return (0);
	i = -1;
	while (++i < size)
	{
		bfs->deg[i] = -1;
		bfs->prev[i] = -1;
		bfs->mked[i] = -1;
		bfs->tmp[i] = 0;
		bfs->path[i] = -1;
	}
	bfs->s = ah->id_start;
	bfs->p = ah->id_end;
	set_deg(bfs, 0, bfs->s);
	set_mked(bfs, 0, bfs->s);
	set_tmp(bfs, 1, bfs->s);
	return (1);
}
