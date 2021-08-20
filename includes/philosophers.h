/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:05:32 by rgilles           #+#    #+#             */
/*   Updated: 2021/08/17 15:05:34 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOHPERS_H
# define SYMBOL value

# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>

enum {IS_EATING, IS_SLEEPING, IS_THINKING, IS_DEAD};

typedef struct	s_data
{
	struct timeval	*init_time;
	int				has_meals_limit;
	unsigned int	n_meals;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	t_die;
	unsigned int	id;
	int				state;
	pthread_mutex_t	fork;
	struct s_data	*next;

}				t_data;

void	populate_data(t_data *data, int argc, char **argv, unsigned int i);
void	*philo_runtime(void *datavoid);
void	print_operation(char *str, int id, struct timeval init_epoch);
int		ft_atoi(const char *nptr);

#endif