/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:49:09 by nqasem            #+#    #+#             */
/*   Updated: 2025/07/10 18:25:00 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_read_file(t_cub3d **cub3d, int *is_complete)
{
	char	*line;
	int		i;

	i = 1;
	line = get_next_line((*cub3d)->fd);
	if (!line)
	{
		check_data_error(cub3d, ERO_READ, 3);
		return (-1);
	}
	while (line)
	{
		if (setup_check_data(line, cub3d, is_complete) == -1)
		{
			handle_get_next_line((*cub3d)->fd, line);
			return (-1);
		}
		i++;
		free(line);
		line = get_next_line((*cub3d)->fd);
	}
	return (0);
}

int	read_file(t_cub3d **cub3d)
{
	int		i;
	int		is_complete;
	char	*line;

	i = 1;
	is_complete = 0;
	if (handle_read_file(cub3d, &is_complete) == -1)
		return (-1);
	if (is_complete != 6 || (*cub3d)->map.map_height == -1)
	{
		check_data_error(cub3d, ERO_MAP, 6);
		return (-1);
	}
	if (check_map(cub3d) == -1)
	{
		free_map_points(*cub3d);
		handle_error(ERO_MAP);
		return (-1);
	}
	free_map_points(*cub3d);
	printf("Parsing completed successfully.\n");
	return (0);
}

int	parsing_manager(t_cub3d **cub3d)
{
	if (open_file(cub3d) == -1)
		return (-1);
	if (read_file(cub3d) == -1)
		return (-1);
	return (0);
}
