/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:31:47 by svanmarc          #+#    #+#             */
/*   Updated: 2023/11/25 07:15:01 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_forks(char *error_msg, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (data->mutex_forks[i])
		{
			pthread_mutex_destroy(data->mutex_forks[i]);
			free(data->mutex_forks[i]);
		}
		i++;
	}
	if (data->mutex_forks)
		free(data->mutex_forks);
	printf("Error: %s\n", error_msg);
	free(data);
}

void	cleanup_mutexes_philos(char *error_msg, t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		if (philos[i]->mutex_full)
		{
			pthread_mutex_destroy(philos[i]->mutex_full);
			free(philos[i]->mutex_full);
		}
		if (philos[i]->mutex_last_meal)
		{
			pthread_mutex_destroy(philos[i]->mutex_last_meal);
			free(philos[i]->mutex_last_meal);
		}
		if (philos[i]->mutex_nb_meals)
		{
			pthread_mutex_destroy(philos[i]->mutex_nb_meals);
			free(philos[i]->mutex_nb_meals);
		}
		i++;
	}
	printf("Error: %s\n", error_msg);
	free(philos);
}

void	cleanup_mutexes_data(char *error_msg, t_data *data)
{
	if (data->mutex_someone_is_dead)
	{
		pthread_mutex_destroy(data->mutex_someone_is_dead);
		free(data->mutex_someone_is_dead);
	}
	if (data->mutex_all_are_full)
	{
		pthread_mutex_destroy(data->mutex_all_are_full);
		free(data->mutex_all_are_full);
	}
	if (data->mutex_write)
	{
		pthread_mutex_destroy(data->mutex_write);
		free(data->mutex_write);
	}
	if (data->mutex_nb_de_philos_full)
	{
		pthread_mutex_destroy(data->mutex_nb_de_philos_full);
		free(data->mutex_nb_de_philos_full);
	}
	printf("Error: %s\n", error_msg);
	free(data);
}

void	cleanup(char *error_msg, t_philo **philos, t_data *data)
{
	if (philos)
		cleanup_mutexes_philos(error_msg, philos);
	if (data)
		cleanup_mutexes_data(error_msg, data);
	if (data->mutex_forks)
		cleanup_forks(error_msg, data);
	exit(EXIT_FAILURE);
}
