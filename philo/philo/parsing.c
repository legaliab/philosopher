/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:42:35 by alabdull          #+#    #+#             */
/*   Updated: 2023/10/09 23:54:55 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int ac, char *av[])
{
	int	i;

	if (ac != 5 && ac != 6)
	{
		printf("Error: Invalid number of arguments.\n");
		return (-1);
	}
	i = 0;
	while (++i < ac)
	{
		if (!ft_is_digit_string(av[i]) || ft_atoi(av[i]) <= 0)
		{
			printf("Error: Invalid arguments.\n");
			return (-1);
		}
	}
	return (0);
}

void	get_data(t_data *info, int ac, char *av[])
{
	info->timestamp = get_time();
	info->count_philo = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	info->fork_state = ft_calloc(info->count_philo, sizeof(int));
	if (ac == 6)
		info->count_meals = ft_atoi(av[5]);
	else
		info->count_meals = -1;
}

void	ft_error(t_data *info, char *message)
{
	free(info);
	printf("%s\n", message);
	exit(1);
}

void	initialize_forks(t_data *info)
{
	int	i;

	if (pthread_mutex_init(&(info->lock), NULL))
		ft_error(info, "Error1");
	info->forks = malloc(sizeof(pthread_mutex_t) * info->count_philo);
	if (!(info->forks))
		ft_error(info, "Error2");
	i = -1;
	while (++i < info->count_philo)
		if (pthread_mutex_init(&(info->forks[i]), NULL))
			ft_error(info, "Error3");
}

void	initialize_philosophers(t_philo **philo, t_data *info)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * info->count_philo);
	if (!(philo))
		ft_error(info, "Error4");
	i = -1;
	while (++i < info->count_philo)
	{
		(*philo)[i].philo_id = i;
		(*philo)[i].info = info;
		(*philo)[i].left_fork = i;
		(*philo)[i].holding_fork = 0;
		(*philo)[i].meal_count = 0;
		(*philo)[i].last_meal_time = get_time();
		if (pthread_mutex_init(&((*philo)[i].ph_lock), NULL))
			ft_error(info, "Error6");
		(*philo)[i].right_fork = ((i + 1) % info->count_philo);
		if (info->count_philo % 2 == 0 && i == info->count_philo - 1)
		{
			(*philo)[i].right_fork = i;
			(*philo)[i].left_fork = ((i + 1) % info->count_philo);
		}
	}
}
