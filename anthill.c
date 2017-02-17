/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anthill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 20:39:03 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/17 20:18:37 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	*get_rooms(char *ln, t_anthill *ah, char *input)
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

static char	*get_tubes(char *ln, t_anthill *ah, char *input)
{
	ah->nb_tubes += 1;
	if (!(ah->tubes = set_tube(ah, ah->tubes, ah->rooms, ln)))
		return (NULL);
	input = ft_strreal(input, ln);
	free(ln);
	return (input);
}

int			free_and_return(int ret, char *ln)
{
	if (ret)
		free(ln);
	return (0);
}

int			putstr_and_free(char *input)
{
	ft_putstr(input);
	free(input);
	return (1);
}

int			get_anthill(int fd, t_anthill *ah)
{
	char	*ln;
	char	*input;
	int		ret;

	ret = get_next_line(fd, &ln);
	input = NULL;
	if (!(input = ft_strreal(input, ln)))
		return (0);
	if (!ln[0] || (ah->ants = ft_atoi(ln)) < 1)
		return (free_and_return(ret, ln));
	free(ln);
	while ((ret = get_next_line(fd, &ln)) && !ft_strchr(ln, '-') && ln[0])
		if (!(input = get_rooms(ln, ah, input)))
			return (0);
	if (ah->id_start == -1 || ah->id_end == -1 || !ah->nb_rooms)
		return (free_and_return(ret, ln));
	if (!init_adjacency_map(ah))
		return (0);
	if (!(input = get_tubes(ln, ah, input)))
		return (0);
	while (get_next_line(fd, &ln) && ln[0])
		if (!(input = get_tubes(ln, ah, input)))
			return (0);
	return (putstr_and_free(input));
}
