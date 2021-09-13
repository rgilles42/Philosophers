/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 19:34:49 by rgilles           #+#    #+#             */
/*   Updated: 2021/09/13 15:27:59 by rgilles          ###   ########.fr       */
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
		data->n_meals = (unsigned int)ft_atoi(argv[5]);
	}
	data->id = i;
	data->state = is_thinking;
	pthread_mutex_init(&(data->fork), NULL);
}
