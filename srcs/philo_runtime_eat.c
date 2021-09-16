/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_runtime_eat.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 16:08:17 by rgilles           #+#    #+#             */
/*   Updated: 2021/09/16 17:01:31 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	is_more_starved(t_data *curr_data, int curr_philo, int dest_philo)
{
	t_data	*dest_data;
	int		ret;

	ret = 0;
	if (curr_philo != 0)
		dest_data = curr_data->next;
	else
	{
		dest_data = curr_data;
		while (dest_philo-- > 0)
			dest_data = dest_data->next;
	}
	pthread_mutex_lock(&curr_data->meal_history_access);
	pthread_mutex_lock(&dest_data->meal_history_access);
	if (curr_data->last_meal_start < dest_data->last_meal_start)
		ret = 1;
	if (curr_data->last_meal_start == dest_data->last_meal_start && curr_philo == 0)
		ret = 1;
	pthread_mutex_unlock(&curr_data->meal_history_access);
	pthread_mutex_unlock(&dest_data->meal_history_access);
	return (ret);
}

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
	pthread_mutex_lock(&data->meal_history_access);
	data->last_meal_start = get_time(*(data->init_time));
	pthread_mutex_unlock(&data->meal_history_access);
	print_operation("is eating weirdly", data->id, *(data->init_time),
		*data->killswitch);
	usleep(data->t_eat);
	pthread_mutex_unlock(&data->next->fork);
	pthread_mutex_unlock(&data->fork);
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
	pthread_mutex_lock(&data->meal_history_access);
	data->last_meal_start = get_time(*(data->init_time));
	pthread_mutex_unlock(&data->meal_history_access);
	print_operation("is eating", data->id, *(data->init_time),
		*data->killswitch);
	usleep(data->t_eat);
	pthread_mutex_unlock(&data->fork);
	pthread_mutex_unlock(&data->next->fork);
}

void	philo_eat(t_data *data, int i)
{
	if (data->id == (i + data->n_philo - 1) % (int)data->n_philo)
		philo_eat_even(data);
	else
		philo_eat_odd(data);
}
