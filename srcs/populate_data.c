/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 19:34:49 by rgilles           #+#    #+#             */
/*   Updated: 2021/09/21 13:26:34 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	populate_data(t_data *data, int argc, char **argv, unsigned int i)
{
	data->n_philo = (unsigned int)ft_atoi(argv[1]);
	data->t_die = (unsigned int)ft_atoi(argv[2]);
	data->t_eat = (unsigned int)ft_atoi(argv[3]) * 1000;
	data->t_sleep = (unsigned int)ft_atoi(argv[4]) * 1000;
	data->last_meal_start = 0;
	data->has_meals_limit = 0;
	if (argc == 6)
	{
		data->has_meals_limit = 1;
		data->n_meals = ft_atoi(argv[5]);
	}
	data->id = i;
	data->state = is_thinking;
	data->t_sleep += 500;
	pthread_mutex_init(&data->fork, NULL);
	pthread_mutex_init(&data->meal_history_access, NULL);
	pthread_mutex_init(&data->n_meals_mutex, NULL);
}
