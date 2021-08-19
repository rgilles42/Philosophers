# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/17 15:06:05 by rgilles           #+#    #+#              #
#    Updated: 2021/08/17 15:06:06 by rgilles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCL = includes
CFLAGS = -Wall -Wextra -Werror

%.o : 		%.c
			${CC} -c ${CFLAGS} -I${INCL} $^ -o $@

test_% : 	tests/test_%.o srcs/%.o
			${CC} ${CFLAGS} -I${INCL} -L${LD_LIBRARY_PATH} -lcriterion -o $@ $^