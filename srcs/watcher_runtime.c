/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_runtime.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 15:08:30 by rgilles           #+#    #+#             */
/*   Updated: 2021/08/21 15:08:33 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	is_all_finished(t_data *data, int n_philo)
{
	int	i;

	i = -1;
	while (++i < n_philo)
	{
		if ((&data[i])->has_meals_limit != 42)
			return (0);
	}
	return (1);
}

static int	tragic_loss(t_data *data, int n_philo)
{
	int	i;

	i = -1;
	while (++i < n_philo)
	{
		if (get_time(*((&data[i])->init_time)) - (&data[i])->last_meal_start
			>= (&data[i])->t_die)
		{
			print_operation("died", (&data[i])->id, *((&data[i])->init_time));
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
	while (!(is_all_finished(data, n_philo) || tragic_loss(data, n_philo)))
		;
	return (data);
}
