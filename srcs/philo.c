/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 11:25:45 by rgilles           #+#    #+#             */
/*   Updated: 2021/08/19 11:25:47 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

t_philo	*philo_create()
{
	return (calloc(1, sizeof(t_philo)));
}

void	philo_destroy(t_philo *p)
{
	free(p);
}
