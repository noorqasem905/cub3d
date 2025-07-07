/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nqasem <nqasem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:10:05 by nqasem            #+#    #+#             */
/*   Updated: 2025/07/07 18:22:45 by nqasem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        handle_error("Error: Invalid number of arguments");
        return (1);
    }

/*  if (parsing(&fdf, argv[1]) == -1)
    {
        handle_error("Error: Parsing failed");
        return (1);
    }

    // Initialize the game and start the main loop
    if (init_game(&fdf) == -1)
    {
        handle_error("Error: Game initialization failed");
        return (1);
    }

    mlx_loop(fdf.mlx_ptr); */
    
    return (0);
}