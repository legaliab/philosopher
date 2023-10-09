/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:14:53 by alabdull          #+#    #+#             */
/*   Updated: 2023/10/09 18:14:56 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_data	info;
	t_philo	*philo;

	if (parse_args(ac, av) == -1)
		return (1);
	memset(&info, 0, sizeof(t_data));
	get_data(&info, ac, av);
	initialize_forks(&info);
	initialize_philosophers(&philo, &info);
	run_simulation(philo, &info);
}
