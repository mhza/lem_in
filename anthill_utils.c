/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anthill_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 09:39:41 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/17 20:27:53 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	**realloc_and_check(char **tab, char *neww)
{
	unsigned int	i;
	unsigned int	tab_size;
	char			**tab_tmp;
	int				duplicate;

	tab_size = 0;
	duplicate = 0;
	while (tab && tab[tab_size])
		tab_size++;
	if (!(tab_tmp = (char**)malloc(sizeof(char*) * (tab_size + 2))))
		return (NULL);
	i = 0;
	while (i < tab_size)
	{
		if (!ft_strcmp(tab[i], neww))
			duplicate = 1;
		tab_tmp[i] = tab[i];
		i++;
	}
	tab_tmp[i] = ft_strdup(neww);
	tab_tmp[i + 1] = 0;
	free(tab);
	if (!duplicate)
		return (tab_tmp);
	return (NULL);
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

char	**set_id_rooms(t_anthill *ah, char **ids, char *ln)
{
	char	*name;
	int		i;

	i = 0;
	while (ln[i] && ln[i] != ' ')
		i++;
	if (!(name = ft_strsub(ln, 0, (size_t)i)))
		return (NULL);
	while (ln[i] && (ln[i] == ' ' || ft_isdigit(ln[i])))
		i++;
	if (ln[i])
		return (NULL);
	ah->rooms = realloc_and_check(ids, name);
	free(name);
	return (ah->rooms);
}

char	**set_tube(t_anthill *ah, char **tubes, char **rooms, char *ln)
{
	int		i;
	int		id1;
	int		id2;
	char	*name;

	i = 0;
	while (ln[i] && ln[i] != '-')
		i++;
	if (!(name = ft_strsub(ln, 0, (size_t)i)))
		return (NULL);
	id1 = get_id_room(rooms, name);
	free(name);
	if (!(name = ft_strsub(ln, i + 1, ft_strlen(ln) - i)))
		return (NULL);
	id2 = get_id_room(rooms, name);
	free(name);
	if (id1 == -1 || id2 == -1)
		return (NULL);
	ah->adjacency = set_adjacency(ah->adjacency, id1, id2);
	ah->tubes = realloc_and_check(tubes, ln);
	return (ah->tubes);
}
