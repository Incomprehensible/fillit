/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 03:15:14 by crycherd          #+#    #+#             */
/*   Updated: 2019/04/09 03:22:35 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int item)
{
	if ((item >= 0 && item <= 127))
		return (1);
	return (0);
}
