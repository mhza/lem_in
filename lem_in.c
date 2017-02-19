/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 14:15:40 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/19 20:57:59 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	ret_putstr_fd(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
	if (fd == 2)
		return (0);
	else
		return (1);
}

static int	init_struct(t_anthill *ah)
{
	ft_bzero(ah, sizeof(t_anthill));
	if (!(ah->rooms = (char**)malloc(sizeof(char*))))
		return (0);
	ah->rooms[0] = 0;
	if (!(ah->tubes = (char**)malloc(sizeof(char*))))
		return (0);
	ah->tubes[0] = 0;
	ah->id_start = -1;
	ah->id_end = -1;
	ah->nb_rooms = 0;
	ah->nb_tubes = 0;
	return (1);
}

static int	free_all(t_anthill *ah, t_bfs *bfs, int ret)
{
	int i;

	i = -1;
	while (ah->rooms && ++i < ah->nb_rooms)
		free(ah->rooms[i]);
	i = -1;
	while (ah->tubes && ++i < ah->nb_tubes)
		free(ah->tubes[i]);
	i = -1;
	while (ah->adjacency && ++i < ah->nb_rooms)
		free(ah->adjacency[i]);
	free(ah->rooms);
	free(ah->tubes);
	free(ah->adjacency);
	if (bfs)
	{
		free(bfs->deg);
		free(bfs->path);
		free(bfs->prev);
		free(bfs->mked);
		free(bfs->tmp);
	}
	return (ret);
}

int			main(int ac, char **av)
{
	t_anthill	ah;
	t_bfs		bfs;

	if (ac > 2 || (av[1] && ft_strcmp(av[1], "-info")
						&& ft_strcmp(av[1], "-all")))
		return (ret_putstr_fd("Usage : ./lem-in [-info][-all] < filename", 2));
	if (!init_struct(&ah))
		return (0);
	if (!get_anthill(&ah))
	{
		free_all(&ah, NULL, 0);
		return (ret_putstr_fd("ERROR", 2));
	}
	if (end_start_linked(&ah))
		call_bfs(&ah, &bfs, 0);
	else
		return (free_all(&ah, NULL, 0));
	print_flow(&ah, bfs.path, bfs.deg[bfs.p]);
	if (ac == 1)
		return (free_all(&ah, &bfs, 1));
	if (!ft_strcmp(av[1], "-info"))
		print_info(&ah, &bfs);
	else if (!ft_strcmp(av[1], "-all"))
		print_all_info(&ah);
	return (free_all(&ah, &bfs, 1));
}
