/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_runtime.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 15:08:30 by rgilles           #+#    #+#             */
/*   Updated: 2021/09/15 22:56:27 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	tragic_loss(t_data *d, int n_philo)
{
	int	i;
	int	starvation_time;

	i = -1;
	while (++i < n_philo)
	{
		pthread_mutex_lock(&d[i].meal_history_access);
		starvation_time = get_time(*(d[i].init_time)) - d[i].last_meal_start;
		pthread_mutex_unlock(&d[i].meal_history_access);
		if (starvation_time >= (int)d[i].t_die)
		{
			(&d[i])->state = is_dead;
			*(d[i].killswitch) = 1;
			print_operation("died", (&d[i])->id, *((&d[i])->init_time), 0);
			return (1);
		}
	}
	return (0);
}

void	*watcher_runtime(void *datavoid)
{
	t_data			*data;
	unsigned int	n_philo;

	data = (t_data *)datavoid;
	n_philo = data->n_philo;
	while (!tragic_loss(data, n_philo))
		;
	return (NULL);
}
