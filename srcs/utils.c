/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 19:30:35 by rgilles           #+#    #+#             */
/*   Updated: 2021/09/15 16:16:32 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	oob_error(int sign)
{
	errno = ERANGE;
	if (sign == 1)
		return (-1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	unsigned int	result;
	int				sign;

	sign = 1;
	result = 0;
	while (*nptr == '\f' || *nptr == '\t' || *nptr == '\n'
		|| *nptr == '\r' || *nptr == '\v' || *nptr == ' ')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = 10 * result + *nptr - '0';
		nptr++;
		if (result > INT_MAX)
			break ;
	}
	if ((result == (unsigned int)INT_MAX + 1 && sign == -1)
		|| result <= INT_MAX)
		return (sign * result);
	return (oob_error(sign));
}

unsigned int	get_time(struct timeval init_time)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return ((curr_time.tv_sec - init_time.tv_sec) * 1000
		+ (curr_time.tv_usec - init_time.tv_usec) / 1000);
}

void	print_operation(char *s, int id, struct timeval init_t, int killswitch)
{
	if (!killswitch)
		printf("%u ms %d %s\n", get_time(init_t), id + 1, s);
}
