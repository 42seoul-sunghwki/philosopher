/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:09:37 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/19 22:08:01 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	odd_philo(t_thread *ph, long start_eating)
{
	while (1)
	{
		if (*ph->left_f == FALSE)
		{
			lock_fork(ph->left_fork, ph->left_f, TRUE);
			if (*ph->right_f == FALSE)
			{
				lock_fork(ph->right_fork, ph->right_f, TRUE); //add msg get fork require
				break ;
			}
			else
				lock_fork(ph->left_fork, ph->left_f, FALSE);
		}
		if (check_status(ph, start_eating, NOT_CHECK) == FUN_FAIL)
			return (FUN_FAIL);
		usleep(100);
	}
	return (FUN_SUC);
}

int	even_philo(t_thread *ph, long start_eating)
{
	while (1)
	{
		if (*ph->right_f == FALSE)
		{
			lock_fork(ph->right_fork, ph->right_f, TRUE);
			if (*ph->left_f == FALSE)
			{
				lock_fork(ph->left_fork, ph->left_f, TRUE);
				break ;
			}
			else
				lock_fork(ph->right_fork, ph->right_f, FALSE);
		}
		if (check_status(ph, start_eating, NOT_CHECK) == FUN_FAIL)
			return (FUN_FAIL);
		usleep(100);
	}
	return (FUN_SUC);
}

void	sleep_philo(t_thread *ph, long start_eating, long cmp_time)
{
	long	microsec;

	while (1)
	{
		microsec = ft_microsec_now() - start_eating;
		if (microsec >= cmp_time || microsec >= ph->info.time_to_die
			|| *(ph->flag) == DIE)
			break ;
		else if (cmp_time - microsec >= THOUSAND)
			usleep(THOUSAND / 2);
		else
			usleep(100);
	}
}

int	eating_philo(t_thread *ph, long start_eating)
{
	if (ph->ph_name % 2 == 0)
	{
		if (even_philo(ph, start_eating) == FUN_FAIL)
			return (FUN_FAIL);
	}
	else
	{
		if (odd_philo(ph, start_eating) == FUN_FAIL)
			return (FUN_FAIL);
	}
	return (FUN_SUC);
}

void	*philo(void *input)
{
	t_thread	ph;
	long		start_eating;

	ph = *(t_thread *)input;
	if (ph.ph_name % 2 == 0)
		usleep(200);
	start_eating = ft_microsec_now();
	while (1)
	{
		if (eating_philo(&ph, start_eating) == FUN_FAIL)
			return (NULL);
		start_eating = ft_microsec_now();
		if (check_status(&ph, start_eating, EAT) == FUN_FAIL)
			return (NULL);
		sleep_philo(&ph, start_eating, ph.info.time_to_eat);
		lock_fork(ph.left_fork, ph.left_f, FALSE);
		lock_fork(ph.right_fork, ph.right_f, FALSE);
		if (check_status(&ph, start_eating, SLEEP) == FUN_FAIL)
			return (NULL);
		sleep_philo(&ph, start_eating, ph.info.time_to_sleep
			+ ph.info.time_to_eat);
		if (check_status(&ph, start_eating, THINK) == FUN_FAIL)
			return (NULL);
	}
}
