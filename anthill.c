/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anthill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 20:39:03 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/16 15:36:57 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	**set_id_rooms(char **ids, char *ln)
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
	ids = ft_realloc(ids, name);
	return (ids);
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
	if (!(name = ft_strsub(ln, i + 1, ft_strlen(ln) - i)))
		return (NULL);
	id2 = get_id_room(rooms, name);
	if (id1 == -1 || id2 == -1)
		return (NULL);
	ah->adjacency = set_adjacency(ah->adjacency, id1, id2);
	return (ft_realloc(tubes, ln));
}

static char	*get_rooms(char *ln, t_anthill *ah, char *input)
{
	if (ft_strchr(ln, ' ') && !ft_strchr(ln, '-') && !ft_strchr(ln, '#'))
	{
		ah->nb_rooms += 1;
		if (!(ah->rooms = set_id_rooms(ah->rooms, ln)))
			return (NULL);
	}
	else if (!ft_strcmp(ln, "##start"))
		ah->id_start = ah->nb_rooms;
	else if (!ft_strcmp(ln, "##end"))
		ah->id_end = ah->nb_rooms;
	return (set_inputstr(input, ln));
}

static char	*get_tubes(char *ln, t_anthill *ah, char *input)
{
	ah->nb_tubes += 1;
	if (!(ah->tubes = set_tube(ah, ah->tubes, ah->rooms, ln)))
		return (NULL);
	return (set_inputstr(input, ln));
}

int			get_anthill(int fd, t_anthill *ah)
{
	char	*ln;
	char	*input;

	get_next_line(fd, &ln);
	if (!(input = ft_strnew(ft_strlen(ln))))
		return (0);
	if (!(input = set_inputstr(input, ln)))
		return (0);
	if ((ah->ants = ft_atoi(ln)) < 1)
		return (0);
	while (get_next_line(fd, &ln) && !ft_strchr(ln, '-'))
		if (!(input = get_rooms(ln, ah, input)))
			return (0);
	if (ah->id_start == -1 || ah->id_end == -1 || !ah->nb_rooms)
		return (0);
	if (!init_adjacency_map(ah))
		return (0);
	if (!(input = get_tubes(ln, ah, input)))
		return (0);
	while (get_next_line(fd, &ln))
		if (!(input = get_tubes(ln, ah, input)))
			return (0);
	ft_putstr(input);
	return (1);
}
