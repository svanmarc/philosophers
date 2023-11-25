/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:12:53 by svanmarc          #+#    #+#             */
/*   Updated: 2023/11/25 17:22:35 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex_forks(t_data *data)
{
	int	i;

	i = 0;
	data->mutex_forks = ft_calloc(data->nb_philos, sizeof(pthread_mutex_t *));
	if (!data->mutex_forks)
		cleanup("malloc mutex_forks failed", NULL, data);
	while (i < data->nb_philos)
	{
		data->mutex_forks[i] = ft_calloc(1, sizeof(pthread_mutex_t));
		if (!data->mutex_forks[i])
			cleanup("malloc mutex_forks[i] failed", NULL, data);
		pthread_mutex_init(data->mutex_forks[i], NULL);
		i++;
	}
}

void	init_mutex_philos(t_philo **philos, int i)
{
	philos[i]->mutex_full = ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(philos[i]->mutex_full, NULL);
	philos[i]->mutex_nb_meals = ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(philos[i]->mutex_nb_meals, NULL);
	philos[i]->mutex_last_meal = ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(philos[i]->mutex_last_meal, NULL);
}

void	init_mutex(t_philo **philos, t_data *data)
{
	int	i;

	i = 0;
	data->mutex_write = ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(data->mutex_write, NULL);
	data->mutex_someone_is_dead = ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(data->mutex_someone_is_dead, NULL);
	data->mutex_all_are_full = ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(data->mutex_all_are_full, NULL);
	data->mutex_nb_de_philos_full = ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(data->mutex_nb_de_philos_full, NULL);
	data->mutex_next_philo_id = ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(data->mutex_next_philo_id, NULL);
	if (!data->mutex_someone_is_dead || !data->mutex_all_are_full
		|| !data->mutex_write || !data->mutex_nb_de_philos_full)
		cleanup("malloc mutexes failed", philos, data);
	while (i < data->nb_philos)
	{
		init_mutex_philos(philos, i);
		if (!philos[i]->mutex_full || !philos[i]->mutex_nb_meals
			|| !philos[i]->mutex_last_meal)
			cleanup("malloc mutexes failed", philos, data);
		i++;
	}
	init_mutex_forks(data);
}
