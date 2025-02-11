/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:09:06 by abreuil           #+#    #+#             */
/*   Updated: 2025/02/11 18:37:12 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// this function counts the map lines
int	map_lines(t_parse *parse)
{
	int		num_lines;
	char	*line;

	num_lines = 0;
	line = get_next_line(parse->fd);
	while (line)
	{
		free(line);
		line = get_next_line(parse->fd);
		num_lines++;
	}
	free(line);
	parse -> lines = num_lines;
	close(parse -> fd);
	return (num_lines);
}

// this functions counts the map collectables
int	map_coins(t_parse *parse, t_game *game)
{
	int	i;
	int	j;
	int	coins;

	i = 0;
	coins = 0;
	while (parse->map[i])
	{
		j = 0;
		while (parse->map[i][j])
		{
			if (parse->map[i][j] == 'C')
				coins++;
			j++;
		}
		i++;
	}
	game->collect = coins;
	return (coins);
}

void	init(t_game *game, t_parse *parse)
{
	// Set the width of the map in the parse structure
	parse -> width = map_width(parse);
	// Calculate the game map width in pixels
	game -> map.width = (parse -> width - 1) * 64;
	// Check if the map width exceeds the maximum allowed width (1920 pixels)
	if (game -> map.width > 1920)
		return (write(2, "Error, map width too big\n", 25), exit(1));
	// Calculate the game map height in pixels
	game -> map.height = (parse -> lines * 64);
	// Check if the map height exceeds the maximum allowed height (1080 pixels)
	if (game -> map.height > 1080)
		return (write(1, "Error, map height too big\n", 26),
			free_tabs(parse->map), exit(1));
	// Initialize the number of collectible items in the game
	game->collect = map_coins(parse, game);
	// Set the exit position from the parsed data
	game -> exit = parse -> exit;
	// Initialize player position and state
	game -> player.x = parse -> player_x;
	game -> player.y = parse -> player_y;
	game -> player.moves = 0;
	game -> player.collect = 0;
	game -> player.exit = 0;
	game -> map.map = parse -> map;
}

int	map_width(t_parse *parse)
{
	int		i;
	int		len;
	int		max_len;

	i = 0;
	max_len = 0;
	while (parse -> map[i])
	{
		len = ft_strlen(parse -> map[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	parse -> width = max_len;
	return (max_len);
}

void	init_window(t_game *game)
{
	game -> mlx = mlx_init();
	if (!game -> mlx)
	{
		free (game -> mlx);
		free_tabs(game -> map.map);
		exit(1);
	}
	game -> win = mlx_new_window(game -> mlx, game -> map.width,
			game -> map.height, "so_long");
	if (!game -> win)
	{
		free(game -> mlx);
		free_tabs(game -> map.map);
		exit(1);
	}
}
