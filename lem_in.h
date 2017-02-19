/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 14:13:28 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/19 12:49:49 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# define MIN(x, y) (x <= y ? x : y)
# define MAX(x, y) (x > y ? x : y)

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

typedef struct	s_power_m
{
	int	**m1;
	int	**m2;
	int	i;
	int	j;
	int	n;
}				t_power_m;

typedef struct	s_line
{
	char			*ln;
	struct s_line	*next;
}				t_line;

t_line			*ft_strreal(t_line *tline, char *line);

int				get_anthill(int fd, t_anthill *ah);

int				get_id_room(char **ids, char *name);
char			*get_room_by_id(t_anthill *ah, int id);

t_line			*get_rooms(char *ln, t_anthill *ah, t_line *input);
t_line			*get_tubes(char *ln, t_anthill *ah, t_line *input);

int				init_adjacency_map(t_anthill *ah);
int				**set_adjacency(int **map, int id1, int id2);
int				**power_adjacency(t_power_m *datas);
int				end_start_linked(t_anthill *ah);

int				*call_bfs(t_anthill *ah, t_bfs *bfs);

void			print_flow(t_anthill *a, int *p, int d);

void			print_debug(t_bfs *bfs, int size);
void			debug_input(t_anthill *ah);
void			print_power(t_anthill *ah);

int				shorter_path_size(t_anthill *ah);
int				count_shorter_path(t_anthill *ah, int power_path);
void			print_info(t_anthill *ah);
void			print_all_info(t_anthill *ah);
void			print_path(t_anthill *ah, t_bfs *bfs);
#endif
