/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anthill_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 09:39:41 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/16 09:45:13 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			get_id_room(char **ids, char *name)
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

char		*get_room_by_id(t_anthill *ah, int id)
{
	if (ah && ah->rooms && id < ah->nb_rooms)
		return (ah->rooms[id]);
	return (NULL);
}
