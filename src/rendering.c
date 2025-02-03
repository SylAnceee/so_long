/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 23:53:58 by abreuil           #+#    #+#             */
/*   Updated: 2025/02/03 15:38:14 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	put_walls(t_game *game)
{
	t_texture	wall;
	int			i;
	int			j;

	wall.path = "./assets2/wall.xpm";
	wall.img = mlx_xpm_file_to_image(game->mlx, wall.path, &wall.width,
			&wall.height);
	if (!wall.img)
		end_game(game);
	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j] != '\n')
		{
			if (game->map.map[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game->win, wall.img, j * 64,
					i * 64);
			j++;
		}
		i++;
	}
	mlx_destroy_image(game->mlx, wall.img);
}

void	put_exit(t_game *game)
{
	t_texture	exit;
	int			i;
	int			j;

	exit.path = "./assets2/exit.xpm";
	exit.img = mlx_xpm_file_to_image(game->mlx, exit.path, &exit.width,
			&exit.height);
	if (!exit.img)
		end_game(game);
	i = 0;
	while (i < game->map.height / 64)
	{
		j = 0;
		while (j < game->map.width / 64)
		{
			if (game->map.map[i][j] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, exit.img, j * 64,
					i * 64);
			j++;
		}
		i++;
	}
	mlx_destroy_image(game->mlx, exit.img);
}

void	put_collect(t_game *game)
{
	t_texture	collect;
	int			i;
	int			j;

	collect.path = "./assets2/collectable.xpm";
	collect.img = mlx_xpm_file_to_image(game->mlx, collect.path, &collect.width,
			&collect.height);
	if (!collect.img)
		end_game(game);
	i = 0;
	while (i < game->map.height / 64)
	{
		j = 0;
		while (j < game->map.width / 64)
		{
			if (game->map.map[i][j] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, collect.img, j
					* 64, i * 64);
			j++;
		}
		i++;
	}
	mlx_destroy_image(game->mlx, collect.img);
}

void	put_back(t_game *game)
{
	t_texture	back;
	int			i;
	int			j;

	back.path = "./assets2/back.xpm";
	back.img = mlx_xpm_file_to_image(game->mlx, back.path, &back.width,
			&back.height);
	if (!back.img)
		end_game(game);
	i = 0;
	while (i < game->map.height / 64)
	{
		j = 0;
		while (j < game->map.width / 64)
		{
			if (game->map.map[i][j] == '0' || game->map.map[i][j] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, back.img, j * 64,
					i * 64);
			j++;
		}
		i++;
	}
	mlx_destroy_image(game->mlx, back.img);
}

void	put_player(t_game *game)
{
	t_texture	player;

	player.path = "./assets2/player/player.xpm";
	player.img = mlx_xpm_file_to_image(game->mlx, player.path, &player.width,
			&player.height);
	if (!player.img)
		end_game(game);
	mlx_put_image_to_window(game->mlx, game->win, player.img, game->player.y
		* 64, game->player.x * 64);
	mlx_destroy_image(game->mlx, player.img);
}
