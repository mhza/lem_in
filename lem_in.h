/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 14:13:28 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/16 11:31:25 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"

typedef struct	s_anthill
{
	int		ants;
	int		nb_rooms;
	int		nb_tubes;
	int		id_start;
	int		id_end;
	char	**rooms;
	char	**tubes;
	int		**adjacency;
}				t_anthill;

typedef struct	s_bfs
{
	int	*deg;
	int	*prev;
	int	*mked;
	int	*tmp;
	int	*path;
	int	s;
	int	p;
}				t_bfs;

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

char			*set_inputstr(char *input, char *ln);

int				get_anthill(int fd, t_anthill *ah);

int				get_id_room(char **ids, char *name);
char			*get_room_by_id(t_anthill *ah, int id);

int				init_adjacency_map(t_anthill *ah);
int				**set_adjacency(int **map, int id1, int id2);

int				*bfs(t_anthill *ah);

void			print_debug(t_bfs *bfs, t_anthill *ah);
void			debug_input(t_anthill *ah);

#endif
