/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 15:27:48 by rgilles           #+#    #+#             */
/*   Updated: 2021/09/13 16:37:21 by rgilles          ###   ########.fr       */
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

	i = 0;
	if (!(argc == 5 || argc == 6))
	{
		printf("%s: expected number of arguments is 4 or 5\n", argv[0]);
		return (0);
	}
	while (++i < argc)
	{
		if (!(is_number(argv[i]) && ft_atoi(argv[i]) > 0 && !errno))
		{
			printf("%s: invalid argument \"%s\" : argument should be a %s",
				argv[0], argv[i], "non-nil, strictly positive integer\n");
			return (0);
		}
	}
	return (1);
}
