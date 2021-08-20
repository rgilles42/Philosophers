/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 11:25:45 by rgilles           #+#    #+#             */
/*   Updated: 2021/08/19 11:25:47 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	has_reached_max_nb_meals(t_data *data, unsigned int i)
{
	if (data->has_meals_limit)
		if (i == data->n_meals)
			return (1);
	return (0);
}

void	*philo_runtime(void *datavoid)
{
	t_data *data = (t_data*)datavoid;
	unsigned int i;

	i = 0;
	while (++i)
	{
//printf("Locking mutex of philo %u\n", data->id);
		pthread_mutex_lock(&data->fork);
//printf("Locking mutex of philo %u\n", data->next->id);
		pthread_mutex_lock(&data->next->fork);
		print_operation("has taken a fork", data->id, *(data->init_time));
		data->state = IS_EATING;
		print_operation("is eating", data->id, *(data->init_time));
		usleep(data->t_eat);
		pthread_mutex_unlock(&data->fork);
		pthread_mutex_unlock(&data->next->fork);
		if (has_reached_max_nb_meals(data, i))
			break;
		data->state = IS_SLEEPING;
		print_operation("is sleeping", data->id, *(data->init_time));
		usleep(data->t_sleep);
		data->state = IS_THINKING;
		print_operation("is thinking", data->id, *(data->init_time));
	}
	return (NULL);
}
