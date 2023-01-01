/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seowokim <seowokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:02:19 by seowokim          #+#    #+#             */
/*   Updated: 2022/12/27 14:03:20 by seowokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ckt_max_min(long nbr, long next_nbr, int minus)
{
	long	cmp;

	cmp = next_nbr / 10;
	if ((nbr != cmp) && minus == 1)
		return (1);
	else if ((nbr != cmp) && minus == -1)
		return (2);
	return (0);
}

static int	cktspace(const char *str)
{
	int	i;

	i = 0;
	while (!(str[i] == '+' || str[i] == '-'
			|| (str[i] >= 48 && str[i] == 57)))
	{
		if (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\r' || str[i] == '\f' || str[i] == ' ')
			i++;
		else
			return (i);
	}
	return (i);
}

static int	cktminus(const char str)
{
	if (str == '+')
		return (1);
	else if (str == '-')
		return (-1);
	return (1);
}

static int	max_min_return(int *flag)
{
	*flag = 0;
	return (0);
}

long long	ft_atoll(const char *str, int *flag)
{
	int			i;
	int			minus;
	long long	res;
	long long	temp;

	i = cktspace(str);
	res = 0;
	temp = 0;
	minus = cktminus(str[i]);
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		temp = res;
		res = (res * 10) + (str[i] - 48);
		if (ckt_max_min(temp, res, minus) == 1 || \
			ckt_max_min(temp, res, minus) == 2)
			return (max_min_return(flag));
		i++;
	}
	res = res * minus;
	return (res);
}
