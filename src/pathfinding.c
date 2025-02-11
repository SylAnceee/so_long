/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 00:08:12 by abreuil           #+#    #+#             */
/*   Updated: 2025/02/11 18:29:50 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// finds the i and y of the player
void	player_pos(t_parse *parse)
{
	int	i;
	int	j;

	i = 0;
	while (parse->map[i])
	{
		j = 0;
		while (parse->map[i][j])
		{
			if (parse->map[i][j] == 'P')
			{
				parse->player_x = i;
				parse->player_y = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

// duplicate the map
char	**dup_map(t_parse parse)
{
	char	**map;
	int		i;

	i = 0;
	map = malloc(sizeof(char *) * (parse.lines + 1));
	if (!map)
		return (NULL);
	while (i < parse.lines)
	{
		map[i] = ft_strdup(parse.map[i]);
		if (!map[i])
		{
			while (i > 0)
			{
				free(map[--i]);
			}
			free(map);
			return (NULL);
		}
		i++;
	}
	map[i] = NULL;
	return (map);
}
// this is a recursive function that will navigate through our map.
// it will check if we are on a valid postion
// if we collected everything
// if exit is reachable
int	pathfinding(t_parse *parse, int i, int j)
{
	if (i < 0 || j < 0 || i >= parse->lines
		|| j >= ft_strlen(parse->game.map.visited[0]))
		return (0);
	if (parse->game.exit_reachable == 1 && parse->game.collect == 0)
		return (free_tabs(parse->game.map.visited), 1);
	if (parse->game.map.visited[i][j] == 'E')
		parse->game.exit_reachable = 1;
	if (parse->game.map.visited[i][j] == '1'
		|| parse->game.map.visited[i][j] == 'X'
		|| (parse->game.map.visited[i][j] == 'E' && parse->exit > 0))
		return (0);
	if (parse->game.map.visited[i][j] == 'C')
		parse->game.collect--;
	parse->game.map.visited[i][j] = 'X';
	if (pathfinding(parse, i - 1, j))
		return (1);
	if (pathfinding(parse, i + 1, j))
		return (1);
	if (pathfinding(parse, i, j - 1))
		return (1);
	if (pathfinding(parse, i, j + 1))
		return (1);
	return (0);
}
