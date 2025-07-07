/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:24:46 by nqasem            #+#    #+#             */
/*   Updated: 2025/07/07 18:09:06 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	handle_error(char *_error)
{
	ft_putendl_fd(_error, 2);
}

int	handle_get_next_line(int fd, char *line, int flag)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (flag);
}

/* void	print_map(t_data *fdf)
{
	int	y;
	int	x;

	for (y = 0; y < fdf->height; y++)
	{
		for (x = 0; x < fdf->width; x++)
		{
			printf("%f ", fdf->map[y][x].z);
			if (fdf->map[y][x].z <= 0 && fdf->map[y][x + 1].z <= 0)
				printf(" ");
			if (fdf->map[y][x].z > 0 && fdf->map[y][x + 1].z <= 0)
				printf(" ");
		}
		printf("\n");
	}
} */