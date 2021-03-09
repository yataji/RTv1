/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yataji <yataji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:44:50 by yataji            #+#    #+#             */
/*   Updated: 2021/03/09 01:51:35 by yataji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double checkt(t_math calc)
{
    double t1;
    double t2;

    if (calc.delta < 0)
        return (-1);
    else if (calc.delta == 0)
        return (-calc.b / (2 * calc.a));
    t1 = (-calc.b - sqrtf(calc.delta)) / (2 * calc.a);
    t2 = (-calc.b + sqrtf(calc.delta)) / (2 * calc.a);
    if (t1 < t2 && t1 >= 0)
        return (t1);
    else if (t2 >= 0)
        return (t2);
    return (-1);
}

double intersect(t_obj *object, t_ray ray)
{
    if (object->type == SPHERE)
    {
        return (sphrintr(object, ray));
    }
    if (object->type == CYLINDER)
    {
        return (cyldintr(object, ray));
    }
    if (object->type == CONE)
    {
        return (coneintr(object, ray));
    }
    return (-1);
}

t_vect normalize(t_vect v1)
{
    double v;

    v = sqrtf(dot(v1, v1));
    return (multi(v1, 1.0 / v));
}

void    setnormal(t_obj *close, t_ray *ray, double t)
{
    if (close->type == SPHERE)
        close->normal = normsphr(ray, close, t);
    else if (close->type == CYLINDER)
        close->normal = normcyld(ray, close, t);
    else if (close->type == CONE)
        close->normal = normcone(ray, close, t);
}