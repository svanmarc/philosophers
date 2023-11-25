/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmarc <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:10:30 by svanmarc          #+#    #+#             */
/*   Updated: 2023/11/25 17:20:38 by svanmarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

# define PHILO_MAX 200
# define COLOR_RESET "\x1b[0m"
# define COLOR_RED "\x1b[31m"
# define COLOR_GREEN "\x1b[32m"
# define COLOR_YELLOW "\x1b[33m"
# define COLOR_BLUE "\x1b[34m"
# define COLOR_MAGENTA "\x1b[35m"
# define COLOR_CYAN "\x1b[36m"
# define COLOR_WHITE "\x1b[37m"
# define BG_GRA "\x1b[40m"
# define BG_RED "\x1b[41m"
# define BG_GRE "\x1b[42m"
# define BG_YEL "\x1b[43m"
# define BG_BLU "\x1b[44m"
# define BG_MAG "\x1b[45m"
# define BG_CYA "\x1b[46m"
# define BG_WHI "\x1b[47m"

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	long			start_time;
	int				next_philo_id;
	pthread_mutex_t	*mutex_next_philo_id;
	int				nb_de_philos_full;
	pthread_mutex_t	*mutex_nb_de_philos_full;
	int				someone_is_dead;
	pthread_mutex_t	*mutex_someone_is_dead;
	int				all_are_full;
	pthread_mutex_t	*mutex_all_are_full;
	pthread_mutex_t	*mutex_write;
	pthread_mutex_t	**mutex_forks;
	t_philo			**philos;
}		t_data;

typedef struct s_philo
{
	pthread_t		thread;

	pthread_t		thread_check;
	int				id;
	int				odd_fork_id;
	int				even_fork_id;
	int				is_full;
	pthread_mutex_t	*mutex_full;
	int				is_dead;
	int				nb_meals;
	pthread_mutex_t	*mutex_nb_meals;
	long			last_meal;
	pthread_mutex_t	*mutex_last_meal;
	t_data			*data;
}			t_philo;

//checking.c
int		is_valid_args(int ac, char **av);

//init.c

t_data	*init_data(t_data *data, int ac, char **av);
t_philo	**init_philos(t_data *data);
void	set_philos_forks_id(t_philo **philos, t_data *data);

//make_thread.c
void	create_threads_philos(t_philo **philos, t_data *data);
void	create_thread_monitor(t_philo **philos, t_data *data);
void	*routine(void *philo);
void	take_forks(t_philo *philo);
long	get_time(void);
void	init_mutex(t_philo **philos, t_data *data);
void	init_mutex_forks(t_data *data);

//monitor.c
void	*monitor(t_data *data);

//state.c
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

//tools.c
int		ft_atoi(char *str);
void	cleanup(char *error_msg, t_philo **philos, t_data *data);
void	cleanup_forks(char *error_msg, t_data *data);
void	cleanup_mutexes_data(char *error_msg, t_data *data);
void	cleanup_mutexes_philos(char *error_msg, t_philo **philos);
void	exit_error(char *str, t_philo **philos, t_data *data);
void	destroy_mutex(t_philo **philos, t_data *data);
void	*ft_calloc(size_t count, size_t size);

//print
void	print_message(t_philo *philo, char *message);
void	print_message_eating(t_philo *philo, char *message);
void	print_message_take_a_fork(t_philo *philo, int fork_id);
void	print_message_leave_a_fork(t_philo *philo, int fork_id);
void	print_message_philo_is_dead(t_philo *philo);
void	print_debug_is_full(t_philo *philo);
void	print_debug_all_are__full(t_data *data);
char	*get_color_by_id(int id);

int		someone_is_dead(t_data *data);
int		philo_is_full(t_philo *philo);
int		all_are_full(t_data *data);
int		is_full(t_philo *philo);

#endif
