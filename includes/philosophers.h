/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 22:05:06 by rgilles           #+#    #+#             */
/*   Updated: 2021/09/20 17:08:50 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>

enum {is_eating, is_sleeping, is_thinking, is_dead};

typedef struct s_data
{
	struct timeval	*init_time;
	unsigned int	n_philo;
	int				has_meals_limit;
	int				n_meals;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	t_die;
	unsigned int	id;
	int				state;
	int				*killswitch;
	pthread_mutex_t	fork;
	pthread_mutex_t	meal_history_access;
	pthread_mutex_t	*killswitch_mutex;
	pthread_mutex_t	n_meals_mutex;
	unsigned int	last_meal_start;
	struct s_data	*next;

}				t_data;

int				sanitize_input(int argc, char **argv);
void			populate_data(t_data *data, int ac, char **av, unsigned int i);
void			*philo_runtime(void *datavoid);
int				is_killswitch_engaged(t_data *data);
void			philo_eat(t_data *data);
void			*watcher_runtime(void *datavoid);
unsigned int	get_time(struct timeval init_time);
void			print_operation(char *s, t_data *data);
int				ft_atoi(const char *nptr);
void			philo_end(pthread_t *philothread, t_data *data);
#endif