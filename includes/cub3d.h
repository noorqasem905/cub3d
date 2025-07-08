/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:51:38 by nqasem            #+#    #+#             */
/*   Updated: 2025/07/08 17:46:56 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../libft/printf/ft_printf.h"

# define ERO_USA        "Error: usage: ./cub3d <file.cub>"
# define ERO_NAME_FILE  "Error: unsupported file"
# define ERO_OPEN_FILE  "Error: failed to open file"
# define ERO_MAP        "Error: map is invalid"
# define ERO_MALLOC     "Error: malloc failed"
# define ERO_FILE       "The file is not accessible or doesn't exist"
# define ERO_READ       "Error: read failed"
# define ERO_CLOSE      "Error: close failed"
# define ERO_MLX        "Error: mlx failed"
# define ERO_MLX_WIN    "Error: mlx_new_window failed"
# define ERO_MLX_IMG    "Error: mlx_new_image failed"
# define ERO_MLX_ADDR   "Error: mlx_get_data_addr failed"
# define ERO_MLX_INIT   "Error: mlx_init failed"

typedef struct s_cub3d	t_cub3d;
typedef struct s_player	t_player;
struct s_player
{
	int map_x;
	int map_y;
};
struct s_cub3d
{
    int     	fd;
    int     	flag;
    int     	width;
    int     	height;
    int     	map_width;
    int     	map_height;
    char    	*file_path;
    char    	**map;
	t_player	player;
};


int		ft_isspace(char c);
int		check_access(char *line);
int		open_file(t_cub3d **cub3d);
int		is_acceptable_file(char *line, int skip);
int     parsing_manager(t_cub3d **cub3d);
int		open_file_manager(t_cub3d **cub3d);
int		read_file_handle(t_cub3d **cub3d, char *line);
void	handle_get_next_line(int fd, char *line);
void	check_name(t_cub3d *cub3d);
void	init_cub3d(t_cub3d *cub3d, char *arg);
void    handle_error(char *_error);

#endif