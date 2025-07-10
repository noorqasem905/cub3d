/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:00:04 by nqasem            #+#    #+#             */
/*   Updated: 2025/07/10 16:08:48 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

void	init_cub3d(t_cub3d *cub3d, char *arg)
{
	cub3d->fd = -1;
	cub3d->flag = 0;
	cub3d->is_empty = -1;
	cub3d->map.map_height = -1;
	cub3d->map.map_width = -1;
	cub3d->map.file_path = NULL;
	cub3d->map.data = NULL;
	cub3d->map.texture_north = NULL;
	cub3d->map.texture_south = NULL;
	cub3d->map.texture_west = NULL;
	cub3d->map.texture_east = NULL;
	cub3d->map.texture_sprite = NULL;
/* 	cub3d->width = 0;
	cub3d->height = 0;
	cub3d->map_width = 0; */
	cub3d->file_path = arg;
/* 	cub3d->map_height = 0;
	cub3d->map = NULL; */
	cub3d->player.map_x = -1;
	cub3d->player.map_y = -1;
}

void	check_name(t_cub3d *cub3d)
{
	char	*arg;
	int	i;

	i = 0;
	arg = cub3d->file_path;
	if (access(arg, F_OK | R_OK) == -1)
	{
		cub3d->flag = 15;
		handle_error(ERO_FILE);
		return ;
	}
	while (arg[i])
		i++;
	if (arg[i - 1] != 'b' || arg[i - 2] != 'u' || arg[i - 3] != 'c' || arg[i
		- 4] != '.')
	{
		cub3d->flag = 1;
		handle_error(ERO_NAME_FILE);
		return ;
	}
}

int	check_access(char *line)
{
	if (access(line, F_OK | R_OK | X_OK) == -1)
	{
		handle_error(ERO_FILE);
		return (-1);
	}
	return (0);
}

int	is_acceptable_file(char *line, int skip)
{
	char	*trimmed_line;
	int		i;

	i = skip;
	while (ft_isspace(line[i]))
		i++;
	trimmed_line = ft_strchr(line + skip, line[i]);
	if (!trimmed_line)
	{
		handle_error(ERO_MAP);
		return (-1);
	}
	if (check_access(trimmed_line) == -1)
		return (-1);
	return (0);
}
