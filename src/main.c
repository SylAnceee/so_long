/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:36:29 by abreuil           #+#    #+#             */
/*   Updated: 2025/02/11 18:20:59 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
/* 
 * check_exist: Checks if the file exists and stores information
 * in the parse struct.
 * check_suffix: Ensures the file has the correct ".ber" extension.
 * valid_file: Validates program arguments and the file's existence/suffix.
 * parse_map: Verifies the map's format, edges, content, elements,
 * and pathfinding.
 * main: Entry point of the program, initializes and runs the game loop.
 */

int	check_exist(char *str, t_parse *parse)
{
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (0);
	parse -> fd = fd;
	parse -> file = str;
	return (1);
}

int	check_suffix(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] != 'r' || str[i - 2] != 'e' || str[i - 3] != 'b'
		|| str[i - 4] != '.')
		return (0);
	return (1);
}

int	valid_file(int ac, char **av, t_parse *parse)
{
	if (ac != 2)
		return (1);
	if (!check_suffix(av[1]))
		return (0);
	if (!check_exist(av[1], parse))
		return (0);
	return (1);
}

int	parse_map(t_parse *parse)
{
	if (!check_map_rectangle(parse))
		return (write(1, "1", 1), free_tabs(parse->map), 0);
	if (!check_map_edges(parse))
		return (write(1, "2", 1), free_tabs(parse->map), 0);
	if (!check_map_content(parse))
		return (write(1, "3", 1), free_tabs(parse->map), 0);
	if (!check_map_elements(parse))
		return (write(1, "4", 1), free_tabs(parse->map), 0);
	parse->game.map.visited = dup_map(*parse);
	if (!parse->game.map.visited)
		return (free_tabs(parse->map), 0);
	player_pos(parse);
	if (!pathfinding(parse, parse->player_x, parse->player_y))
		return (free_tabs(parse->game.map.visited),
			free_tabs(parse->map), 0);
	return (1);
}

int	main(int ac, char **av)
{
	t_parse	parse;
	t_game	game;

	if (!valid_file(ac, av, &parse))
		return (write(2, "Error, file not found\n", 23), 0);
	if (!check_map(&parse))
		return (write(2, "Error, map did not load correctly", 27), 0);
	parse.game.exit_reachable = 0;
	if (!parse.map || !parse_map(&parse))
		return (write(2, "Error, map not valid\n", 22), 0);
	init(&game, &parse);
	init_window(&game);
	mlx_hook(game.win, DestroyNotify, 0, end_game, &game);
	init_textures(&game);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_loop(game.mlx);
}
