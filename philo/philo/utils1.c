/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alabdull <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:43:15 by alabdull          #+#    #+#             */
/*   Updated: 2023/10/09 23:58:00 by alabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

long long	ft_atoi(const char *str)
{
	size_t		i;
	long		sign;
	long long	nbr;

	i = 0;
	nbr = 0;
	sign = 1;
	while (str[i] && is_space(str[i]))
		i++;
	if (str[i] == '-' && ++i)
		sign = -1;
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (sign == -1 && nbr * 10 < nbr)
			return (-1);
		if (sign == 1 && nbr * 10 < nbr)
			return (-1);
		nbr = (nbr * 10) + (str[i] - 48);
		i++;
	}
	return (nbr * sign);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((long long)tv.tv_sec * 1000) + ((long long)tv.tv_usec / 1000));
}

void	ft_usleep(int ms, t_philo *philo)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < ms)
	{
		pthread_mutex_lock(&(philo->info->lock));
		if (philo->info->dead)
		{
			pthread_mutex_unlock(&(philo->info->lock));
			break ;
		}
		pthread_mutex_unlock(&(philo->info->lock));
		usleep(100);
	}
}

void	ft_free(t_philo *philo, t_data *info)
{
	free(info->forks);
	free(info->fork_state);
	free(philo);
}
