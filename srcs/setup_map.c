/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:06:30 by nqasem            #+#    #+#             */
/*   Updated: 2025/07/10 18:19:57 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_values(char *line, int skip)
{
	int		i;
	int		value;
	char	*tmp;

	i = skip;
	while (ft_isspace(line[i]))
		i++;
	tmp = ft_strchr(line + skip, line[i]);
	if (!tmp)
		return (-1);
	while (ft_isdigit(tmp[i]) || tmp[i] == '+' || tmp[i] == '-')
	{
		value = ft_atoi(tmp + i);
		if (value < 0 || value > 255)
			return (-1);
		while (ft_isdigit(tmp[i]) || tmp[i] == '+' || tmp[i] == '-')
			i++;
		if (tmp[i] == ',')
			i++;
		else if (tmp[i] != '\0')
			return (-1);
	}
	return (0);
}

int	setup_check_map(t_cub3d **cub3d, char **map_line)
{
	if (open_file(cub3d) == -1)
	{
		handle_error(ERO_OPEN_FILE);
		return (-1);
	}
	(*map_line) = get_next_line((*cub3d)->fd);
	if (!(*map_line))
		return (-1);
	(*cub3d)->point = (t_point **)malloc(sizeof(t_point *)
			* ((*cub3d)->map.map_height));
	if (!(*cub3d)->point)
	{
		handle_get_next_line((*cub3d)->fd, *map_line);
		(*cub3d)->map.map_height = -1;
		handle_error(ERO_MALLOC);
		return (-1);
	}
	return (0);
}

void	set_map_values(t_cub3d **cub3d, char *line, int y)
{
	int	x;
	int	size;

	x = 0;
	size = ft_strlen(line);
	while (line[x])
	{
		if (line[x] == 'N')
			(*cub3d)->point[y][x].access = 2;
		else
			(*cub3d)->point[y][x].access = line[x] - '0';
		(*cub3d)->point[y][x].x = x;
		(*cub3d)->point[y][x].y = y;
		(*cub3d)->point[y][x].width = size;
		x++;
	}
}

int	check_map_values_condtion(t_cub3d **cub3d, char *line, int *check_empty)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			(*check_empty) = 0;
		if (line[i] != '1' && line[i] != '0'
			&& !ft_isspace(line[i]) && line[i] != 'N')
			return (-1);
		else if (line[i] == 'N' && (*cub3d)->player.map_x == -1)
			(*cub3d)->player.map_x = i;
		else if (line[i] == 'N' && (*cub3d)->player.map_y != -1)
			return (-1);
		i++;
	}
	return (0);
}

int	check_map_values(t_cub3d **cub3d, char *line, int y)
{
	int	size;
	int	check_empty;

	check_empty = 1;
	size = ft_strlen(line);
	if (check_map_values_condtion(cub3d, line, &check_empty) == -1)
		return (-1);
	if (!check_empty && (*cub3d)->is_empty == 1)
		return (-1);
	if (check_empty)
		(*cub3d)->is_empty = 1;
	if (check_empty == 0)
	{
		(*cub3d)->map.map_width = size;
		(*cub3d)->point[y] = (t_point *)malloc((sizeof(t_point)) * (size));
		if (!(*cub3d)->point[y])
		{
			handle_error(ERO_MALLOC);
			return (-1);
		}
		set_map_values(cub3d, line, y);
	}
	return (0);
}
