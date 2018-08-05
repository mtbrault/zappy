/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** ressource spawn
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"

void	get_client(info_t *info)
{
	int client_fd = accept(info->server.fd,
		(struct sockaddr *)&info->server.s_in_client,
			&info->server.s_in_size);
	if (client_fd != -1)
		add_client(info, client_fd);
	else
		exit(84);
	dprintf(client_fd, "WELCOME\n");
}

void	ressource_spawn(info_t *info)
{
	time_t	now = time(NULL);
	tile_t	*tmp;

	if (now - info->ressource_spawn <= (20 / info->freq))
		return ;
	for (int y = 0; y < info->height; y++) {
		for (int x = 0; x < info->width; x++) {
			tmp = get_tile(x, y, info);
			for (int i = 0; i < 7; ++i) {
				if ((rand() % 20) == 0) {
					tmp->ressources[i] += 1;
					for (gui_list_t *tmpg = info->gui; tmpg; tmpg = tmpg->next) {
						if (tmpg->gui->is_log)
							dprintf(tmpg->gui->fd ,"adi %i %i %i\n", i, 
								tmp->x, tmp->y);
						}
				}
			}
			tmp = tmp->right;
		}
		tmp = tmp->right;
		tmp = tmp->down;
	}
	info->ressource_spawn = now;
}