/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 07:40:28 by svanmarc          #+#    #+#             */
/*   Updated: 2023/11/25 17:12:23 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_full(t_philo *philo)
{
	int	val;

	if (philo->data->nb_meals != -1)
		return (0);
	pthread_mutex_lock(philo->mutex_full);
	val = philo->is_full;
	pthread_mutex_unlock(philo->mutex_full);
	return (val);
}

int	all_are_full(t_data *data)
{
	int	result;

	if (data->nb_meals == -1)
		return (0);
	pthread_mutex_lock(data->mutex_nb_de_philos_full);
	result = (data->nb_de_philos_full == data->nb_philos);
	pthread_mutex_unlock(data->mutex_nb_de_philos_full);
	return (result);
}

int	someone_is_dead(t_data *data)
{
	int	val;

	pthread_mutex_lock(data->mutex_someone_is_dead);
	val = data->someone_is_dead;
	pthread_mutex_unlock(data->mutex_someone_is_dead);
	return (val);
}

void	thinking(t_philo *philo)
{
	if (someone_is_dead(philo->data) || all_are_full(philo->data))
		return ;
	print_message(philo, "is thinking");
}

void	sleeping(t_philo *philo)
{
	if (someone_is_dead(philo->data) || all_are_full(philo->data))
		return ;
	print_message(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}
