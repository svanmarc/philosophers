/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:20:52 by svanmarc          #+#    #+#             */
/*   Updated: 2023/11/25 17:23:14 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	set_philos_forks_id(t_philo **philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (philos[i]->id % 2 == 0)
		{
			philos[i]->even_fork_id = philos[i]->id;
			philos[i]->odd_fork_id = philos[i]->id + 1;
			if (philos[i]->odd_fork_id == data->nb_philos)
				philos[i]->odd_fork_id = 0;
		}
		else
		{
			philos[i]->even_fork_id = philos[i]->id + 1;
			if (philos[i]->even_fork_id == data->nb_philos)
				philos[i]->even_fork_id = 0;
			philos[i]->odd_fork_id = philos[i]->id;
		}
		i++;
	}
}

t_philo	**init_philos( t_data *data)
{
	int		i;
	t_philo	**philos;

	i = 0;
	philos = ft_calloc(data->nb_philos, sizeof(t_philo *));
	if (!philos)
		exit_error("malloc philo failed", philos, data);
	while (i < data->nb_philos)
	{
		philos[i] = ft_calloc(1, sizeof(t_philo));
		philos[i]->id = i;
		philos[i]->nb_meals = 0;
		philos[i]->last_meal = get_time();
		philos[i]->data = data;
		philos[i]->mutex_full = NULL;
		philos[i]->mutex_last_meal = NULL;
		philos[i]->mutex_nb_meals = NULL;
		i++;
	}
	return (philos);
}

t_data	*init_data(t_data *data, int ac, char **av)
{
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit_error("malloc data failed", NULL, data);
	data->nb_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_meals = ft_atoi(av[5]);
	else
		data->nb_meals = -1;
	data->next_philo_id = 0;
	data->mutex_next_philo_id = NULL;
	data->mutex_someone_is_dead = NULL;
	data->someone_is_dead = 0;
	data->mutex_all_are_full = NULL;
	data->all_are_full = 0;
	data->mutex_write = NULL;
	data->start_time = get_time();
	return (data);
}
