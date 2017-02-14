/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 14:13:28 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/14 21:21:44 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
#define LEM_IN_H

# include "libft/libft.h"
typedef struct	s_anthill
{
	int	ants;
	int	nb_rooms;
	int	nb_tubes;
	int	id_start;
	int	id_end;
	char **rooms;
	char **tubes;
	int	**adjacency;
}				t_anthill;

typedef struct	s_room
{
	int		id;
	int		is_start;
	int		is_end;
	char	*name;
	int		*ants;
	int		*room;
}				t_room;

typedef struct	s_ant
{
	int	id;
	int	room;
}				t_ant;

char			*ft_strreal(char *s1, char *s2);

int				get_anthill(int fd, t_anthill *ah);
int				get_id_room(char **ids, char *name);

int				init_adjacency_map(t_anthill *ah);
int				**set_adjacency(int **map, int id1, int id2);

#endif
