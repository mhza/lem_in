/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anthill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 20:39:03 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/19 13:28:13 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		is_room(char *ln)
{
	int i;

	if (!ft_strcmp(ln, "##start") || !ft_strcmp(ln, "##end") || ln[0] == '#')
		return (1);
	i = ft_strlen(ln) - 1;
	while (i && ft_isdigit(ln[i]))
		i--;
	if (ln[i] != ' ' && ln[i] != '-')
		return (0);
	i = ln[i] == '-' ? i - 2 : i - 1;
	while (i && ft_isdigit(ln[i]))
		i--;
	if (ln[i] != ' ' && ln[i] != '-')
		return (0);
	i = ln[i] == '-' ? i - 1 : i;
	while (--i)
		if (ln[i] == '-')
			return (0);
	return (1);
}

static int		putstr_and_free(t_line *input, int ok, char *ln)
{
	t_line	*tmp;

	while (input)
	{
		tmp = input;
		if (ok)
			ft_putstr(input->ln);
		input = input->next;
		free(tmp->ln);
		free(tmp);
	}
	if (!ok)
		free(ln);
	return (ok);
}

int				get_anthill(int fd, t_anthill *ah)
{
	char	*ln;
	t_line	*input;
	int		ret;

	if ((ret = get_next_line(fd, &ln)) == -1)
		return (0);
	input = NULL;
	if (!(input = ft_strreal(NULL, ln)))
		return (0);
	if (!ln[0] || (ah->ants = ft_atoi(ln)) < 1)
		return (putstr_and_free(input, 0, ln));
	free(ln);
	while ((ret = get_next_line(fd, &ln)) && ln && ln[0] && is_room(ln))
		if (!(get_rooms(ln, ah, input)))
			return (putstr_and_free(input, 0, ln));
	if (ah->id_start == -1 || ah->id_end == -1 || ah->id_start == ah->id_end ||
		!ah->nb_rooms)
		return (putstr_and_free(input, 0, ln));
	if (!init_adjacency_map(ah) || !(get_tubes(ln, ah, input)))
		return (putstr_and_free(input, 0, ln));
	while (get_next_line(fd, &ln) && ln && ln[0])
		if (!(get_tubes(ln, ah, input)))
			return (putstr_and_free(input, 0, ln));
	return (putstr_and_free(input, 1, ln));
}
