/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiqarbac <jiqarbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 12:18:10 by yataji            #+#    #+#             */
/*   Updated: 2021/04/17 16:54:14 by jiqarbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	shadow(t_rtv1 *rt, t_lights *lights, t_obj *close)
{
	t_obj		*tmp;
	t_var		v;
	t_ray		shadow_r;
	t_vect		dirvect;
	double		dist;

	tmp = rt->obj;
	shadow_r.org = lights->pos;
	dirvect = moins(rt->ray.hit, lights->pos);
	dist = dot(dirvect, dirvect);
	shadow_r.dir = normalize(dirvect);
	while (tmp)
	{
		v.near = intersect(tmp, shadow_r) + 0.01;
		if (tmp != close && v.near > 0)
		{
			if (dot(multi(shadow_r.dir, v.near),
					multi(shadow_r.dir, v.near)) < dist)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

static t_color	diffuspclr(t_rtv1 *rt, t_obj *close, t_lights *lights)
{
	double		dot1;
	t_vect		lightdir;
	t_vect		reflect;
	t_color		c;

	c = (t_color){0, 0, 0};
	lightdir = normalize(moins(lights->pos, rt->ray.hit));
	dot1 = dot(close->normal, lightdir);
	if (dot1 > 0)
	{
		c = multi_tcolor(close->color, multi_color(lights->color, 1.0 / 255));
		c = multi_color(c, dot1 * lights->intensity / 100.0);
	}
	reflect = normalize(moins(lightdir, multi(close->normal, 2 * dot1)));
	dot1 = dot(reflect, normalize(moins(rt->ray.hit, rt->ray.org)));
	if (dot1 > 0)
		c = add_color(c, multi_color(lights->color, powf(dot1, 100)
					* lights->intensity / 100.0));
	return (c);
}

t_ray	initmpray(t_ray ray, t_obj *closeobj, t_cam *cam)
{
	t_ray ret;
	t_vect reflect;
	double dot1;

	ret.org = ray.hit;
	dot1 = dot(closeobj->normal, cam->lokat);
	reflect = normalize(moins(cam->lokat, multi(closeobj->normal, 2 * dot1)));
	ret.dir = reflect;
	return (ret);
}

t_color		reflection(t_rtv1 *rt, t_obj *close)
{
	t_color ret;
	t_obj *closenew;
	t_ray ray;
	t_var v;

	rt->tmpo = rt->obj;
	ray = initmpray(rt->ray, close, rt->cam);
	v.near = -1.0;
	while (rt->tmpo)
	{
		if (rt->tmpo == close)
			rt->tmpo = rt->tmpo->next;
		if (rt->tmpo->ref)
			reflection(rt, rt->tmpo);
		v.t = intersect(rt->tmpo, ray);
		if ((v.t < v.near && v.t > 0) || (v.t > v.near && v.near < 0))
		{
			closenew = rt->tmpo;
			v.near = v.t;
		}
		rt->tmpo = rt->tmpo->next;
	}
	ret = add_color(closenew->color, close->color);
	return (ret);
}

int	color(t_rtv1 *rt, t_obj *close, t_lights *lights)
{
	t_color		c;
	t_color		ret;
	int			shad;

	rt->color = 0;
	rt->ptr = (unsigned char *)&rt->color;
	ret = multi(close->color, 0.1);
	rt->tmpl = lights;
	while (rt->tmpl)
	{
		shad = shadow(rt, rt->tmpl, close);
		if (close->ref == 1)
		{
			// printf("jiji\n");
			c = reflection(rt, close);
		}
		if (shad)
			c = diffuspclr(rt, close, rt->tmpl);
		else
			c = (t_color){0, 0, 0};
			//reflection
		ret = add_color(ret, c);
		rt->tmpl = rt->tmpl->next;
	}
	rt->ptr[2] = ret.x;
	rt->ptr[1] = ret.y;
	rt->ptr[0] = ret.z;
	rt->ptr[3] = 0;
	return (rt->color);
}

// static int	color(t_rtv1 *rt, t_obj *close, t_lights *lights)
// {
// 	t_color		c;
// 	t_color		ret;
// 	int			shad;

// 	rt->color = 0;
// 	rt->ptr = (unsigned char *)&rt->color;
// 	ret = multi(close->color, 0.1);
// 	rt->tmpl = lights;
// 	while (rt->tmpl)
// 	{
// 		shad = shadow(rt, rt->tmpl, close);
// 		if (shad)
// 			c = diffuspclr(rt, close, rt->tmpl);
// 		else
// 			c = (t_color){0, 0, 0};
// 		ret = add_color(ret, c);
// 		rt->tmpl = rt->tmpl->next;
// 	}
// 	rt->ptr[2] = ret.x;
// 	rt->ptr[1] = ret.y;
// 	rt->ptr[0] = ret.z;
// 	rt->ptr[3] = 0;
// 	return (rt->color);
// }

int k = 0;

static void	draw2(t_var v, t_obj *close, t_rtv1 rt, t_obj *tmpo)
{
	while (tmpo)
	{
		v.t = intersect(tmpo, rt.ray);
		if ((v.t < v.near && v.t > 0) || (v.t > v.near && v.near < 0))
		{
			close = tmpo;
			v.near = v.t;
		}
		tmpo = tmpo->next;
	}
	if (k < 3)
	{
		printf ("%d\n", close->ref);
		k++;
	}
	if (v.near > 0 && close)
	{
		setnormal(close, &rt.ray, v.near);
		rt.mlx.dtadd[v.y + v.x * MAXWIDTH] = color(&rt, close, rt.lights);
	}
	else
		rt.mlx.dtadd[v.y + v.x * MAXWIDTH] = 0;
}

void	draw(t_rtv1 rt)
{
	t_obj		*close;
	t_var		v;

	v.y = -1;
	v.near = -1.0;
	while (++v.y < MAXWIDTH)
	{
		v.x = -1;
		while (++v.x < MAXHEIGHT)
		{
			rt.ray = initray(rt.tmpc, v.y, v.x);
			rt.tmpo = rt.obj;
			close = NULL;
			v.near = -1;
			draw2(v, close, rt, rt.tmpo);
		}
	}
}
