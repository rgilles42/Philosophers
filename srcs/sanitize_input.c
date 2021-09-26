/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 15:27:48 by rgilles           #+#    #+#             */
/*   Updated: 2021/09/15 11:13:11 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	is_number(char *str)
{
	while (str && *str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

int	sanitize_input(int argc, char **argv)
{
	int	i;

	i = 1;
	if (!(argc == 5 || argc == 6))
	{
		printf("%s: expected number of arguments is 4 or 5\n", argv[0]);
		return (0);
	}
	if (!(is_number(argv[1]) && ft_atoi(argv[1]) > 0 && errno != ERANGE))
	{
		printf("%s: invalid argument 1: \"%s\" : argument should be a %s",
			argv[0], argv[1], "non-nil, strictly positive integer\n");
		return (0);
	}
	while (++i < argc)
	{
		if (!(is_number(argv[i]) && ft_atoi(argv[i]) >= 0 && errno != ERANGE))
		{
			printf("%s: invalid argument %d: \"%s\" : argument should be a %s",
				argv[0], i, argv[i], "positive integer\n");
			return (0);
		}
	}
	return (1);
}
