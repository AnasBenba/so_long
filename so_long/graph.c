#include "so_long.h"

void free_imgs(t_map *img, int i_coins, int i_player, int i_enemy)
{
    int i;

    i = 0;
    if (!img)
        return ;
    if (img->img_wall)
    {
        mlx_destroy_image(img->mlx, img->img_wall);
        img->img_wall = NULL;
    }
    if (img->img_black)
    {
        mlx_destroy_image(img->mlx, img->img_black);
        img->img_black = NULL;
    }
    if (img->door_closed)
    {
        mlx_destroy_image(img->mlx, img->door_closed);
        img->door_closed = NULL;
    }
    if (img->door_open)
    {
        mlx_destroy_image(img->mlx, img->door_open);
        img->door_open = NULL;
    }
    while (i < i_coins && img->coin_img[i])
    {
        mlx_destroy_image(img->mlx, img->coin_img[i]);
        img->coin_img[i] = NULL;
        i++;
    }
    i = 0;
    while (i < i_player && img->player_img[i])
    {
        mlx_destroy_image(img->mlx, img->player_img[i]);
        img->player_img[i] = NULL;
        i++;
    }
    i = 0;
    while (i < i_enemy && img->enemy_img[i])
    {
        mlx_destroy_image(img->mlx, img->enemy_img[i]);
        img->enemy_img[i] = NULL;
        i++;
    }
}

void    put_frames(char type, int x, int y, t_map *game)
{
    if (type == 'C')
    {
        mlx_put_image_to_window(game->mlx, game->win, game->coin_img[game->c_frame], y * 32, x * 32);
    }
    else if (type == 'P')
    {
            if (game->flag == 1)
                mlx_put_image_to_window(game->mlx, game->win, game->img_black, (game->y_player - 1) * 32, game->x_player * 32);
            else if (game->flag == 2)
                mlx_put_image_to_window(game->mlx, game->win, game->img_black, game->y_player * 32, (game->x_player + 1) * 32);
            else if (game->flag == 3)
                mlx_put_image_to_window(game->mlx, game->win, game->img_black, (game->y_player + 1)* 32, game->x_player * 32);
            else if (game->flag == 4)
                mlx_put_image_to_window(game->mlx, game->win, game->img_black, game->y_player * 32, (game->x_player - 1) * 32);
            game->flag = 0;
            mlx_put_image_to_window(game->mlx, game->win, game->player_img[game->p_frame], game->y_player * 32, game->x_player * 32);

    }
    else if (type == 'X')
    {
        mlx_put_image_to_window(game->mlx, game->win, game->enemy_img[game->e_frame], y * 32, x * 32);
    }
    else if (type == 'E')
    {
        if (game->coin_count != 0)
            mlx_put_image_to_window(game->mlx, game->win, game->door_closed, y * 32, x * 32);
        else
            mlx_put_image_to_window(game->mlx, game->win, game->door_open, y * 32, x * 32);
    }
}

void update_frames(t_map *game)
{
    if (game->c_slow++ >= (5000))
    {
        if (game->c_frame == 13)
            game->c_frame = 0;
        game->c_frame++;
        game->c_slow = 0;
    }
    if (game->p_slow++ >= (6000))
    {
        if (game->p_frame == 3)
            game->p_frame = 0;
        game->p_frame++;
        game->p_slow = 0;
    }
    if (game->x_slow++ >= (8000))
    {
        if (game->e_frame == 3)
            game->e_frame = 0;
        game->e_frame++;
        game->x_slow = 0;
    }
}

int draw_coin(t_map *map)
{
    int x = 0;
    int y;

    while (map->map[x])
    {
        y = 0;
        while (map->map[x][y])
        {
            if (map->map[x][y] == 'C' || map->map[x][y] == 'X' || map->map[x][y] == 'P' || map->map[x][y] == 'E')
            {
                update_frames(map);
                put_frames(map->map[x][y], x, y, map);
            }
            y++;
        }
        x++;
    }
    return (0);
}

void init_img_null(void **img, int i)
{
    int y;

    y = 0;
    while (y < i)
    {
        img[y] = NULL;
        y++;
    }
}

int game_init_2(t_map *img)
{
    int height;
    int width;

    height = 32;
    width = 32;
    img->img_wall = NULL;
    img->img_wall = mlx_xpm_file_to_image(img->mlx, img->wall, &(width), &(height));
    img->img_black = mlx_xpm_file_to_image(img->mlx, img->black, &(width), &(height));
    img->door_closed = mlx_xpm_file_to_image(img->mlx, img->door_c, &(width), &(height));
    img->door_open = mlx_xpm_file_to_image(img->mlx, img->door_o, &(width), &(height));

    // init_img_null(img->coin_img, 13);
    img->coin_img[0] = mlx_xpm_file_to_image(img->mlx, img->coins[0], &(width), &(height));
    if (!img->coin_img[0])
    {
        write(2, "Error\nfaild to load img\n", 24);
        free_imgs(img, 14, 4, 4);
        return (1);
    }
    img->coin_img[1] = mlx_xpm_file_to_image(img->mlx, img->coins[1], &(width), &(height));
    if (!img->coin_img[1])
    {
        write(2, "Error\nfaild to load img\n", 24);
        free_imgs(img, 14, 4, 4);
        return (1);
    }
    img->coin_img[2] = mlx_xpm_file_to_image(img->mlx, img->coins[2], &(width), &(height));
    if (!img->coin_img[2])
    {
        write(2, "Error\nfaild to load img\n", 24);
        free_imgs(img, 14, 4, 4);
        return (1);
    }
    img->coin_img[3] = mlx_xpm_file_to_image(img->mlx, img->coins[3], &(width), &(height));
    if (!img->coin_img[3])
    {
        write(2, "Error\nfaild to load img\n", 24);
        free_imgs(img, 14, 4, 4);
        return (1);
    }
    img->coin_img[4] = mlx_xpm_file_to_image(img->mlx, img->coins[4], &(width), &(height));
    if (!img->coin_img[4])
    {
        write(2, "Error\nfaild to load img\n", 24);
        free_imgs(img, 14, 4, 4);
        return (1);
    }
    img->coin_img[5] = mlx_xpm_file_to_image(img->mlx, img->coins[5], &(width), &(height));
    if (!img->coin_img[5])
    {
        write(2, "Error\nfaild to load img\n", 24);
        free_imgs(img, 14, 4, 4);
        return (1);
    }
    img->coin_img[6] = mlx_xpm_file_to_image(img->mlx, img->coins[6], &(width), &(height));
    if (!img->coin_img[6])
    {
        write(2, "Error\nfaild to load img\n", 24);
        free_imgs(img, 14, 4, 4);
        return (1);
    }
    img->coin_img[7] = mlx_xpm_file_to_image(img->mlx, img->coins[7], &(width), &(height));
    if (!img->coin_img[7])
    {
        write(2, "Error\nfaild to load img\n", 24);
        free_imgs(img, 14, 4, 4);
        return (1);
    }
    img->coin_img[8] = mlx_xpm_file_to_image(img->mlx, img->coins[8], &(width), &(height));
    if (!img->coin_img[8])
    {
        write(2, "Error\nfaild to load img\n", 24);
        free_imgs(img, 14, 4, 4);
        return (1);
    }
    img->coin_img[9] = mlx_xpm_file_to_image(img->mlx, img->coins[9], &(width), &(height));
    if (!img->coin_img[9])
    {
        write(2, "Error\nfaild to load img\n", 24);
        free_imgs(img, 14, 4, 4);
        return (1);
    }
    img->coin_img[10] = mlx_xpm_file_to_image(img->mlx, img->coins[10], &(width), &(height));
    if (!img->coin_img[10])
    {
        write(2, "Error\nfaild to load img\n", 24);
        free_imgs(img, 14, 4, 4);
        return (1);
    }
    img->coin_img[11] = mlx_xpm_file_to_image(img->mlx, img->coins[11], &(width), &(height));
    if (!img->coin_img[11])
    {
        write(2, "Error\nfaild to load img\n", 24);
        free_imgs(img, 14, 4, 4);
        return (1);
    }
    img->coin_img[12] = mlx_xpm_file_to_image(img->mlx, img->coins[12], &(width), &(height));
    if (!img->coin_img[12])
    {
        write(2, "Error\nfaild to load img\n", 24);
        free_imgs(img, 14, 4, 4);
        return (1);
    }
    img->coin_img[13] = mlx_xpm_file_to_image(img->mlx, img->coins[13], &(width), &(height));
    if (!img->coin_img[13])
    {
        write(2, "Error\nfaild to load img\n", 24);
        free_imgs(img, 14, 4, 4);
        return (1);
    }

    // init_img_null(img->player_img, 2);
    img->player_img[0] = mlx_xpm_file_to_image(img->mlx, img->player[0], &(width), &(height));
    if (!img->player_img[0])
    {
        write(2, "Error\nfaild to load img\n", 24);
        free_imgs(img, 14, 4, 4);
        return (1);
    }
    img->player_img[1] = mlx_xpm_file_to_image(img->mlx, img->player[1], &(width), &(height));
    if (!img->player_img[1])
    {
        write(2, "Error\nfaild to load img\n", 24);
        free_imgs(img, 14, 4, 4);
        return (1);
    }
    img->player_img[2] = mlx_xpm_file_to_image(img->mlx, img->player[2], &(width), &(height));
    if (!img->player_img[2])
    {
        write(2, "Error\nfaild to load img\n", 24);
        free_imgs(img, 14, 4, 4);
        return (1);
    }
    img->player_img[3] = mlx_xpm_file_to_image(img->mlx, img->player[3], &(width), &(height));
    if (!img->player_img[3])
    {
        write(2, "Error\nfaild to load img\n", 24);
        free_imgs(img, 14, 4, 4);
        return (1);
    }

    img->enemy_img[0] = mlx_xpm_file_to_image(img->mlx, img->enemy[0], &(width), &(height));
    if (!img->enemy_img[0])
    {
        write(2, "Error\nfaild to load img\n", 24);
        free_imgs(img, 14, 4, 4);
        return (1);
    }
    img->enemy_img[1] = mlx_xpm_file_to_image(img->mlx, img->enemy[1], &(width), &(height));
    if (!img->enemy_img[1])
    {
        write(2, "Error\nfaild to load img\n", 24);
        free_imgs(img, 14, 4, 4);
        return (1);
    }
    img->enemy_img[2] = mlx_xpm_file_to_image(img->mlx, img->enemy[2], &(width), &(height));
    if (!img->enemy_img[2])
    {
        write(2, "Error\nfaild to load img\n", 24);
        free_imgs(img, 14, 4, 4);
        return (1);
    }
    img->enemy_img[3] = mlx_xpm_file_to_image(img->mlx, img->enemy[3], &(width), &(height));
    if (!img->enemy_img[3])
    {
        write(2, "Error\nfaild to load img\n", 24);
        free_imgs(img, 14, 4, 4);
        return (1);
    }
    return (0);
}

void exit_door(t_map *game)
{
    if (game->coin_count == 0 && game->map[game->x_player][game->y_player] == 'E')
    {
        free_imgs(game, 14, 4, 4);
        mlx_destroy_window(game->mlx, game->win);
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        free_all(game);
        write(1, "YOU WON!\n", 9);
        exit(0);
    }
}

void reset(t_map *game)
{
    int x;
    int y;

    x = 0;
    while (game->map[x])
    {
        y = 0;
        while (game->map[x][y])
        {
            if (game->map[x][y] != '1')
                mlx_put_image_to_window(game->mlx, game->win, game->img_black, y * 32, x * 32);
            y++;
        }
        x++;
    }
}

int key_esc(int keycode, t_map *game)
{
    if (keycode == 65363)
    {
        if (game->map[game->x_player][game->y_player + 1] == 'X')
        {
            free_imgs(game, 14, 4, 4);
            mlx_destroy_window(game->mlx, game->win);
            mlx_destroy_display(game->mlx);
            free(game->mlx);
            free_all(game);
            exit(0);
        }
        if (game->map[game->x_player][game->y_player + 1] != '1')
        {
            game->flag = 1;
            game->y_player += 1;
            game->count++;
        }
        if (game->map[game->x_player][game->y_player] == 'C')
        {
            mlx_put_image_to_window(game->mlx, game->win, game->img_black, game->y_player * 32, game->x_player * 32);
            game->map[game->x_player][game->y_player] = '0';
            game->coin_count--;
        }
        exit_door(game);
        reset(game);
        ft_printf("count: %d\n", game->count);
    }
    if (keycode == 65362)
    {
        if (game->map[game->x_player - 1][game->y_player] == 'X')
        {
            free_imgs(game, 14, 4, 4);
            mlx_destroy_window(game->mlx, game->win);
            mlx_destroy_display(game->mlx);
            free(game->mlx);
            free_all(game);
            exit(0);
        }
        if (game->map[game->x_player - 1][game->y_player] != '1')
        {
            game->flag = 2;
            game->x_player -= 1;
            game->count++;
        }
        if (game->map[game->x_player][game->y_player] == 'C')
        {
            mlx_put_image_to_window(game->mlx, game->win, game->img_black, game->y_player * 32, game->x_player * 32);
            game->map[game->x_player][game->y_player] = '0';
            game->coin_count--;
        }
        exit_door(game);
        reset(game);
        ft_printf("count: %d\n", game->count);
    }
    if (keycode == 65361)
    {
        if (game->map[game->x_player][game->y_player - 1] == 'X')
        {
            free_imgs(game, 14, 4, 4);
            mlx_destroy_window(game->mlx, game->win);
            mlx_destroy_display(game->mlx);
            free(game->mlx);
            free_all(game);
            exit(0);
        }
        if (game->map[game->x_player][game->y_player - 1] != '1')
        {
            game->flag = 3;
            game->y_player -= 1;
            game->count++;
        }
        if (game->map[game->x_player][game->y_player] == 'C')
        {
            mlx_put_image_to_window(game->mlx, game->win, game->img_black, game->y_player * 32, game->x_player * 32);
            game->map[game->x_player][game->y_player] = '0';
            game->coin_count--;
        }
        exit_door(game);
        reset(game);
        ft_printf("count: %d\n", game->count);
    }
    if (keycode == 65364)
    {
        if (game->map[game->x_player + 1][game->y_player] == 'X')
        {
            free_imgs(game, 14, 4, 4);
            mlx_destroy_window(game->mlx, game->win);
            mlx_destroy_display(game->mlx);
            free(game->mlx);
            free_all(game);
            exit(0);
        }
        if (game->map[game->x_player + 1][game->y_player] != '1')
        {
            game->flag = 4;
            game->x_player += 1;
            game->count++;
        }
        if (game->map[game->x_player][game->y_player] == 'C')
        {
            mlx_put_image_to_window(game->mlx, game->win, game->img_black, game->y_player * 32, game->x_player * 32);
            game->map[game->x_player][game->y_player] = '0';
            game->coin_count--;
        }
        exit_door(game);
        reset(game);
        ft_printf("count: %d\n", game->count);
    }
    if (keycode == 65307)
    {
        free_imgs(game, 14, 4, 4);
        mlx_destroy_window(game->mlx, game->win);
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        free_all(game);
        exit(0);
    }
    return (0);
}

int close_window(t_map *game)
{
    if (game)
    {
        free_imgs(game, 14, 4, 4);
        mlx_destroy_window(game->mlx, game->win);
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        free_all(game);
        exit(0);
    }
    return (0);
}

int game_init_1(t_map *map)
{
    map->c_frame = 0;
    map->p_frame = 0;
    map->e_frame = 0;
    map->p_slow = 0;
    map->c_slow = 0;
    map->x_slow = 0;
    map->flag = 0;
    map->count = 0;

    map->wall = "./textures/wall.xpm";
    map->black = "./textures/black.xpm";
    map->door_c = "./textures/Door_closed.xpm";
    map->door_o = "./textures/Door_open.xpm";

    map->coins[0] = "./textures/coin.xpm";
    map->coins[1] = "./textures/coin2.xpm";
    map->coins[2] = "./textures/coin3.xpm";
    map->coins[3] = "./textures/coin4.xpm";
    map->coins[4] = "./textures/coin5.xpm";
    map->coins[5] = "./textures/coin6.xpm";
    map->coins[6] = "./textures/coin7.xpm";
    map->coins[7] = "./textures/coin8.xpm";
    map->coins[8] = "./textures/coin9.xpm";
    map->coins[9] = "./textures/coin10.xpm";
    map->coins[10] = "./textures/coin11.xpm";
    map->coins[11] = "./textures/coin12.xpm";
    map->coins[12] = "./textures/coin13.xpm";
    map->coins[13] = "./textures/coin14.xpm";

    map->player[0] = "./textures/player.xpm";
    map->player[1] = "./textures/player2.xpm";
    map->player[2] = "./textures/player3.xpm";
    map->player[3] = "./textures/player4.xpm";

    map->enemy[0] = "./textures/enemy.xpm";
    map->enemy[1] = "./textures/enemy2.xpm";
    map->enemy[2] = "./textures/enemy3.xpm";
    map->enemy[3] = "./textures/enemy4.xpm";
    init_img_null((void **)map->coin_img, 14);
    init_img_null((void **)map->player_img, 4);
    init_img_null((void **)map->enemy_img, 4);
    if (game_init_2(map) == 1)
        return (1);
    return (0);
}

int open_window(t_map *map)
{
    size_t col;
    size_t row;
    int x;
    int y;

    x = 0;
    col = ft_strlen(map->map[0]);
    row = ft_arrlen(map->map);
    map->win = mlx_new_window(map->mlx, col * 32, row * 32, "so_long");
    if (game_init_1(map) == 1)
        return (1);
    while (map->map[x])
    {
        y = 0;
        while (map->map[x][y])
        {
            if (map->map[x][y] == '1')
                mlx_put_image_to_window(map->mlx, map->win, map->img_wall, y * 32, x * 32);
            y++;
        }
        x++;
    }
    mlx_hook(map->win, 2, 1L<<0, key_esc, map);
    // mlx_key_hook(map->win, key_esc, map);
    mlx_hook(map->win, 17, 0, close_window, map);
    mlx_loop_hook(map->mlx, draw_coin, map);
    return (0);
}