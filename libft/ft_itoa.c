/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-skim <min-skim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:22:22 by min-skim          #+#    #+#             */
/*   Updated: 2022/03/15 13:22:24 by min-skim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_len(int n)
{
	int				len;
	long long		nb;

	nb = (long long)n;
	len = 0;
	if (nb <= 0)
	{
		nb *= -1;
		len++;
	}
	while (nb)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int				len;
	char			*ret;
	long long		num;

	len = count_len(n);
	num = (long long)n;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	if (num < 0)
	{
		ret[0] = '-';
		num *= -1;
	}
	if (num == 0)
		ret[0] = '0';
	ret[len--] = '\0';
	while (num)
	{
		ret[len--] = num % 10 + '0';
		num /= 10;
	}
	return (ret);
}
