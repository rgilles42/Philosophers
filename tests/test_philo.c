/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 11:26:47 by rgilles           #+#    #+#             */
/*   Updated: 2021/08/19 11:26:48 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <criterion/criterion.h>

Test(philo, init)
{
	t_philo *philo;

	philo = philo_create();
	cr_assert_neq(philo, NULL);
	philo_destroy(philo);
}
