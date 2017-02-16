/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 14:15:40 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/16 11:40:56 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char		*ft_strreal(char *s1, char *s2)
{
	char	*new;

	new = NULL;
	if (s1 == NULL || *s1 == '\0')
		new = ft_strdup(s2);
	else if ((new = ft_strjoin(s1, s2)) == NULL)
		return (NULL);
	return (new);
}

char		*set_inputstr(char *input, char *ln)
{
	if (!(input = ft_strreal(input, ln)))
		return (NULL);
	if (!(input = ft_strreal(input, "\n")))
		return (NULL);
	return (input);
}

static int	ret_putstr_fd(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
	if (fd == 2)
		return (0);
	else
		return (1);
}

int			main(int ac, char **av)
{
	// int			fd;
	t_anthill	ah;

	if (ac != 1 || !av[0])
		return (ret_putstr_fd("Usage : ./lem-in", 2));
	// if ((fd = open(av[1], O_RDONLY)) == -1)
	// 	return (0);
	ft_bzero(&ah, sizeof(t_anthill));
	ah.rooms = (char**)malloc(sizeof(char*));
	ah.rooms[0] = 0;
	ah.tubes = (char**)malloc(sizeof(char*));
	ah.tubes[0] = 0;
	if (!get_anthill(0, &ah))
		return (ret_putstr_fd("ERROR", 2));
	debug_input(&ah);
	bfs(&ah);
	return (1);
}
