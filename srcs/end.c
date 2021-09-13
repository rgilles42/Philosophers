/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 13:33:17 by rgilles           #+#    #+#             */
/*   Updated: 2021/09/13 15:28:00 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	philo_end(pthread_t *philothread, t_data *data)
{
	int	i;
	int	nb_philo;

	i = -1;
	nb_philo = data->n_philo;
	free(data->killswitch);
	while (++i < nb_philo)
		pthread_mutex_destroy(&(data[i].fork));
	free(philothread);
	free(data);
}
