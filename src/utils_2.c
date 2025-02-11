/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 23:54:02 by abreuil           #+#    #+#             */
/*   Updated: 2025/02/11 18:21:04 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_tabs(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	init_textures(t_game *game)
{
	put_walls(game);
	put_back(game);
	put_player(game);
	put_collect(game);
	put_exit(game);
}

int	end_game(t_game *game)
{
	mlx_destroy_window(game -> mlx, game -> win);
	mlx_destroy_display(game -> mlx);
	free(game -> mlx);
	free_tabs(game -> map.map);
	exit(0);
}
