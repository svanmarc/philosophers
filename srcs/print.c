/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 08:27:11 by svanmarc          #+#    #+#             */
/*   Updated: 2023/11/25 07:22:52 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*get_color_by_id(int id)
{
	if (id % 6 == 0)
		return (COLOR_RED);
	if (id % 6 == 1)
		return (COLOR_GREEN);
	if (id % 6 == 2)
		return (COLOR_YELLOW);
	if (id % 6 == 3)
		return (COLOR_BLUE);
	if (id % 6 == 4)
		return (COLOR_CYAN);
	if (id % 6 == 5)
		return (COLOR_MAGENTA);
	return (COLOR_WHITE);
}

void	print_message_eating(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->data->mutex_write);
	if (someone_is_dead(philo->data))
	{
		pthread_mutex_unlock(philo->data->mutex_write);
		return ;
	}
	printf("%s [%ld] philo %d: %s {%d, %d}%s\n", get_color_by_id(philo->id),
		(get_time() - philo->data->start_time), philo->id,
		message, philo->even_fork_id, philo->odd_fork_id, COLOR_RESET);
	pthread_mutex_unlock(philo->data->mutex_write);
}

void	print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->data->mutex_write);
	if (someone_is_dead(philo->data))
	{
		pthread_mutex_unlock(philo->data->mutex_write);
		return ;
	}
	printf("%s [%ld] philo %d: %s %s\n", get_color_by_id(philo->id),
		(get_time() - philo->data->start_time), philo->id,
		message, COLOR_RESET);
	pthread_mutex_unlock(philo->data->mutex_write);
}

void	print_message_take_a_fork(t_philo *philo, int fork_id)
{
	pthread_mutex_lock(philo->data->mutex_write);
	if (someone_is_dead(philo->data))
	{
		pthread_mutex_unlock(philo->data->mutex_write);
		return ;
	}
	printf("%s [%ld] philo %d: take a fork  {-------%d}%s\n",
		get_color_by_id(philo->id), (get_time() - philo->data->start_time),
		philo->id, fork_id, COLOR_RESET);
	pthread_mutex_unlock(philo->data->mutex_write);
}

void	print_message_philo_is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->data->mutex_write);
	if (someone_is_dead(philo->data))
	{
		pthread_mutex_unlock(philo->data->mutex_write);
		return ;
	}
	printf("%s [%ld] philo %d: died 💀 %s\n", get_color_by_id(philo->id),
		(get_time() - philo->data->start_time), philo->id, COLOR_RESET);
	pthread_mutex_unlock(philo->data->mutex_write);
}
