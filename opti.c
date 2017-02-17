/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 17:00:33 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/17 22:57:48 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		shorter_path_size(t_anthill *ah)
{
	t_power_m	datas;
	int			power;

	datas.m1 = ah->adjacency;
	datas.m2 = ah->adjacency;
	datas.n = ah->nb_rooms;
	datas.i = 0;
	datas.j = 0;
	power = 1;
	while (!datas.m1[ah->id_start][ah->id_end])
	{
		datas.m1 = power_adjacency(&datas);
		power++;
	}
	return (power);
}

int		count_shorter_path(t_anthill *ah, int power_path)
{
	t_power_m	datas;
	int			power;

	datas.m1 = ah->adjacency;
	datas.m2 = ah->adjacency;
	datas.n = ah->nb_rooms;
	datas.i = 0;
	datas.j = 0;
	power = 0;
	while (++power < power_path)
		datas.m1 = power_adjacency(&datas);
	return (datas.m1[ah->id_start][ah->id_end]);
}

void	print_info(t_anthill *ah)
{
	t_power_m	datas;
	int			power;

	datas.m1 = ah->adjacency;
	datas.m2 = ah->adjacency;
	datas.n = ah->nb_rooms;
	datas.i = 0;
	datas.j = 0;
	power = 1;
	while (!datas.m1[ah->id_start][ah->id_end])
	{
		datas.m1 = power_adjacency(&datas);
		power++;
	}
	ft_putstr("----------------------------------\n");
	ft_putstr("Length of shorter path        > ");
	ft_putnbr(power);
	ft_putstr("\nNumber of shorter paths       > ");
	ft_putnbr(datas.m1[ah->id_start][ah->id_end]);
	ft_putchar('\n');
}

void	print_all_info(t_anthill *ah)
{
	t_power_m	datas;
	int			power;

	datas.m1 = ah->adjacency;
	datas.m2 = ah->adjacency;
	datas.n = ah->nb_rooms;
	datas.i = 0;
	datas.j = 0;
	power = 0;
	ft_putstr("-------------------------------\n");
	while (++power < ah->nb_rooms)
	{
		ft_putnbr(count_shorter_path(ah, power));
		ft_putstr(" paths of Length ");
		ft_putnbr(power);
		ft_putchar('\n');
		datas.m1 = power_adjacency(&datas);
	}
}
