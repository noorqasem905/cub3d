/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:10:05 by nqasem            #+#    #+#             */
/*   Updated: 2025/07/15 19:24:36 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;

	if (argc != 2)
	{
		handle_error(ERO_USA);
		return (1);
	}
	cub3d = malloc(sizeof(t_cub3d));
	if (!cub3d)
	{
		handle_error(ERO_MALLOC);
		return (1);
	}
	init_cub3d(cub3d, argv[1]);
	if (parsing_manager(&cub3d) == -1)
	{
		handle_error("Error\nParsing failed");
		close(cub3d->fd);
		free(cub3d);
		return (1);
	}
	close(cub3d->fd);
	free(cub3d);
	return (0);
}
