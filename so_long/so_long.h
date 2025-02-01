/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:21:32 by abenba            #+#    #+#             */
/*   Updated: 2025/01/20 18:21:33 by abenba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <mlx.h>
# include "printf/ft_printf.h"

typedef struct s_map 
{
    void *mlx;
    void *win;
    void *img_wall;
    void *img_black;
    void *coin_img[14];
    void *door_closed;
    void *door_open;
    void *player_img[4];
    void *player_img_up;
    void *enemy_img[4];
    char *wall;
    char *black;
    char *door_c;
    char *door_o;
    char *player[4];
    char *coins[14];
    char *enemy[4];
    char **map;
    int coin_count;
    int c_frame;
    int p_frame;
    int e_frame;
    int x_player;
    int y_player;
    int c_slow;
    int p_slow;
    int x_slow;
    int flag;
    int count;
} t_map;

size_t	ft_strlen(const char *c);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
char	*get_next_line(int fd);
size_t	ft_arrlen(char **s);
int    open_window(t_map *map);
void free_imgs(t_map *img, int i_coins, int i_player, int i_enemy);
void free_all(t_map *map);
void	ft_free(char **ptr);


#endif
