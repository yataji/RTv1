/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:25:19 by yataji            #+#    #+#             */
/*   Updated: 2021/03/14 18:05:46 by yataji           ###   ########.fr       */
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

int			ck(char *str, char *check, int len)
{
	int		i;

	if (str[0] != '\t')
		return (-1);
	if (ft_strncmp(str, check, len) != 0)
		return (-1);
	i = len - 1;
	while (str[i])
	{
		if (str[i] == ':' && str[i + 1] == ':')
			return (-1);
		else if (str[i] == ':' || str[i] == '-' ||
			str[i] == ' ' || str[i] == '\t')
		{
			if (str[i] == ':' && str[i - 1] == ':')
				return (-1);
			i++;
		}
		else if (ft_isdigit(str[i]) == 0)
			return (-1);
		i++;
	}
	return (1);
}
