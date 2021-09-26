/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_runtime.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 11:25:45 by rgilles           #+#    #+#             */
/*   Updated: 2021/09/26 13:55:41 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	has_reached_max_nb_meals(t_data *data, int i)
{
	if (data->has_meals_limit)
	{
		pthread_mutex_lock(&data->n_meals_mutex);
		if (i == data->n_meals - 1)
		{
			data->n_meals = -1;
			pthread_mutex_unlock(&data->n_meals_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->n_meals_mutex);
	}
	return (0);
}

static void	philo_sleep(t_data *data)
{
	print_operation("is sleeping", data);
	usleep(data->t_sleep);
}

static void	philo_think(t_data *data)
{
	data->state = is_thinking;
	print_operation("is thinking", data);
}

int	is_killswitch_engaged(t_data *data)
{
	pthread_mutex_lock(data->killswitch_mutex);
	if (*data->killswitch)
	{
		pthread_mutex_unlock(data->killswitch_mutex);
		return (1);
	}
	pthread_mutex_unlock(data->killswitch_mutex);
	return (0);
}

void	*philo_runtime(void *datavoid)
{
	t_data			*data;
	int				i;

	i = -1;
	data = (t_data *)datavoid;
	if (has_reached_max_nb_meals(data, i))
		return (NULL);
	while (++i != -1)
	{
		if (i != 0)
			philo_think(data);
		if (is_killswitch_engaged(data))
			break ;
		philo_eat(data);
		if (has_reached_max_nb_meals(data, i))
			break ;
		if (is_killswitch_engaged(data))
			break ;
		data->state = is_sleeping;
		philo_sleep(data);
		if (is_killswitch_engaged(data))
			break ;
	}
	return (NULL);
}
