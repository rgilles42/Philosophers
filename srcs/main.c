/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:23:42 by rgilles           #+#    #+#             */
/*   Updated: 2021/08/17 15:23:49 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	build_data(int argc, char **argv, t_data *data, struct timeval *st_time)
{
	unsigned int	i;
	unsigned int	n_philo;

	n_philo = ft_atoi(argv[1]);
	i = -1;
	while (++i < n_philo)
	{
		populate_data(&data[i], argc, argv, i);
		(&data[i])->init_time = st_time;
		if (i < n_philo - 1)
			(&data[i])->next = &data[i + 1];
		else
			(&data[i])->next = &data[0];
	}
}

int	main(int argc, char **argv)
{
	pthread_t		*philothread;
	unsigned int	i;
	t_data			*data;
	struct timeval	start_time;
	unsigned int	n_philo;

//	if (sanitize_input(argc, char **argv)){...}
	n_philo = ft_atoi(argv[1]);
	philothread = malloc(n_philo * sizeof(pthread_t));
	data = malloc(n_philo * sizeof(t_data));
	if (!data || !philothread)
		return (-1);
	build_data(argc, argv, data, &start_time);
	i = -1;
	gettimeofday(&start_time, NULL);
	while (++i < n_philo)
		pthread_create(&philothread[i], NULL, philo_runtime, &data[i]);
	while (i-- > 0)
		pthread_join(philothread[i], NULL);
}
