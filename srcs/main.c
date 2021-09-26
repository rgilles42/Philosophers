/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 15:23:42 by rgilles           #+#    #+#             */
/*   Updated: 2021/09/20 15:53:29 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	build_data(int argc, char **argv, t_data *data, struct timeval *st_time)
{
	unsigned int	i;
	unsigned int	n_philo;
	int				*killswitch;
	pthread_mutex_t	*kswmutex;

	killswitch = malloc(sizeof(int));
	kswmutex = malloc(sizeof(pthread_mutex_t));
	if (!killswitch || !kswmutex)
		return (0);
	*killswitch = 0;
	n_philo = ft_atoi(argv[1]);
	gettimeofday(st_time, NULL);
	i = -1;
	while (++i < n_philo)
	{
		populate_data(&data[i], argc, argv, i);
		data[i].init_time = st_time;
		data[i].killswitch = killswitch;
		data[i].killswitch_mutex = kswmutex;
		if (i < n_philo - 1)
			(&data[i])->next = &data[i + 1];
		else
			(&data[i])->next = &data[0];
	}
	return (1);
}

int	main(int argc, char **argv)
{
	pthread_t		*ths;
	unsigned int	i;
	t_data			*data;
	struct timeval	start_time;

	if (!sanitize_input(argc, argv))
		return (1);
	ths = malloc((ft_atoi(argv[1]) + 1) * sizeof(pthread_t));
	data = malloc(ft_atoi(argv[1]) * sizeof(t_data));
	if (!build_data(argc, argv, data, &start_time) || !data || !ths)
		return (-1);
	pthread_mutex_init(data->killswitch_mutex, NULL);
	i = -1;
	while (++i <= data->n_philo / 2 && 2 * i < data->n_philo)
		pthread_create(&ths[i * 2], NULL, philo_runtime, &data[i * 2]);
	i = -1;
	usleep(data[0].t_sleep);
	while (++i < data->n_philo / 2)
		pthread_create(&ths[i * 2 + 1], NULL, philo_runtime, &data[i * 2 + 1]);
	pthread_create(&ths[data->n_philo], NULL, watcher_runtime, data);
	i = -1;
	while (++i < data->n_philo)
		pthread_join(ths[i], NULL);
	pthread_join(ths[data->n_philo], NULL);
	philo_end(ths, data);
}
