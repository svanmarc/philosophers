/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:17:58 by svanmarc          #+#    #+#             */
/*   Updated: 2023/11/25 17:35:23 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	if (someone_is_dead(philo->data) || all_are_full(philo->data))
		return ;
	pthread_mutex_lock(philo->mutex_last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->mutex_last_meal);
	print_message_eating(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	if (philo->data->nb_meals != -1)
	{
		pthread_mutex_lock(philo->mutex_nb_meals);
		philo->nb_meals++;
		if (philo->nb_meals == philo->data->nb_meals)
		{
			pthread_mutex_lock(philo->mutex_full);
			philo->is_full = 1;
			pthread_mutex_unlock(philo->mutex_full);
			pthread_mutex_lock(philo->data->mutex_nb_de_philos_full);
			philo->data->nb_de_philos_full++;
			pthread_mutex_unlock(philo->data->mutex_nb_de_philos_full);
		}
		pthread_mutex_unlock(philo->mutex_nb_meals);
	}
	pthread_mutex_unlock(philo->data->mutex_forks[philo->even_fork_id]);
	pthread_mutex_unlock(philo->data->mutex_forks[philo->odd_fork_id]);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->data->mutex_forks[philo->even_fork_id]);
	if (someone_is_dead(philo->data) || all_are_full(philo->data))
	{
		pthread_mutex_unlock(philo->data->mutex_forks[philo->even_fork_id]);
		return ;
	}
	print_message_take_a_fork(philo, philo->even_fork_id);
	pthread_mutex_lock(philo->data->mutex_forks[philo->odd_fork_id]);
	if (someone_is_dead(philo->data) || all_are_full(philo->data))
	{
		pthread_mutex_unlock(philo->data->mutex_forks[philo->even_fork_id]);
		pthread_mutex_unlock(philo->data->mutex_forks[philo->odd_fork_id]);
		return ;
	}
	print_message_take_a_fork(philo, philo->odd_fork_id);
}

void	*fn_check_if_this_philo_is_dead(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->mutex_last_meal);
		if (get_time() > philo->last_meal + philo->data->time_to_die)
		{
			print_message_philo_is_dead(philo);
			pthread_mutex_lock(philo->data->mutex_someone_is_dead);
			philo->data->someone_is_dead = 1;
			pthread_mutex_unlock(philo->data->mutex_someone_is_dead);
			pthread_mutex_unlock(philo->mutex_last_meal);
			break ;
		}
		pthread_mutex_unlock(philo->mutex_last_meal);
		if (someone_is_dead(philo->data))
			break ;
		if (all_are_full(philo->data))
			break ;
		if (is_full(philo))
			break ;
		usleep(1000);
	}
	return (NULL);
}

int	waiting_my_turn(t_philo *philo, int wait_my_turn)
{
	while (wait_my_turn)
	{
		pthread_mutex_lock(philo->data->mutex_next_philo_id);
		if (philo->data->next_philo_id == philo->id)
		{
			philo->data->next_philo_id += 2;
			if (philo->data->next_philo_id >= philo->data->nb_philos)
			{
				if (philo->data->next_philo_id % 2)
					philo->data->next_philo_id = 0;
				else
					philo->data->next_philo_id = 1;
			}
			wait_my_turn = 0;
		}
		pthread_mutex_unlock(philo->data->mutex_next_philo_id);
		usleep(1000);
	}
	return (wait_my_turn);
}

void	*routine(void *philo_ptr)
{
	int			wait_my_turn;
	t_philo		*philo;
	int			should_terminate;

	philo = (t_philo *)philo_ptr;
	pthread_create(&philo->thread_check, NULL,
		(void *)fn_check_if_this_philo_is_dead, philo);
	while (1)
	{
		should_terminate = 0;
		pthread_mutex_lock(philo->data->mutex_someone_is_dead);
		if (philo->data->someone_is_dead || philo->data->all_are_full
			|| philo->is_full)
			should_terminate = 1;
		pthread_mutex_unlock(philo->data->mutex_someone_is_dead);
		if (should_terminate)
			return (NULL);
		wait_my_turn = 1;
		wait_my_turn = waiting_my_turn(philo, wait_my_turn);
		take_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
