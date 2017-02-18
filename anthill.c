/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anthill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 20:39:03 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/18 22:21:09 by mhaziza          ###   ########.fr       */
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

static int		free_and_return(int ret, char *ln)
{
	if (ret)
		free(ln);
	return (0);
}

static int		putstr_and_free(t_line *input)
{
	t_line	*tmp;

	while (input)
	{
		ft_putstr(input->ln);
		input = input->next;
	}
	while (input)
	{
		tmp = input->next;
		free(input->ln);
		free(input->next);
		input = tmp;
	}
	return (1);
}

int				get_anthill(int fd, t_anthill *ah)
{
	char	*ln;
	t_line	*input;
	int		ret;

	ret = get_next_line(fd, &ln);
	input = NULL;
	if (!(input = ft_strreal(input, ln)))
		return (0);
	if (!ln[0] || (ah->ants = ft_atoi(ln)) < 1)
		return (free_and_return(ret, ln));
	free(ln);
	while ((ret = get_next_line(fd, &ln)) && ln && ln[0] && is_room(ln))
		if (!(input = get_rooms(ln, ah, input)))
			return (0);
	if (ah->id_start == -1 || ah->id_end == -1 || !ah->nb_rooms)
		return (free_and_return(ret, ln));
	if (!init_adjacency_map(ah))
		return (0);
	if (!(input = get_tubes(ln, ah, input)))
		return (0);
	while (get_next_line(fd, &ln) && ln && ln[0])
		if (!(input = get_tubes(ln, ah, input)))
			return (0);
	putstr_and_free(input);
	return (1);
}
