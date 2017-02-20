/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 14:13:28 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/20 18:24:28 by mhaziza          ###   ########.fr       */
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

typedef struct	s_ditrib
{
	int		*ants;
	int		*cost;
	int		*deg;
}				t_distrib;

t_line			*ft_strreal(t_line *tline, char *line);

int				get_anthill(t_anthill *ah);

int				get_id_room(char **ids, char *name);
char			*get_room_by_id(t_anthill *ah, int id);

t_line			*get_rooms(char *ln, t_anthill *ah, t_line *input);
char			**set_id_rooms(t_anthill *ah, char **ids, char *ln);
t_line			*get_tubes(char *ln, t_anthill *ah, t_line *input);

int				init_adjacency_map(t_anthill *ah);
int				**set_adjacency(int **map, int id1, int id2);
int				**power_adjacency(t_power_m *datas, int free_m1);
int				end_start_linked(t_anthill *ah);

int				*call_bfs(t_anthill *ah, t_bfs *bfs, int is_opti);
int				get_top_tmp(t_bfs *bfs, int size);
int				set_path(t_bfs *bfs);
void			print_flow(t_anthill *a, int *p, int d);

int				remove_shorter(t_anthill *ah, t_bfs *bfs);
int				is_optimisable(t_anthill *ah);

int				global_cost(t_distrib *distrib, int count);
void			get_opti(t_anthill *ah, t_bfs *bfs);

void			print_info_distrib(t_distrib *distrib, int count);
void			print_info(t_anthill *ah, t_bfs *bfs);
void			print_all_info(t_anthill *ah);
void			print_path(t_anthill *ah, t_bfs *bfs);

#endif
