/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:10:05 by nqasem            #+#    #+#             */
/*   Updated: 2025/07/10 16:20:25 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int comma_handle_color(char *line)
{
	char	*tmp;
    int		comma_count;

	comma_count = 0;
    tmp = line;
	while (ft_strchr(tmp, ','))
	{
		tmp = ft_strchr(tmp, ',');
		if (!tmp)
			break ;
		if (*(tmp + 1) == ',' || *(tmp + 1) == '\0')
			return (-1);
		comma_count++;
		tmp++;
	}
	if (comma_count != 2)
		return (-1);
	return (0);
}

int	find_std_color_formial(char *line, int *lock, int *index)
{
	int	i;

	i = *index;
	if (ft_isdigit(line[i]) && (*lock) == 0)
    {
        (*lock) = 1;
        while (ft_isdigit(line[i]))
            *index = ++i;
		return (1);
    }
    else if (line[i] == ',')
    {
        if ((*lock) == 0)
            return (-1);
        (*lock) = 0;
	}
	else if (ft_isdigit(line[i]) && (*lock) == 1)
		return (-1);
    else if (!ft_isspace(line[i]) && !ft_isdigit(line[i]) && line[i] != ',')
		return (-1);
	return (0);
}

int handle_color_formality(char *line)
{
    int		i;
	int		ret;
    int		lock;

    i = 0;
    ret = 0;
    lock = 0;
	if (comma_handle_color(line) == -1)
		return (-1);
    while (line[i])
    {
		if ((line[i] == '+' || line[i] == '-') && ft_isdigit(line[i + 1]))
			;
		else if (ft_isdigit(line[i]) || ft_isspace(line[i]) || line[i] == ',')
        {
			ret = find_std_color_formial(line, &lock, &i);
			if (ret == -1)
				return (-1);
			if (ret == 1)
			 continue ;
        }
		else
			return (-1);
        i++;
    }
    return (0);
}

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

int	handle_color_data(char *line, int skip)
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
    if (handle_color_formality(trimmed_line) == -1)
    {        
		handle_error(ERO_MAP);
		return (-1);
    }
	if (check_values(trimmed_line, skip) == -1)
	{
		handle_error(ERO_MAP);
		return (-1);
	}
	return (0);
}

void check_data_error(t_cub3d **cub3d, char *message, int flag)
{

	(*cub3d)->flag = flag;
	if (message)
		handle_error(message);
}

int	check_data_condition_2(char *trimmed_line, t_cub3d **cub3d, int *is_complete, int *height)
{
	if (ft_strncmp(trimmed_line, "F ", 2) == 0 || ft_strncmp(trimmed_line,
			"C ", 2) == 0)
	{
		(*is_complete)++;
		if(handle_color_data(trimmed_line, 2) == -1)
			return (-1);
	}
	else if ((ft_strncmp(trimmed_line, "1", 1) == 0 || ft_strncmp(trimmed_line,
				"0", 1) == 0 || ft_strncmp(trimmed_line, " ", 1) == 0))
	{
		(*height)++;
		if ((*is_complete) < 6 && (ft_strncmp(trimmed_line, "1", 1) == 0
				|| ft_strncmp(trimmed_line, "0", 1) == 0
				|| ft_strncmp(trimmed_line, " ", 1) == 0))
		{
			check_data_error(cub3d, ERO_MAP, 6);
			return (-1);
		}
	}
	else
	{
		check_data_error(cub3d, ERO_MAP, 6);
		return (-1);
	}
	return (0);
}
int	check_data_condition(char *trimmed_line, t_cub3d **cub3d, int *is_complete)
{
	int height;
	
	height = 0;
	if (ft_strncmp(trimmed_line, "NO ", 3) == 0 || ft_strncmp(trimmed_line,
			"SO ", 3) == 0 || ft_strncmp(trimmed_line, "WE ", 3) == 0
		|| ft_strncmp(trimmed_line, "EA ", 3) == 0)
	{
		(*is_complete)++;
		if (is_acceptable_file(trimmed_line, 3))
			return (-1);
	}
 	else
		if (check_data_condition_2(trimmed_line, cub3d, is_complete, &height) == -1)
			return (-1);
	if ((*cub3d)->map.map_height == -1 && height > 0)
		(*cub3d)->map.map_height = 0;
	(*cub3d)->map.map_height += height;
	return (0);
}

int	setup_check_data(char *line, t_cub3d **cub3d, int *is_complete)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \t\n\r");
	printf("Trimmed line: '%s'\n", trimmed_line);
	if (!trimmed_line)
	{
		handle_error(ERO_MALLOC);
		return (-1);
	}
	if (trimmed_line[0] == '\0')
	{
		free(trimmed_line);
		check_data_error(cub3d, NULL, 6);
		return (0);
	}
	if (check_data_condition(trimmed_line, cub3d, is_complete) == -1)
	{
		free(trimmed_line);
		return (-1);
	}
	free(trimmed_line);
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
	(*cub3d)->point = (t_point **)malloc(sizeof(t_point *) * ((*cub3d)->map.map_height));
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
	int i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			(*check_empty) = 0;
		if (line[i] != '1' && line[i] != '0' && !ft_isspace(line[i]) && line[i] != 'N')
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

void free_map_points(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	if (!cub3d->point || !cub3d)
		return ;
	while (i < cub3d->map.map_height)
	{
		free(cub3d->point[i]);
		i++;
	}
	free(cub3d->point);
}

int		check_map_condtion(t_cub3d **cub3d, char *map_line, int *lock, int *y)
{
	if ((*lock))
	{
		if(check_map_values(cub3d, map_line, (*y)) == -1)
		{
			(*cub3d)->map.map_height = (*y);
			handle_get_next_line((*cub3d)->fd, map_line);
			return (-1);
		}
		if ((*cub3d)->is_empty == 0)
		{
			(*cub3d)->player.map_y = (*y);
			(*y)++;
		}
	}
	else if (ft_strncmp(map_line, "1", 1) == 0 || ft_strncmp(map_line, "0", 1) == 0
		|| ft_strncmp(map_line, " ", 1) == 0)
	{
		(*lock) = 1;
		return (1);
	}
	else
		return (3);
	return (0);
}

int		check_map_searching(t_cub3d **cub3d, char *map_line, int *lock, int *y)
{
	int i;

	i = 0;
	(*cub3d)->is_empty = 0;
	while (map_line)
	{
		int ret = check_map_condtion(cub3d, map_line, lock, y);
		if (ret == -1)
			return (-1);
		else if (ret == 1)
			continue ;
		if(ret == 3 && (*lock) == 1)
		{
			(*cub3d)->map.map_height = (*y);
			handle_get_next_line((*cub3d)->fd, map_line);
			return (-1);
		}
		i++;
		free(map_line);
		map_line = get_next_line((*cub3d)->fd);
	}
	return (0);
}

int		check_map(t_cub3d **cub3d)
{
	char	*map_line;
	int		lock;
	int		y;

	lock = 0;
	y = 0;
	close((*cub3d)->fd);
	(*cub3d)->fd = -1;
 	if (setup_check_map(cub3d, &map_line) == -1)
		return (-1);
 	if (check_map_searching(cub3d, map_line, &lock, &y) < 0)
		return (-1);
	if ((*cub3d)->player.map_x == -1 || (*cub3d)->player.map_y == -1)
	{
		(*cub3d)->map.map_height = y;
		handle_error(ERO_MAP);
		return (-1);
	}
	(*cub3d)->map.map_height = y;
	return (0);
}

void	frees_struct(t_point **root)
{
	int	i;

	i = 0;
	if (!*root | !root)
		return ;
	while (root[i])
	{
		free(root[i]);
		i++;
	}
	free(root);
	root = NULL;
}

 void print_data(t_cub3d *cub3d)
{
	int	i;
	int	j;

	printf("Map Width: %d\n", cub3d->map.map_width);
	printf("Map Height: %d\n", cub3d->map.map_height);
	printf("Player Position: (%d, %d)\n", cub3d->player.map_x, cub3d->player.map_y);
	for (i = 0; i < cub3d->map.map_height; i++)
	{
		for (j = 0; j < cub3d->map.map_width; j++)
		{
			printf("access-> %d:", cub3d->point[i][j].access);
			printf("(%d, %d):\n", cub3d->point[i][j].x, cub3d->point[i][j].y);
		}
	}
}

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
/* 	if (handle_read_file(cub3d, &is_complete) == -1)
		return (-1); */
 	line = get_next_line((*cub3d)->fd);
	if (!line)
	{
		check_data_error(cub3d, ERO_READ, 3);
		return (-1);
	}
	while (line)
	{
		if (setup_check_data(line, cub3d, &is_complete) == -1)
		{
			handle_get_next_line((*cub3d)->fd, line);
			return (-1);
		}
		i++;
		free(line);
		line = get_next_line((*cub3d)->fd);
	} 
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

int	main(int argc, char **argv)
{
	t_cub3d *cub3d;
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
		handle_error("Error: Parsing failed");
		close(cub3d->fd);
		free(cub3d);
		return (1);
	}
	// print_data(cub3d);
	close(cub3d->fd);
	free(cub3d);
	return (0);
}
