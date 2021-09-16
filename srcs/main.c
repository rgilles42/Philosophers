/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:23:42 by rgilles           #+#    #+#             */
/*   Updated: 2021/09/15 23:15:44 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	build_data(int argc, char **argv, t_data *data, struct timeval *st_time)
{
	unsigned int	i;
	unsigned int	n_philo;
	int				*killswitch;

	killswitch = malloc(sizeof(int));
	if (!killswitch)
		return (0);
	*killswitch = 0;
	n_philo = ft_atoi(argv[1]);
	i = -1;
	while (++i < n_philo)
	{
		populate_data(&data[i], argc, argv, i);
		data[i].init_time = st_time;
		data[i].killswitch = killswitch;
		if (i < n_philo - 1)
			(&data[i])->next = &data[i + 1];
		else
			(&data[i])->next = &data[0];
	}
	return (1);
}

int	main(int argc, char **argv)
{
	pthread_t		*philothread;
	unsigned int	i;
	t_data			*data;
	struct timeval	start_time;

	if (!sanitize_input(argc, argv))
		return (1);
	philothread = malloc((ft_atoi(argv[1]) + 1) * sizeof(pthread_t));
	data = malloc(ft_atoi(argv[1]) * sizeof(t_data));
	if (!build_data(argc, argv, data, &start_time) || !data || !philothread)
		return (-1);
	i = -1;
	gettimeofday(&start_time, NULL);
	while (++i <= data->n_philo / 2 && 2 * i < data->n_philo)
	{
		printf("Starting philo %u\n", i * 2);
		pthread_create(&philothread[i], NULL, philo_runtime, &data[i * 2]);
	}
	i = -1;
	while (++i < data->n_philo / 2)
	{
		printf("Starting philo %u\n", i * 2 + 1);
		pthread_create(&philothread[i], NULL, philo_runtime, &data[i * 2 + 1]);
	}
	pthread_create(&philothread[data->n_philo], NULL, watcher_runtime, data);
	pthread_detach(philothread[data->n_philo]);
	i = -1;
	while (++i < data->n_philo)
		pthread_join(philothread[i], NULL);
	philo_end(philothread, data);
}
