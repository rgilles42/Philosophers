/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 13:33:17 by rgilles           #+#    #+#             */
/*   Updated: 2021/09/20 15:51:38 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	philo_end(pthread_t *philothread, t_data *data)
{
	int	i;
	int	nb_philo;

	i = -1;
	nb_philo = data->n_philo;
	pthread_mutex_destroy(data[0].killswitch_mutex);
	free(data[0].killswitch_mutex);
	free(data->killswitch);
	while (++i < nb_philo)
	{
		pthread_mutex_destroy(&data[i].fork);
		pthread_mutex_destroy(&data[i].meal_history_access);
		pthread_mutex_destroy(&data[i].n_meals_mutex);
	}
	free(philothread);
	free(data);
}
