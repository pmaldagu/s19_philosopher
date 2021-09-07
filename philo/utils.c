/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaldagu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:29:05 by pmaldagu          #+#    #+#             */
/*   Updated: 2021/08/04 16:27:26 by pmaldagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_strlen(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long int	value;

	i = 0;
	value = 0;
	while (value < 2147483660 && str[i] >= '0' && str[i] <= '9')
	{
		value = ((value * 10) + (str[i] - 48));
		i++;
	}
	if (value > 2147483647)
		return (-1);
	return (value);
}

int	ft_charsize_int(int n)
{
	int		size;

	size = 0;
	if (n <= 0)
	{
		n *= -1;
		size++;
	}
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*nb;
	int		len;
	int		t;

	t = n;
	len = ft_charsize_int(n);
	nb = malloc(sizeof(char) * (len + 1));
	if (!nb)
		return (NULL);
	nb[len] = '\0';
	if (n < 0)
		n *= -1;
	while (len-- > 0)
	{
		nb[len] = n % 10 + '0';
		n /= 10;
	}
	if (t < 0)
		nb[0] = '-';
	return (nb);
}
