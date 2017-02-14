/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_anthill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 20:39:03 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/14 21:41:27 by mhaziza          ###   ########.fr       */
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

static char **set_id_rooms(char **ids, char *ln)
{
	char *name;
	int i;

	i = 0;
	while (ln[i] && ln[i] != ' ')
		i++;
	if (!(name = ft_strsub(ln, 0, (size_t)i)))
		return (NULL);
	while (ln[i] && (ln[i] == ' ' || ft_isdigit(ln[i])))
		i++;
	if (ln[i])
		return (NULL);
	ids = ft_realloc(ids, name);
	// free(name);
	return (ids);
}

static char **set_tube(t_anthill *ah, char **tubes, char **rooms, char *ln)
{
	int i;
	int id1;
	int id2;
	char *name;

	i = 0;
	while (ln[i] && ln[i] != '-')
		i++;
	if (!(name = ft_strsub(ln, 0, (size_t)i)))
		return (NULL);
	id1 = get_id_room(rooms, name);
	if (!(name = ft_strsub(ln, i + 1, ft_strlen(ln) - i)))
		return (NULL);
	id2 = get_id_room(rooms, name);
	if (id1 == -1 || id2 == -1)
		return (NULL);
	ah->adjacency = set_adjacency(ah->adjacency, id1, id2);
	return (ft_realloc(tubes, ln));
}

int			get_anthill(int fd, t_anthill *ah)
{
	char	*ln;

	get_next_line(fd, &ln);
	ft_putstr(ft_strreal(ln, "\n"));
	if ((ah->ants = ft_atoi(ln)) < 1)
		return (0);
	while (get_next_line(fd, &ln) && !ft_strchr(ln, '-'))
	{
		if (ft_strchr(ln, ' ') && !ft_strchr(ln, '-') && !ft_strchr(ln, '#'))
		{
			ah->nb_rooms += 1;
			if (!(ah->rooms = set_id_rooms(ah->rooms, ln)))
				return (0);
		}
		else if (!ft_strcmp(ln, "##start"))
			ah->id_start = ah->nb_rooms;
		else if (!ft_strcmp(ln, "##end"))
			ah->id_end = ah->nb_rooms;
		ft_putstr(ft_strreal(ln, "\n"));
	}
	if (!init_adjacency_map(ah))
		return (0);
	ah->nb_tubes += 1;
	if (!(ah->tubes = set_tube(ah, ah->tubes, ah->rooms, ln)))
		return (0);
	ft_putstr(ft_strreal(ln, "\n"));
	while (get_next_line(fd, &ln))
	{
		ah->nb_tubes += 1;
		if (!(ah->tubes = set_tube(ah, ah->tubes, ah->rooms, ln)))
			return (0);
		ft_putstr(ft_strreal(ln, "\n"));

	}
	printf("\n\nah->ants %i\nah->rooms %i\n",ah->ants, ah->nb_rooms);
	printf("ah->tubes %i\n",ah->nb_tubes);
	printf("ah->id_start %i, start name %s\n",ah->id_start, ah->rooms[ah->id_start]);
	printf("ah->id_end   %i,   end name %s\n",ah->id_end, ah->rooms[ah->id_end]);
	printf("\n\nROOMS\n");
	ft_puttab_str(ah->rooms);
	printf("\n\nTUBES\n");
	ft_puttab_str(ah->tubes);
	printf("\n\nADJACENCY MAP\n");
	ft_puttab_int(ah->adjacency, ah->nb_rooms, ah->nb_rooms);
	return (1);
}
