/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_runtime.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 11:25:45 by rgilles           #+#    #+#             */
/*   Updated: 2021/09/13 16:09:19 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	has_reached_max_nb_meals(t_data *data, unsigned int i)
{
	if (data->has_meals_limit)
	{
		if (i == data->n_meals)
			return (1);
	}
	return (0);
}

static void	philo_sleep(t_data *data)
{
	data->state = is_sleeping;
	print_operation("is sleeping", data->id, *(data->init_time),
		*data->killswitch);
	usleep(data->t_sleep);
}

static void	philo_think(t_data *data, int *is_first_turn)
{
	data->state = is_thinking;
	if (!(*is_first_turn && data->id % 2 == 0))
		print_operation("is thinking", data->id, *(data->init_time),
			*data->killswitch);
	*is_first_turn = 0;
}

void	*philo_runtime(void *datavoid)
{
	t_data			*data;
	int				is_first_turn;
	unsigned int	i;

	i = 0;
	is_first_turn = 1;
	data = (t_data *)datavoid;
	while (++i)
	{
		philo_think(data, &is_first_turn);
		if (*data->killswitch == 1)
			break ;
		philo_eat(data);
		if (has_reached_max_nb_meals(data, i))
			break ;
		if (*data->killswitch == 1)
			break ;
		philo_sleep(data);
		if (*data->killswitch == 1)
			break ;
	}
	return (NULL);
}
