/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_runtime.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 15:08:30 by rgilles           #+#    #+#             */
/*   Updated: 2021/09/20 16:13:51 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	tragic_loss(t_data *d)
{
	unsigned int	i;
	int				starvation_time;
	int				philo_has_ended;

	i = -1;
	while (++i < d->n_philo)
	{
		pthread_mutex_lock(&d[i].meal_history_access);
		starvation_time = get_time(*(d[i].init_time)) - d[i].last_meal_start;
		pthread_mutex_unlock(&d[i].meal_history_access);
		philo_has_ended = 0;
		pthread_mutex_lock(&d[i].n_meals_mutex);
		philo_has_ended = d[i].n_meals == -1;
		pthread_mutex_unlock(&d[i].n_meals_mutex);
		if (!philo_has_ended && starvation_time >= (int)d[i].t_die)
		{
			print_operation("died", &d[i]);
			pthread_mutex_lock(d[0].killswitch_mutex);
			*(d[i].killswitch) = 1;
			pthread_mutex_unlock(d[0].killswitch_mutex);
			return (1);
		}
	}
	return (0);
}

static int	has_ended(t_data *d)
{
	unsigned int	i;

	i = -1;
	while (++i < d->n_philo)
	{
		pthread_mutex_lock(&d[i].n_meals_mutex);
		if (d[i].n_meals != -1)
		{
			pthread_mutex_unlock(&d[i].n_meals_mutex);
			return (0);
		}
		pthread_mutex_unlock(&d[i].n_meals_mutex);
	}
	return (1);
}

void	*watcher_runtime(void *datavoid)
{
	t_data			*data;

	data = (t_data *)datavoid;
	while (!has_ended(data) && !tragic_loss(data))
		;
	return (NULL);
}
