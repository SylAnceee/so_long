/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abreuil <abreuil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 23:59:11 by abreuil           #+#    #+#             */
/*   Updated: 2025/02/11 18:21:37 by abreuil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
/* This function checks if the player can move to the specified coordinates.
 * It verifies if the target position is not a wall ('1'), if it is an exit ('E')
 * and all collectibles have been collected, it ends the game. If the target
 * position is a collectible ('C'), it decrements the collectible count and 
 * updates the map.
*/

int	check_move(t_game *game, int x, int y)
{
	if (game -> map.map[x][y] == '1')
		return (0);
	if (game -> map.map[x][y] == 'E')
	{
		if (game -> collect == 0)
			end_game(game);
		return (0);
	}
	if (game -> map.map[x][y] == 'C')
	{
		game -> collect--;
		game -> map.map[x][y] = '0';
		put_back(game);
	}
	return (1);
}

/**
 * This function calculates the number of moves the player does
 */
void	move_player(t_game *game, int x, int y)
{
	if (check_move(game, x, y))
	{
		put_back(game);
		game -> player.x = x;
		game -> player.y = y;
		game -> player.moves++;
		write (1, "moves: ", 7);
		ft_putnbr_fd(game -> player.moves, 1);
		write (1, "\n", 1);
		put_player(game);
	}
}

/**
 * This function handles key press events. It moves the player based on the
 * key pressed (WASD for movement, ESC to end the game).
 */
int	key_hook(int keycode, t_game *game)
{
	if (keycode == 119)
		move_player(game, game->player.x - 1, game->player.y);
	if (keycode == 97)
		move_player(game, game->player.x, game->player.y - 1);
	if (keycode == 115)
		move_player(game, game->player.x + 1, game->player.y);
	if (keycode == 100)
		move_player(game, game->player.x, game->player.y + 1);
	if (keycode == 65307)
		end_game(game);
	return (0);
}
