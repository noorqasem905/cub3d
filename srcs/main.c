/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:10:05 by nqasem            #+#    #+#             */
/*   Updated: 2025/07/08 09:44:21 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_name(char *arg, t_cub3d *cub3d)
{
	int	i;

	i = 0;
	if (access(arg, F_OK | R_OK) == -1)
	{
		cub3d->flag = 15;
		handle_error(ERO_FILE);
		return ;
	}
	while (arg[i])
		i++;
	if (arg[i - 1] != 'b' || arg[i - 2] != 'u' || arg[i - 3] != 'c'
		|| arg[i - 4] != '.')
	{
		cub3d->flag = 1;
		handle_error(ERO_NAME_FILE);
		return ;
	}
}

int open_file(t_cub3d **cub3d, char *arg)
{
    (*cub3d)->fd = open(arg, O_RDONLY);
    if ((*cub3d)->fd < 0)
    {
        (*cub3d)->flag = 2;
        handle_error(ERO_OPEN_FILE);
        return (-1);
    }
    check_name(arg, (*cub3d));
    if ((*cub3d)->flag != 0)
        return (-1);
    return (0);
}


int read_file_handle(t_cub3d **cub3d, char *line)
{
    int ret;

    handle_get_next_line((*cub3d)->fd, line);
    if (ret == -1)
    {
        (*cub3d)->flag = 4;
        handle_error(ERO_READ);
        return (-1);
    }
    if (ret == 0)
    {
        (*cub3d)->flag = 5;
        handle_error(ERO_MAP);
        return (-1);
    }
    return (0);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int check_access(char *line)
{
    int fd;

    if (access(line, F_OK | R_OK | X_OK) == -1)
    {
        handle_error(ERO_FILE);
        return (-1);
    }
    return (0);
}

int is_acceptable_file(char *line, int skip)
{
    char *trimmed_line;
    int i;

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
// test ./test.cub or .///////test ../cub 

int check_map(){}


int check_data(char *line, t_cub3d **cub3d, int *is_complete)
{
    char *trimmed_line;

    trimmed_line = ft_strtrim(line, " \t\n\r");
    if (trimmed_line[0] == '\0')
    {
        free(trimmed_line);
        return (0);
    }
    printf("Trimmed Line: %s:\n", trimmed_line);
    if (ft_strncmp(trimmed_line, "NO ", 3) == 0 || ft_strncmp(trimmed_line, "SO ", 3) == 0 ||
             ft_strncmp(trimmed_line, "WE ", 3) == 0 || ft_strncmp(trimmed_line, "EA ", 3) == 0)
    {
        (*is_complete) ++;
        if (is_acceptable_file(trimmed_line, 3))
        {
            free(trimmed_line);
            return (-1);
        }
    }
    else if (ft_strncmp(trimmed_line, "F ", 2) == 0 || ft_strncmp(trimmed_line, "C ", 2) == 0)
    {
        (*is_complete) ++;
        // handle_color_data(trimmed_line);
    }
    else if ( 
             (ft_strncmp(trimmed_line, "1", 1) == 0 || ft_strncmp(trimmed_line, "0", 1) == 0 ||
              ft_strncmp(trimmed_line, " ", 1) == 0))
    {
        if ((*is_complete) < 6 && (ft_strncmp(trimmed_line, "1", 1) == 0 || ft_strncmp(trimmed_line, "0", 1) == 0 ||
            ft_strncmp(trimmed_line, " ", 1) == 0))
        {
            (*cub3d)->flag = 6;
            handle_error(ERO_MAP);
            free(trimmed_line);
            return (-1);
        }
        else
        {
            
        }
    }
    else
    {
        printf("Invalid data: %s\n", trimmed_line);
        (*cub3d)->flag = 6;
        handle_error(ERO_MAP);
        free(trimmed_line);
        return (-1);
    }
    free(trimmed_line);
    return (0);
}

int read_file(t_cub3d **cub3d)
{
    int is_complete = 0;
    char *line;

    line = get_next_line((*cub3d)->fd);
    if (!line)
    {        (*cub3d)->flag = 3;
        handle_error(ERO_READ);
        return (-1);
    }
    while (line)
    {
        if (check_data(line, cub3d, &is_complete) == -1)
        {
            handle_get_next_line((*cub3d)->fd, line);
            return (-1);
        }
        // printf("Line: %s", line);
        free(line);
        line = get_next_line((*cub3d)->fd);
    }
    if (is_complete != 6)
    {
        (*cub3d)->flag = 6;
        handle_error(ERO_MAP);
        return (-1);
    }
    free(line);
    return (0);
}

int parsing_manager(t_cub3d **cub3d, char *arg)
{
    if (open_file(cub3d, arg) == -1)
        return (-1);
    if (read_file(cub3d) == -1)
        return (-1);
    return (0);
}

void    init_cub3d(t_cub3d *cub3d)
{
    cub3d->fd = -1;
    cub3d->flag = 0;
    cub3d->width = 0;
    cub3d->height = 0;
    cub3d->map_width = 0;
    cub3d->map_height = 0;
    cub3d->map = NULL;
}

int main(int argc, char **argv)
{
    t_cub3d *cub3d;
    if (argc != 2)
    {
        handle_error(ERO_USA);
        return (1);
    }
    cub3d = malloc(sizeof(t_cub3d));
    if (!cub3d)
    {        handle_error(ERO_MALLOC);
        return (1);
    }
    init_cub3d(cub3d);
    if (parsing_manager(&cub3d, argv[1]) == -1)
    {
        handle_error("Error: Parsing failed");
        close(cub3d->fd);
        free(cub3d);
        return (1);
    }
    close(cub3d->fd);
    free(cub3d);
/*
    // Initialize the game and start the main loop
    if (init_game(&fdf) == -1)
    {
        handle_error("Error: Game initialization failed");
        return (1);
    }

    mlx_loop(fdf.mlx_ptr); */
    
    return (0);
}