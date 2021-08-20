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

int	main(int argc, char **argv)
{
	pthread_t		*philothread;
	unsigned int	i;
	t_data			*data;
	struct timeval	start_time;

//	if (sanitize_input(argc, char **argv)){...}
	unsigned int n_philo = ft_atoi(argv[1]);
	philothread = malloc(n_philo * sizeof(pthread_t));
	data = malloc(n_philo * sizeof(t_data));
	if (!data || !philothread)
		return (-1);
	i = -1;
	while (++i < n_philo)
	{
		populate_data(&data[i], argc, argv, i);
		(&data[i])->init_time = &start_time;
		if (i < n_philo - 1)
			(&data[i])->next = &data[i + 1];
		else
			(&data[i])->next = &data[0];
	}
	i = -1;
	gettimeofday(&start_time, NULL);
	while (++i < n_philo)
		pthread_create(&philothread[i], NULL, philo_runtime, &data[i]);
	while (--n_philo >= 0)
		pthread_join(philothread[n_philo], NULL);
}