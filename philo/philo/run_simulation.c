/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:43:02 by alabdull          #+#    #+#             */
/*   Updated: 2023/10/09 23:53:50 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->philo_id % 2 == 0)
		ft_usleep(philo->info->time_to_eat, philo);
	while (1)
	{
		pthread_mutex_lock(&(philo->info->lock));
		if (philo->info->dead)
		{
			pthread_mutex_unlock(&(philo->info->lock));
			break ;
		}
		pthread_mutex_unlock(&(philo->info->lock));
		if (((philo->info->count_meals > 0 \
			&& philo->meal_count >= philo->info->count_meals))
			|| philo->info->count_philo == 1)
			return (NULL);
		ft_iseating(philo);
		if (philo->info->count_meals > 0
			&& philo->meal_count >= philo->info->count_meals)
			return (NULL);
		is_sleeping_and_thinking(philo);
	}
	return (NULL);
}

void	run_simulation(t_philo *philo, t_data *info)
{
	int	i;

	i = -1;
	while (++i < info->count_philo)
		pthread_create(&(philo[i].thread), NULL, philosopher, &philo[i]);
	simulation_finished(philo, info);
	i = -1;
	while (++i < info->count_philo)
	{
		pthread_join(philo[i].thread, NULL);
		pthread_mutex_destroy(&(philo[i].ph_lock));
	}
	pthread_mutex_destroy(&(info->lock));
	i = -1;
	while (++i < info->count_philo)
		pthread_mutex_destroy(&(info->forks[i]));
	ft_free(philo, info);
}
