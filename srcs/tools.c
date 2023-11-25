/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:42:06 by svanmarc          #+#    #+#             */
/*   Updated: 2023/11/25 17:32:54 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_error(char *str, t_philo **philos, t_data *data)
{
	printf("Error: %s\n", str);
	if (data)
		free(data);
	if (philos)
		free(philos);
	exit(EXIT_FAILURE);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	while (str[i] == ' ' || (str[i] <= 9 && str[i] >= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr * sign);
}

void	free_all(t_philo **philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (philos[i])
		{
			free(data->mutex_forks[i]);
			free(philos[i]->mutex_full);
			free(philos[i]->mutex_last_meal);
			free(philos[i]->mutex_nb_meals);
			free(philos[i]);
		}
		i++;
	}
	free(data->mutex_forks);
	free(data->mutex_write);
	free(data->mutex_someone_is_dead);
	free(data->mutex_all_are_full);
	free(data->mutex_nb_de_philos_full);
	free(data->mutex_next_philo_id);
	free(data);
	free(philos);
}

void	destroy_mutex(t_philo **philos, t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(data->mutex_write);
	pthread_mutex_destroy(data->mutex_someone_is_dead);
	pthread_mutex_destroy(data->mutex_all_are_full);
	pthread_mutex_destroy(data->mutex_nb_de_philos_full);
	pthread_mutex_destroy(data->mutex_next_philo_id);
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(philos[i]->mutex_full);
		pthread_mutex_destroy(philos[i]->mutex_last_meal);
		pthread_mutex_destroy(philos[i]->mutex_nb_meals);
		pthread_mutex_destroy(data->mutex_forks[i]);
		i++;
	}
	free_all(philos, data);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	while (i < count * size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
