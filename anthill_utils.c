/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anthill_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 09:39:41 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/18 15:34:51 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	**realloc_and_check(char **tab, char *neww, int ok)
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
	if (!duplicate || ok)
		return (tab_tmp);
	return (NULL);
}

static char	**set_id_rooms(t_anthill *ah, char **ids, char *ln)
{
	char	*name;
	int		i;
	int		wrong;

	wrong = 0;
	i = ft_strlen(ln) - 1;
	while (i && ft_isdigit(ln[i]))
		i--;
	if (ln[i] != ' ' && ln[i] != '-')
		return (NULL);
	i = ln[i] == '-' ? i - 2 : i - 1;
	while (i && ft_isdigit(ln[i]))
		i--;
	if (ln[i] != ' ' && ln[i] != '-')
		return (NULL);
	i = ln[i] == '-' ? i - 2 : i - 1;
	if (!(name = ft_strsub(ln, 0, i + 1)))
		return (NULL);
	ah->rooms = realloc_and_check(ids, name, 0);
	free(name);
	return (ah->rooms);
}

static char	**set_tube(t_anthill *ah, char **tubes, char **rooms, char *ln)
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
	ah->tubes = realloc_and_check(tubes, ln, 1);
	return (ah->tubes);
}

char		*get_rooms(char *ln, t_anthill *ah, char *input)
{
	if (!ft_strchr(ln, '#'))
	{
		ah->nb_rooms += 1;
		if (!(ah->rooms = set_id_rooms(ah, ah->rooms, ln)))
			return (NULL);
	}
	else if (!ft_strcmp(ln, "##start"))
		ah->id_start = ah->nb_rooms;
	else if (!ft_strcmp(ln, "##end"))
		ah->id_end = ah->nb_rooms;
	input = ft_strreal(input, ln);
	free(ln);
	return (input);
}

char		*get_tubes(char *ln, t_anthill *ah, char *input)
{
	ah->nb_tubes += 1;
	if (!(ah->tubes = set_tube(ah, ah->tubes, ah->rooms, ln)))
		return (NULL);
	input = ft_strreal(input, ln);
	free(ln);
	return (input);
}
