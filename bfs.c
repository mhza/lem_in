/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 17:05:45 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/17 23:27:44 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	set_path(t_bfs *bfs)
{
	int i;
	int deg_p;

	if ((deg_p = bfs->deg[bfs->p]) < 0)
		return (-1);
	if (!(bfs->path = (int*)malloc(sizeof(int) * (deg_p + 1))))
		return (-1);
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

int			get_deg_min(t_bfs *bfs, int size)
{
	int	i;
	int	min;

	i = -1;
	min = 1;
	while (++i < size)
		if (bfs->deg[i] < min && bfs->deg[i] > 0)
			min = bfs->deg[i];
	return (min);
}

static int	get_top_tmp(t_bfs *bfs, int size)
{
	int	i;
	int	min;
	int exist_one;
	int top;

	i = -1;
	exist_one = 0;
	min = get_deg_min(bfs, size);
	i = -1;
	while (++i < size)
	{
		if (bfs->tmp[i])
			exist_one = 1;
		if (bfs->tmp[i] && (bfs->deg[i] == min || i == bfs->s))
			return (i);
	}
	top = -1;
	while (exist_one && top == -1 && min++)
	{
		i = -1;
		while (++i < size)
			if (bfs->tmp[i] && (bfs->deg[i] == min))
				return (i);
	}
	return (-1);
}

int			*call_bfs(t_anthill *ah, t_bfs *bfs)
{
	int		i;
	int		j;

	if (!init(bfs, ah->nb_rooms, ah))
		return (NULL);
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
	return (NULL);
}
