/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:25:19 by yataji            #+#    #+#             */
/*   Updated: 2021/03/29 15:15:57 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

size_t		ft_strlend(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int			ck(char *str, char *check, int l)
{
	int		i;

	if (str[0] != ' ')
		return (-1);
	if (ft_strncmp(str, check, l) != 0)
		return (-1);
	i = l - 1;
	if ((str[l] < '0' || str[l] > '9') && str[l] != '-' && str[l] != '+')
		return (-1);
	while (str[i])
	{
		if ((str[i] == ':' && str[i + 1] == ':') ||
			(str[i] == ':' && str[i + 1] == '\0'))
			return (-1);
		else if (str[i] == ':' || str[i] == '-' ||
			str[i] == ' ')
		{
			if (str[i] == ':' && str[i - 1] == ':')
				return (-1);
		}
		else if (ft_isdigit(str[i]) == 0)
			return (-1);
		i++;
	}
	return (1);
}
