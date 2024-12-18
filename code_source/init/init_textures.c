/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaesteve <gaesteve@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:34:03 by mcombeau          #+#    #+#             */
/*   Updated: 2024/12/18 14:12:23 by gaesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*on copie les images et on destroy direct comme ca c est deja liberer*/
int	*xpm_to_img(t_data *data, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;
	/*Chargement de la texture stockée dans tmp temporairement.*/
	init_texture_img(data, &tmp, path);
	/*tableau qui contiendra tous les pixels de la texture*/
	buffer = ft_calloc(1,
			sizeof * buffer * data->texinfo.size * data->texinfo.size);
	if (!buffer)
		clean_exit(data, err_msg(NULL, ERR_MALLOC, 1));
	y = 0;
	/*Copie des pixels de tmp a buffer*/
	while (y < data->texinfo.size)
	{
		x = 0;
		while (x < data->texinfo.size)
		{
			buffer[y * data->texinfo.size + x]
				= tmp.addr[y * data->texinfo.size + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, tmp.img);
	return (buffer);
}

void	init_textures(t_data *data)
{
	data->textures = ft_calloc(7, sizeof * data->textures);
	if (!data->textures)
		clean_exit(data, err_msg(NULL, ERR_MALLOC, 1));
	data->textures[NORTH] = xpm_to_img(data, data->texinfo.north);
	data->textures[SOUTH] = xpm_to_img(data, data->texinfo.south);
	data->textures[EAST] = xpm_to_img(data, data->texinfo.east);
	data->textures[WEST] = xpm_to_img(data, data->texinfo.west);
	if (BONUS)
	{
		data->textures[DOOR] = xpm_to_img(data, "./textures/bonus/door.xpm");
		data->textures[SKULL] = xpm_to_img(data, "./textures/bonus/skull.xpm");
	}
	data->title_img = mlx_xpm_file_to_image(
		data->mlx,
		"./textures/title_screen.xpm",
		&data->win_width,
		&data->win_height);
}

void	init_texinfo(t_texinfo *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
	textures->floor = 0;
	textures->ceiling = 0;
	textures->hex_floor = 0x0;
	textures->hex_ceiling = 0x0;
	textures->size = TEX_SIZE;
	textures->step = 0.0;
	textures->pos = 0.0;
	textures->x = 0;
	textures->y = 0;
}
