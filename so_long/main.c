/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:21:23 by abenba            #+#    #+#             */
/*   Updated: 2025/01/20 18:21:24 by abenba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free(char **ptr)
{
	size_t	i;

	if (ptr == NULL)
		return ;
	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void free_all(t_map *map)
{
	ft_free(map->map);
	free(map);
}

int	count_lines(int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		i++;
		line = get_next_line(fd);
	}
	return (i);
}

size_t	ft_arrlen(char **s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		i++;
	}
	return (i);
}

int check_wall(t_map *map)
{
	int		up;
	size_t	down;
	int		i;
	int		len;

	i = 0;
	up = 0;
	down = ft_arrlen(map->map) - 1;
	while (map->map[up][i])
	{
		if (map->map[up][i] != '1')
			return (1);
		i++;
	}
	i = 0;
	while (map->map[down][i])
	{
		if (map->map[up][i] != '1')
			return (1);
		i++;
	}
	i = 0;
	len = ft_strlen(map->map[i]);
	while (map->map[i])
	{
		if (map->map[i][0] != '1' || map->map[i][len - 1] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_components(t_map *map, int i)
{
	int	E;
	int	P;
	int X;
	int	y;

	E = 0;
	P = 0;
	map->coin_count = 0;
	X = 0;
	while (map->map[i])
	{
		y = 0;
		while (map->map[i][y])
		{
			if (map->map[i][y] == 'E')
				E++;
			else if (map->map[i][y] == 'P')
			{
				map->x_player = i;
				map->y_player = y;
				P++;
			}
			else if (map->map[i][y] == 'C')
				map->coin_count++;
			else if (map->map[i][y] == 'X')
				X++;
			else if (map->map[i][y] != '1' && map->map[i][y] != '0')
				return (1);
			y++;
		}
		i++;
	}
	if (E > 1 || E == 0 || P == 0 || P > 1 || map->coin_count <= 0)
		return (1);
	return (E + P + map->coin_count);
}

void flood_fill(char **map, int x, int y, int *i)
{
	if (x < 0 || y < 0)
		return ;
	if (map[x][y] == '1' || map[x][y] == 'f' || map[x][y] == 'X')
		return ;
	if (map[x][y] == 'P' || map[x][y] == 'E' || map[x][y] == 'C')
		(*i)++;
	map[x][y] = 'f';
	flood_fill(map, x - 1, y, i);
	flood_fill(map, x + 1, y, i);
	flood_fill(map, x, y + 1, i);
	flood_fill(map, x, y - 1, i);
}

int	check_path(char **map, int comp)
{
	int	x;
	int	y;
	int check;

	x = 0;
	check = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == 'P')
				break ;
			y++;
		}
		if (map[x][y] == 'P')
			break ;
		x++;
	}
	flood_fill(map, x, y, &check);
	x = 0;
	if (comp != check)
		return (1);
	return (0);
}
void inis_map(char **map, int i)
{
	while (i >= 0)
	{
		map[i] = NULL;
		i--;
	}
}

void copy_map(char **tmp, char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		tmp[i] = ft_strdup(map[i]);
		i++;
	}
}

int	check_map(t_map *map)
{
	size_t	len;
	int		i;
	char **tmp_map;
	int comp;

	i = 0;
	len = ft_strlen(map->map[i]);
	while (map->map[i])
	{
		if (len != ft_strlen(map->map[i]))
			return (1);
		i++;
	}
	comp = check_components(map, 0);
	if (check_wall(map) == 1 || comp == 1)
		return (1);
	tmp_map = (char **)malloc((ft_arrlen(map->map) + 1) * sizeof(char *));
	if (!tmp_map)
		return (0);
	inis_map(tmp_map, ft_arrlen(map->map));
	copy_map(tmp_map, map->map);
	if (check_path(tmp_map, comp) == 1)
	{
		ft_free(tmp_map);
		return (1);
	}
	ft_free(tmp_map);
	return (0);
}


int store_map(int fd, t_map *map, char *argv)
{
	int		i;
	size_t	len;
	char *temp;

	i = count_lines(fd);
	close(fd);
	fd = open(argv, O_RDONLY);
	if (fd < 1)
	{
		free(map);
		return (0);
	}
	map->map = (char **)malloc((i + 1) * sizeof(char *));
	if (!map->map)
		return (1);
	inis_map(map->map, i);
	i = 0;
	temp = get_next_line(fd);
	while (temp)
	{
		len = ft_strlen(temp);
		if (len > 0 && temp[len - 1] == '\n')
			temp[len - 1] = '\0';
		map->map[i] = ft_strdup(temp);
		free(temp);
		if (!map->map[i])
		{
			ft_free(map->map);
			return (0);
		}
		i++;
		temp = get_next_line(fd);
	}
	if (i < 3)
		return (1);
	close(fd);
	if (check_map(map) == 1)
		return (1);
	return (0);
}

int	check_ext(int argc, char **argv)
{
	int		i;
	char	*ext;

	i = 0;
	if (argc < 2 || argc > 2)
		return (1);
	while (argv[1][i])
		i++;
	if (i <= 4 || (i == 5 && argv[1][0] == '/'))
		return (1);
	i -= 5;
	ext = ft_substr(argv[1], i + 1, ft_strlen(argv[1]));
	if (ft_strcmp(ext, ".ber") != 0)
	{
		free(ext);
		return (1);
	}
	if (argv[1][i] == '/' || argv[1][i] == ' ')
	{
		free(ext);
		return (1);
	}
	free(ext);
	return (0);
}

int for_norm(t_map **map, int argc, char **argv, int *fd)
{
	if (check_ext(argc, argv) == 1)
		return (1);
	*map = malloc(sizeof(t_map));
	if (!map)
		return (1);
	*fd = open(argv[1], O_RDONLY);
	if (*fd < 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	int fd;
	t_map	*map;

	map = NULL;
	if (for_norm(&map, argc, argv, &fd) == 1)
		return (0);
	if (store_map(fd, map, argv[1]) == 1)
	{
		free_all(map);
		write(2, "Error\n", 6);
		write (2, "Invalid map\n", 12);
		return (1);
	}
	map->mlx = mlx_init();
	if (open_window(map) == 1)
	{
		free_all(map);
		mlx_destroy_window(map->mlx, map->win);
		return (1);
	}
	mlx_loop(map->mlx);
	free_all(map);
	free_imgs(map, 14, 4, 4);
	return (0);
}
