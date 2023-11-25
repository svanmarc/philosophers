/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:01:58 by svanmarc          #+#    #+#             */
/*   Updated: 2023/11/25 07:26:03 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_too_low(char **av)
{
	if (ft_atoi(av[2]) < 60)
	{
		printf("Error: time to die is too low\n");
		printf("please, set a time to die > 60\n");
		return (0);
	}
	if (ft_atoi(av[3]) < 60)
	{
		printf("Error: time to eat is too low\n");
		printf("please, set a time to eat > 60\n");
		return (0);
	}
	if (ft_atoi(av[4]) < 60)
	{
		printf("Error: time to sleep is too low\n");
		printf("please, set a time to sleep > 60\n");
		return (0);
	}
	return (1);
}

static int	nbr_philos(char *av)
{
	int	nb;

	nb = ft_atoi(av);
	if (nb < 1)
	{
		printf("Error: at leat 1 philo\n");
		return (0);
	}
	if (nb > PHILO_MAX)
	{
		printf("Error: too many philos, 200 max\n");
		return (0);
	}
	return (1);
}

static int	valid_nbrs(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				printf("Error: not numbers\n");
				return (0);
			}
			if ((ft_atoi(av[i]) < 0) || (ft_atoi(av[i]) > 2147483647))
			{
				printf("Error: wrong numbers\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	valid_nb_args(int ac)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (0);
	}
	return (1);
}

int	is_valid_args(int ac, char **av)
{
	if ((!valid_nb_args(ac)) || (!valid_nbrs(av))
		|| (!nbr_philos(av[1])) || (!time_too_low(av)))
	{
		return (0);
	}
	return (1);
}
