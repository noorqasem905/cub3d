/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:24:46 by nqasem            #+#    #+#             */
/*   Updated: 2025/07/08 09:14:38 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	handle_error(char *_error)
{
	ft_putendl_fd(_error, 2);
}

void	handle_get_next_line(int fd, char *line)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

