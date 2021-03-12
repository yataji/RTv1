/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:00:48 by yataji            #+#    #+#             */
/*   Updated: 2021/03/12 17:49:31 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			main(int ac, char **av)
{
	t_rtv1	rt;
	int		fd;

	rt.lights = NULL;
	if ((fd = open(av[1], O_RDONLY)) && ac != 2)
		return (0);
	if (parse(&rt, fd) == -1)
	{
		ft_putendl("error parsing");
		return (0);
	}
	rt.mlx = init();
	draw(rt);
	mlx_put_image_to_window(rt.mlx.ptr, rt.mlx.win_ptr, rt.mlx.img_ptr, 0, 0);
	mlx_hook(rt.mlx.win_ptr, 2, 0, &keypress, &rt.mlx);
	mlx_loop(rt.mlx.ptr);
	return (0);
}
