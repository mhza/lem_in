/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaziza <mhaziza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 14:15:40 by mhaziza           #+#    #+#             */
/*   Updated: 2017/02/15 18:45:06 by mhaziza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*ft_strreal(char *s1, char *s2)
{
	char	*new;

	new = NULL;
	if (s1 == NULL || *s1 == '\0')
		new = ft_strdup(s2);
	else if ((new = ft_strjoin(s1, s2)) == NULL)
		return (NULL);
	// free(s1);
	return (new);
}

static int ret_putstr_fd(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
	if (fd == 2)
		return (0);
	else
		return (1);
}

int	main(int ac, char **av)
{
	int			fd;
	t_anthill	ah;

	if (ac != 2)
		return (ret_putstr_fd("Usage : ./lem-in <filename>", 2));
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (0);
	ft_bzero(&ah, sizeof(t_anthill));
	ah.rooms = (char**)malloc(sizeof(char*));
	ah.rooms[0] = 0;
	ah.tubes = (char**)malloc(sizeof(char*));
	ah.tubes[0] = 0;
	if (!get_anthill(fd, &ah))
		return (ret_putstr_fd("ERROR", 2));
	bfs(&ah);
	return (1);
}
