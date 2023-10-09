/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_finished.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:43:09 by alabdull          #+#    #+#             */
/*   Updated: 2023/10/09 23:55:30 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_sleeping_and_thinking(t_philo *philo)
{
	display_routine(philo->info, philo->philo_id, "is sleeping");
	ft_usleep(philo->info->time_to_sleep, philo);
	display_routine(philo->info, philo->philo_id, "is thinking");
	return (0);
}

int	finished_meals(t_data *info, t_philo *philo)
{
	int	i;
	int	all_ate;

	i = -1;
	all_ate = 1;
	while (++i < info->count_philo && info->count_philo != 1)
	{
		pthread_mutex_lock(&(philo[i].ph_lock));
		if (info->count_meals != -1 && philo[i].meal_count < info->count_meals)
		{
			all_ate = 0;
			pthread_mutex_unlock(&(philo[i].ph_lock));
			return (0);
		}
		pthread_mutex_unlock(&(philo[i].ph_lock));
	}
	if (all_ate == 1 && info->count_meals != -1)
		return (1);
	return (0);
}

int	is_dead(t_data *info, t_philo *philo)
{
	int			i;
	long long	current_time;

	i = -1;
	while (++i < info->count_philo)
	{
		pthread_mutex_lock(&(philo[i].ph_lock));
		current_time = get_time();
		if ((current_time - philo[i].last_meal_time) >= info->time_to_die)
		{
			display_routine(info, i, "has died");
			pthread_mutex_lock(&(philo->info->lock));
			info->dead = 1;
			pthread_mutex_unlock(&(philo->info->lock));
			pthread_mutex_unlock(&(philo[i].ph_lock));
			return (1);
		}
		pthread_mutex_unlock(&(philo[i].ph_lock));
	}
	return (0);
}

int	simulation_finished(t_philo *philo, t_data *info)
{
	while (1)
	{
		pthread_mutex_lock(&(philo->info->lock));
		if (info->dead)
		{
			pthread_mutex_unlock(&(philo->info->lock));
			break ;
		}
		pthread_mutex_unlock(&(philo->info->lock));
		if (is_dead(info, philo) == 1)
			break ;
		if (finished_meals(info, philo) == 1 && info->count_philo != 1)
			break ;
	}
	return (1);
}
