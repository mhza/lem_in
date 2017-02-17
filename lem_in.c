/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 14:15:40 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/17 23:00:32 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char		*ft_strreal(char *s1, char *s2)
{
	char	*new;

	new = NULL;
	if ((s1 == NULL || *s1 == '\0') && s2)
	{
		if ((new = ft_strnew(ft_strlen(s2) + 1)) == NULL)
			return (NULL);
	}
	else
	{
		if ((new = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)) == NULL)
			return (NULL);
		ft_strcpy(new, s1);
	}
	ft_strcat(new, s2);
	new[ft_strlen(new)] = '\n';
	new[ft_strlen(new)] = '\0';
	free(s1);
	return (new);
}

static int	ret_putstr_fd(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
	if (fd == 2)
		return (0);
	else
		return (1);
}

void		init_struct(t_anthill *ah)
{
	ft_bzero(ah, sizeof(t_anthill));
	ah->rooms = (char**)malloc(sizeof(char*));
	ah->rooms[0] = 0;
	ah->tubes = (char**)malloc(sizeof(char*));
	ah->tubes[0] = 0;
	ah->id_start = -1;
	ah->id_end = -1;
	ah->nb_rooms = 0;
	ah->nb_tubes = 0;
}

void		free_all(t_anthill *ah, t_bfs *bfs)
{
	int i;

	i = -1;
	while (++i < ah->nb_rooms)
		free(ah->rooms[i]);
	i = -1;
	while (++i < ah->nb_tubes)
		free(ah->tubes[i]);
	i = -1;
	while (++i < ah->nb_rooms)
		free(ah->adjacency[i]);
	free(ah->rooms);
	free(ah->tubes);
	if (bfs)
	{
		free(ah->adjacency);
		free(bfs->deg);
		free(bfs->path);
		free(bfs->prev);
		free(bfs->mked);
		free(bfs->tmp);
	}
}

int			main(int ac, char **av)
{
	t_anthill	ah;
	t_bfs		bfs;

	if (ac > 2 ||
		(av[1] && ft_strcmp(av[1], "-info") && ft_strcmp(av[1], "-all")))
		return (ret_putstr_fd("Usage : ./lem-in [-info][-all] < filename", 2));
	init_struct(&ah);
	if (!get_anthill(0, &ah))
		return (ret_putstr_fd("ERROR", 2));
	if (end_start_linked(&ah))
		call_bfs(&ah, &bfs);
	else
	{
		free_all(&ah, NULL);
		return (0);
	}
	print_flow(&ah, bfs.path, bfs.deg[bfs.p]);
	if (ac == 2 && !ft_strcmp(av[1], "-info"))
		print_info(&ah);
	if (ac == 2 && !ft_strcmp(av[1], "-all"))
		print_all_info(&ah);
	free_all(&ah, &bfs);
	return (1);
}
