/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_runtime_eat.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 16:08:17 by rgilles           #+#    #+#             */
/*   Updated: 2021/09/15 11:13:13 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	philo_eat_even(t_data *data)
{
	pthread_mutex_lock(&data->next->fork);
	print_operation("has taken a fork", data->id, *(data->init_time),
		*data->killswitch);
	if (data->n_philo != 1)
		pthread_mutex_lock(&data->fork);
	else
	{
		while (!*data->killswitch)
			;
		return;
	}
	print_operation("has taken a fork", data->id, *(data->init_time),
		*data->killswitch);
	data->state = is_eating;
	data->last_meal_start = get_time(*(data->init_time));
	print_operation("is eating", data->id, *(data->init_time),
		*data->killswitch);
	usleep(data->t_eat);
	pthread_mutex_unlock(&data->fork);
	pthread_mutex_unlock(&data->next->fork);
}

static void	philo_eat_odd(t_data *data)
{
	pthread_mutex_lock(&data->fork);
	print_operation("has taken a fork", data->id, *(data->init_time),
		*data->killswitch);
	pthread_mutex_lock(&data->next->fork);
	print_operation("has taken a fork", data->id, *(data->init_time),
		*data->killswitch);
	data->state = is_eating;
	data->last_meal_start = get_time(*(data->init_time));
	print_operation("is eating", data->id, *(data->init_time),
		*data->killswitch);
	usleep(data->t_eat);
	pthread_mutex_unlock(&data->fork);
	pthread_mutex_unlock(&data->next->fork);
}

void	philo_eat(t_data *data)
{
	if (data->id % 2 == 0)
		philo_eat_even(data);
	else
		philo_eat_odd(data);
}
