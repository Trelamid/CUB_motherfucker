#include "libft/libft.h"
#include "mlx_st/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
# include <sys/types.h>
# include <signal.h>
//#include <thread.h>

typedef struct s_win
{
	void	*mlx;
	void	*win;
	int		draw_w;
	int		x;
	int		y;
}t_win;

typedef struct s_vector
{
	int	x;
	int	y;
}t_vector;

typedef struct s_image {
	void		*r;
	t_vector	size;
	char		*pixels;
	int			bits_per_pixel;
	int			line_size;
	int			endian;
}				t_image;

typedef struct s_pc
{
	int		mana; // =0
	t_image	mana_sp;
	t_image	left_sp;
	float	pos_x;
	float	pos_y;
	float	pos_a;
	float	view_a;
	float	depth;

	float	plane_x;
	float	plane_y;
}t_pc;

typedef struct s_area
{
	char	**map;
	char	**map_r;
	int		map_h;
	int		map_w;
	t_image	drow;
	t_image	wall;
	t_image	pika;
}t_area;

typedef struct s_key
{
	int	key_left;
	int	key_right;
	int	key_mid;
	int	key_top;
	int	key_bot;
	int x;
	int y;
}t_key;

typedef struct s_m_a
{
	t_image				sp_magic;
	struct s_m_a	*next;
}t_m_a;

typedef struct s_magic_lst
{
	t_m_a				**m_a;
	t_image				icon_m;
	int					type;
	struct s_magic_lst	*next;
	struct s_magic_lst	*prev;
}t_magic_lst;

typedef struct s_magic
{
	int			type; // 1 = fire
	t_magic_lst	**magic_lst;
	int			cast;
}t_magic;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}t_color;

typedef struct s_color_uc
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}t_color_uc;

typedef struct s_ray_c{
	int		ceil;
	int		floor;
	float	x_for_get;
	float	y_for_get;
	int		x;
	int		y;
	float	dist_w;
	t_color	fon;
	t_color	fon_n;
	t_image	sp;
	t_image	wall;
	pthread_t pthr;
}t_ray_c;

typedef struct s_main
{
	t_win	win;
	t_pc	pc;
	t_area	area;
	t_key	keys;
	t_magic	magic;
	t_ray_c	ray_c;
}t_main;

void	my_put_pixel(char *pixels, int x, int y, t_color color)
{
	if (x < 0 || y < 0)
		return ;
//	if (x > (*framebuffer).width || y > (*framebuffer).height)
//		return ;
	pixels[(1500 * y + x) * 4] = color.b;
	pixels[(1500 * y + x) * 4 + 1] = color.g;
	pixels[(1500 * y + x) * 4 + 2] = color.r;
	pixels[(1500 * y + x) * 4 + 3] = color.a;
}

void	my_put_pixel_uc(char *pixels, int x, int y, t_color_uc color)
{
	if (x < 0 || y < 0)
		return ;
//	if (x > (*framebuffer).width || y > (*framebuffer).height)
//		return ;
	pixels[(1500 * y + x) * 4] = (char)color.b;
	pixels[(1500 * y + x) * 4 + 1] = (char)color.g;
	pixels[(1500 * y + x) * 4 + 2] = (char)color.r;
	pixels[(1500 * y + x) * 4 + 3] = (char)color.a;
}

t_image	ft_new_sprite(void *mlx, char *path)
{
	t_image	img;

	img.r = mlx_xpm_file_to_image(mlx, path, &img.size.x, &img.size.y);
	img.pixels = mlx_get_data_addr(img.r, &img.bits_per_pixel,
			&img.line_size, &img.endian);
	return (img);
}

int	ft_close(void)
{
	exit(17);
}

int	make_win(t_main *m)
{
	m->win.mlx = mlx_init();
	m->win.win = mlx_new_window(m->win.mlx, 1500, 1000, "CUB3D");
	m->win.x = 1500;
	m->win.y = 1000;
	m->win.draw_w = 1;
	mlx_hook(m->win.win, 17, 0, ft_close, NULL);
	return (1);
}

int	check_int(int i1, int i2, t_main *m)
{
	if (i1 < 0 || i2 < 0 || i1 > m->area.map_h - 1 || i2 > m->area.map_w - 1
		|| (m->area.map)[i1][i2] != '1')
		return (0);
	return (1);
}

int	key_A(t_main *m)
{
//	m->pc.pos_x -= 0.1f;
	float	ch_x;
	float	ch_y;

	ch_x = sinf(m->pc.pos_a);
	ch_y = cosf(m->pc.pos_a);
	m->pc.pos_x += ch_x * 0.2f;
	m->pc.pos_y -= ch_y * 0.2f;
	if (check_int((int)(m->pc.pos_y - ch_y * 0.2f), (int)(m->pc.pos_x + ch_x * 0.2f), m))
	{
		m->pc.pos_x -= ch_x * 0.2f;
		m->pc.pos_y += ch_y * 0.2f;
	}
	return (1);
}

int	key_S(t_main *m)
{
//	m->pc.pos_y += 0.1f;
//	if (m->pc.pos_y < 0 || m->pc.pos_y >= m->area.map_h || m->area.map[(int)m->pc.pos_y][(int)m->pc.pos_x] != '0')
//	{
//		m->pc.pos_y -= 1;
//	}
	float	ch_x;
	float	ch_y;

	ch_x = cosf(m->pc.pos_a);
	ch_y = sinf(m->pc.pos_a);
	m->pc.pos_x -= ch_x * 0.2f;
	m->pc.pos_y -= ch_y * 0.2f;
	if (check_int((int)(m->pc.pos_y - ch_y * 0.2f), (int)(m->pc.pos_x - ch_x * 0.2f), m))
	{
		m->pc.pos_x += ch_x * 0.2f;
		m->pc.pos_y += ch_y * 0.2f;
	}
	return (1);
}

int	key_D(t_main *m)
{
//	m->pc.pos_x += 0.1f;
	float	ch_x;
	float	ch_y;

	ch_x = sinf(m->pc.pos_a);
	ch_y = cosf(m->pc.pos_a);
	m->pc.pos_x -= ch_x * 0.2f;
	m->pc.pos_y += ch_y * 0.2f;
	if (check_int((int)(m->pc.pos_y + ch_y * 0.2f), (int)(m->pc.pos_x - ch_x * 0.2f), m))
	{
		m->pc.pos_x += ch_x * 0.2f;
		m->pc.pos_y -= ch_y * 0.2f;
	}
	return (1);
}

int	key_W(t_main *m)
{
//	m->pc.pos_y -= 0.1f;
//	if (m->pc.pos_y < 0 || m->pc.pos_y >= m->area.map_h || m->area.map[(int)m->pc.pos_y][(int)m->pc.pos_x] != '0')
//	{
//		m->pc.pos_y += 1;
//	}
	float	ch_x;
	float 	ch_y;

	ch_x = cosf(m->pc.pos_a);
	ch_y = sinf(m->pc.pos_a);
	m->pc.pos_x += ch_x * 0.2f;
	m->pc.pos_y += ch_y * 0.2f;
	if (check_int((int)(m->pc.pos_y + ch_y * 0.2f), (int)(m->pc.pos_x + ch_x * 0.2f), m))
	{
		m->pc.pos_x -= ch_x * 0.2f;
		m->pc.pos_y -= ch_y * 0.2f;
	}
	return (1);
}

int	key_Q(t_main *m)
{
	float	prev_plane_x;

	prev_plane_x = m->pc.plane_x;
	m->pc.pos_a -= 0.1f;
	m->pc.plane_x = m->pc.plane_x * cosf(-0.1f) - m->pc.plane_y * sinf(-0.1f);
	m->pc.plane_y = prev_plane_x * sinf(-0.1f) + m->pc.plane_y * cosf(-0.1f);
	m->win.draw_w = 1;
//	printf("x %f y %f a%f\n", m->pc.plane_x, m->pc.plane_y, m->pc.pos_a);
	return (1);
}

int	key_E(t_main *m)
{
	float	prev_plane_x;

	prev_plane_x = m->pc.plane_x;
	m->pc.pos_a += 0.1f;
	m->pc.plane_x = m->pc.plane_x * cosf(0.1f) - m->pc.plane_y * sinf(0.1f);
	m->pc.plane_y = prev_plane_x * sinf(0.1f) + m->pc.plane_y * cosf(0.1f);
	m->win.draw_w = 1;
	return (1);
}

int	check_key(int key, t_main *main)
{
	if (key == 53)
		ft_close();
	else if (key == 0)
		key_A(main);
	else if (key == 1)
		key_S(main);
	else if (key == 2)
		key_D(main);
	else if (key == 13)
		key_W(main);
	else if (key == 12)
		key_Q(main);
	else if (key == 14)
		key_E(main);
	main->win.draw_w = 1;
	return (1);
}

//int	key_hook(int key, t_main *main)
//{
//	check_key(key, main);
//	if (key == 53)
//		ft_close();
//	else if (key == 0)
//		key_A(main);
//	else if (key == 1)
//		key_S(main);
//	else if (key == 2)
//		key_D(main);
//	else if (key == 13)
//		key_W(main);
//	else if (key == 12)
//		key_Q(main);
//	else if (key == 14)
//		key_E(main);
//	printf("%d", key);
//	return (1);
//}

int	mana(t_main *main)
{
	static int	mana;

	mana++;
	if (mana >= 10)
	{
		mana = 0;
		if (main->pc.mana >= 100)
			return (1);
		else
			main->pc.mana++;
//		ft_putnbr_fd(main->pc.mana, 1);
//		ft_putstr_fd("\n", 1);
	}
	return (0);
}

t_color	get_color_sprite(int y, int x, t_image *sprite, int *i)
{
	t_color	pix;

	if (!sprite || x < 0 || y < 0 || x > sprite->size.x || y > sprite->size.y)
	{
		*i = 0;
		return (pix);
	}

	pix.b = (int)sprite->pixels[(sprite->size.x * y + x) * 4];
	pix.g = (int)sprite->pixels[(sprite->size.x * y + x) * 4 + 1];
	pix.r = (int)sprite->pixels[(sprite->size.x * y + x) * 4 + 2];
	pix.a = (int)sprite->pixels[(sprite->size.x * y + x) * 4 + 3];
//	printf("%d\n", pix.a);
	if (pix.a < 0)
	{
		*i = 0;
		return (pix);
	}
	*i = 1;
	return (pix);
}

int	my_put_image(t_image *screen, t_image *sprite, int x, int y)
{
	t_color	pix;
	int		x_i;
	int		y_i;
	int		i;

	x_i = -1 + x;
	while (++x_i < sprite->size.x + x && x_i < screen->size.x)
	{
		y_i = -1 + y;
		while (++y_i < sprite->size.y + y && y_i < screen->size.y)
		{
			pix = get_color_sprite(y_i - y, x_i - x, sprite, &i);
			if (i == 1)
				my_put_pixel(screen->pixels, x_i, y_i, pix);
		}
	}
	return (1);
}

int	draw_mana(t_main *m)
{
	int		x;
	int		y;
	t_color	c_mana;
//	t_color	c_string;

	y = 930;
	c_mana.a = 0;
	c_mana.r = 0;
	c_mana.g = 0;
	c_mana.b = 255;
	while (y < 970)
	{
		x = 105;
		while (x < 2 * m->pc.mana + 95)
		{
			my_put_pixel(m->area.drow.pixels, x, y, c_mana);
			x++;
		}
		y++;
	}
	return (1);
}

t_color	x_walls(t_image wall, int num_str_x, int h_obj, int y_w, float dist_wall)
{
	t_color	color;
	int		x;
	int		y;
	float	dist_c;

	x = num_str_x;
	y = (y_w * wall.size.x) / h_obj;
	dist_c = 2 / dist_wall;
	if (dist_c > 1)
		dist_c = 1;
	if (y == 1000)
		y = 999;
	color.b = wall.pixels[(wall.size.x * y + x) * 4];
	if (color.b < 0)
			color.b += 255;
	if (color.b > 0)
	{
		color.b *= dist_c;
		if (color.b < 0)
			color.b = 0;
	}
	color.g = wall.pixels[(wall.size.x * y + x) * 4 + 1];
	if (color.g < 0)
		color.g += 255;
	if (color.g > 0)
	{
		color.g *= dist_c;
		if (color.g < 0)
			color.g = 0;
	}
	color.r = wall.pixels[(wall.size.x * y + x) * 4 + 2];
	if (color.r < 0)
		color.r += 255;
	if (color.r > 0)
	{
		color.r *= dist_c;
		if (color.r < 0)
			color.r = 0;
	}
	color.a = 0;
//	color.r = 150;
//	color.g = 150;
//	color.b = 150;
	return (color);
}

t_color	get_color_wall(t_image wall, float x, float y, int raz, int y_w, float dist_wall)
{
	t_color	need;

	x += 0.01f;
	y += 0.01f;
	x = x - (int)x;
	y = y - (int)y;
	if (y > x)
		return (x_walls(wall, (int)((y - (int)y) * 1000), raz, y_w, dist_wall));
	else
		return (x_walls(wall, (int)((x - (int)x) * 1000), raz, y_w, dist_wall));
}

t_color	get_put_color_pika(t_main *m, int raz, int y, int x_s)
{
	int		x_c;
	int		x_sp;
	int		y_sp;
	t_color	pika_c;

	x_c = 1000 * raz / 1150;
	y_sp = y * 1150 / raz;
	while (x_s <= x_c)
	{
		x_sp = x_s * 1000 / x_c;
		pika_c.b = m->area.pika.pixels[(m->area.pika.size.x * y_sp + x_sp) * 4];
		pika_c.g = m->area.pika.pixels[(m->area.pika.size.x * y_sp + x_sp) * 4 + 1];
		pika_c.r = m->area.pika.pixels[(m->area.pika.size.x * y_sp + x_sp) * 4 + 2];
		pika_c.a = 1;
		if (m->area.pika.pixels[(m->area.pika.size.x * y_sp + x_sp) * 4 + 2] != 0)
			my_put_pixel(m->area.drow.pixels, x_s, y, pika_c);
		x_s++;
	}
	return (pika_c);
}

//int	draw_area2(t_main *m)
//{
//	int		x;
//	int		y;
//	float	ray_angle;
//	float	dist_w;
//	int		find_wall;
//	float	eye_x;
//	float	eye_y;
//	int		test_x;
//	int		test_y;
//	int		ceil;
//	int		floor;
//	int		color;
//	t_color	fon;
//	t_color	fon_n;
//	t_color	wall;
//	int		i;
//
//	x = -1;
//	printf("%f\n", m->pc.pos_a);
//	while (++x < m->win.x)
//	{
//		ray_angle = (m->pc.pos_a - m->pc.view_a / 2.0f) + ((float)(x) / (float)m->win.x) * m->pc.view_a; //направление луча
//		dist_w = 0.0f;
//		find_wall = 0;
//		eye_x = sinf(ray_angle);
//		eye_y = cosf(ray_angle);
//		while (find_wall == 0 && dist_w < m->pc.depth)
//		{
//			dist_w += 0.01f;
//			test_x = (int)(m->pc.pos_x + eye_x * dist_w);
//			test_y = (int)(m->pc.pos_y + eye_y * dist_w);
//			if (test_x < 0 || test_x >= m->area.map_w || test_y < 0 || test_y >= m->area.map_h)
//			{
//				find_wall = 2;
//				dist_w = m->pc.depth;
//			}
//			else if (m->area.map[test_y][test_x] == '1')
//				find_wall = 1;
//		}
//		y = -1;
//		ceil = (int)((float)(m->win.y / 2.0) - (float)m->win.y / ((float)dist_w));
//		floor = m->win.y - ceil;
//		fon.a = 0;
//		fon.r = 0;
//		fon.g = 51;
//		fon.b = 153;
//
//		fon_n.a = 0;
//		fon_n.r = 0;
//		fon_n.g = 51;
//		fon_n.b = 0;
//		while (++y < m->win.y) //отрисовка полосы
//		{
//			if (y <= ceil)
//				my_put_pixel(m->area.drow.pixels, x, y, fon);
//			else if (y > ceil && y <= floor)
//			{
//				if (find_wall == 1)
//				{
//					wall = get_color_wall(m, m->pc.pos_x + eye_x * dist_w, m->pc.pos_y + eye_y * dist_w, floor - ceil, y - ceil, dist_w);
//					my_put_pixel(m->area.drow.pixels, x, y, wall);
//				}
//				else
//				{
//					my_put_pixel(m->area.drow.pixels, x, y, fon);
//				}
//			}
//			else
//			{
//				my_put_pixel(m->area.drow.pixels, x, y, fon_n);
//			}
//		}
//	}
//	return (1);
//}

void	*draw_line(void *ray_cc)
{
	t_ray_c	*ray_c;
	t_color	wall;

	ray_c = ray_cc;
	int a = -1;
	while(++a < 10)
	{
		if (ray_c->y > ray_c->ceil && ray_c->y <= ray_c->floor)
		{
			wall = get_color_wall(ray_c->wall, ray_c->x_for_get, ray_c->y_for_get, ray_c->floor - ray_c->ceil, ray_c->y - ray_c->ceil, ray_c->dist_w);
			my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, wall);
		}
		ray_c->y += 1;
	}
	return (NULL);
//	pthread_detach(ray_c->pthr);
	if (ray_c->y <= ray_c->ceil)
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, ray_c->fon);
	else if (ray_c->y > ray_c->ceil && ray_c->y <= ray_c->floor)
	{
		wall = get_color_wall(ray_c->wall, ray_c->x_for_get, ray_c->y_for_get, ray_c->floor - ray_c->ceil, ray_c->y - ray_c->ceil, ray_c->dist_w);
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, wall);
	}
	else
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, ray_c->fon_n);
	ray_c->y += 1;
	if (ray_c->y <= ray_c->ceil)
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, ray_c->fon);
	else if (ray_c->y > ray_c->ceil && ray_c->y <= ray_c->floor)
	{
		wall = get_color_wall(ray_c->wall, ray_c->x_for_get, ray_c->y_for_get, ray_c->floor - ray_c->ceil, ray_c->y - ray_c->ceil, ray_c->dist_w);
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, wall);
	}
	else
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, ray_c->fon_n);
	ray_c->y += 1;
	if (ray_c->y <= ray_c->ceil)
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, ray_c->fon);
	else if (ray_c->y > ray_c->ceil && ray_c->y <= ray_c->floor)
	{
		wall = get_color_wall(ray_c->wall, ray_c->x_for_get, ray_c->y_for_get, ray_c->floor - ray_c->ceil, ray_c->y - ray_c->ceil, ray_c->dist_w);
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, wall);
	}
	else
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, ray_c->fon_n);
	ray_c->y += 1;
	if (ray_c->y <= ray_c->ceil)
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, ray_c->fon);
	else if (ray_c->y > ray_c->ceil && ray_c->y <= ray_c->floor)
	{
		wall = get_color_wall(ray_c->wall, ray_c->x_for_get, ray_c->y_for_get, ray_c->floor - ray_c->ceil, ray_c->y - ray_c->ceil, ray_c->dist_w);
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, wall);
	}
	else
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, ray_c->fon_n);
	ray_c->y += 1;
	if (ray_c->y <= ray_c->ceil)
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, ray_c->fon);
	else if (ray_c->y > ray_c->ceil && ray_c->y <= ray_c->floor)
	{
		wall = get_color_wall(ray_c->wall, ray_c->x_for_get, ray_c->y_for_get, ray_c->floor - ray_c->ceil, ray_c->y - ray_c->ceil, ray_c->dist_w);
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, wall);
	}
	else
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, ray_c->fon_n);
	ray_c->y += 1;
	if (ray_c->y <= ray_c->ceil)
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, ray_c->fon);
	else if (ray_c->y > ray_c->ceil && ray_c->y <= ray_c->floor)
	{
		wall = get_color_wall(ray_c->wall, ray_c->x_for_get, ray_c->y_for_get, ray_c->floor - ray_c->ceil, ray_c->y - ray_c->ceil, ray_c->dist_w);
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, wall);
	}
	else
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, ray_c->fon_n);
	ray_c->y += 1;
	if (ray_c->y <= ray_c->ceil)
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, ray_c->fon);
	else if (ray_c->y > ray_c->ceil && ray_c->y <= ray_c->floor)
	{
		wall = get_color_wall(ray_c->wall, ray_c->x_for_get, ray_c->y_for_get, ray_c->floor - ray_c->ceil, ray_c->y - ray_c->ceil, ray_c->dist_w);
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, wall);
	}
	else
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, ray_c->fon_n);
	ray_c->y += 1;
	if (ray_c->y <= ray_c->ceil)
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, ray_c->fon);
	else if (ray_c->y > ray_c->ceil && ray_c->y <= ray_c->floor)
	{
		wall = get_color_wall(ray_c->wall, ray_c->x_for_get, ray_c->y_for_get, ray_c->floor - ray_c->ceil, ray_c->y - ray_c->ceil, ray_c->dist_w);
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, wall);
	}
	else
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, ray_c->fon_n);
	ray_c->y += 1;
	if (ray_c->y <= ray_c->ceil)
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, ray_c->fon);
	else if (ray_c->y > ray_c->ceil && ray_c->y <= ray_c->floor)
	{
		wall = get_color_wall(ray_c->wall, ray_c->x_for_get, ray_c->y_for_get, ray_c->floor - ray_c->ceil, ray_c->y - ray_c->ceil, ray_c->dist_w);
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, wall);
	}
	else
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, ray_c->fon_n);
	ray_c->y += 1;
	if (ray_c->y <= ray_c->ceil)
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, ray_c->fon);
	else if (ray_c->y > ray_c->ceil && ray_c->y <= ray_c->floor)
	{
		wall = get_color_wall(ray_c->wall, ray_c->x_for_get, ray_c->y_for_get, ray_c->floor - ray_c->ceil, ray_c->y - ray_c->ceil, ray_c->dist_w);
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, wall);
	}
	else
		my_put_pixel(ray_c->sp.pixels, ray_c->x, ray_c->y, ray_c->fon_n);
	return (NULL);
}

int	dark(char *i, char *rez, double index)
{
	int	d;
	int	r;

	if (index < 1.0)
		index = 1.0;
	r = (int)*rez; //blue
	if (r < 0)
		r += 255;
	r = r - 20;
	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	*i = (char)(r / index);
	i++;
	rez++;
	r = (int)*rez; //green
	if (r < 0)
		r += 255;
	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	*i = (char)(r / index);
	i++;
	rez++;
	r = (int)*rez; //red
	if (r < 0)
		r += 255;
	r = r + 20;
	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	*i = (char)(r / index);
	i++;
	rez++;
	r = (int)*rez;
	if (r < 0)
		r += 255;
	*i = (char)(r / index);
}

int	draw_wall(t_main *m)
{
	int		x;
	int		y;
	float	ray_angle;
	double	dist_w;
	int		find_wall;
	int		ceil;
	int		floorr;
	t_color	fon;
	t_color	fon_n;
	t_color	wall;
	double 	ray_d_x;
	double 	ray_d_y;
	int 	map_x;
	int 	map_y;
	double 	side_dist_x;
	double 	side_dist_y;
	double 	delta_dist_x;
	double	delta_dist_y;
	int 	step_x;
	int 	step_y;
	int		side;
	double	camera_x;
	double	dir_x;
	double	dir_y;
	double floorXWall, floorYWall;
	t_ray_c	ray_c[200];

//	plane_x = 0.66;
//	plane_y = 0.0;
//	int c = 7;
//	m->pc.pos_x = c;
//	m->pc.pos_y = c;
	x = -1;
//	m->pc.pos_a = 6.2f;
//	m->pc.view_a = 0.66f;
	dir_y = sinf(m->pc.pos_a);
	dir_x = cosf(m->pc.pos_a);
	while (++x < m->win.x)
	{
//		ray_angle = (m->pc.pos_a - m->pc.view_a / 2.0f) + ((float)(x) / (float)m->win.x) * m->pc.view_a; //направление луча
		find_wall = 0;
		camera_x = 2 * x / (double)(m->win.x) - 1;
		ray_d_x = dir_x - m->pc.plane_x * camera_x;
		ray_d_y = dir_y - m->pc.plane_y * camera_x;
//		ray_d_y = 1;
//		ray_d_x = -0.659120f;
//		printf("camera_x : %f\n", camera_x);
//		double ray_d_x2 = m->pc.dir_x - plane_x * camera_x;
//		double ray_d_y2 = m->pc.dir_y - plane_y * camera_x;
		map_x = (int)(m->pc.pos_x);
		map_y = (int)(m->pc.pos_y);
//		if(ray_d_x > 1 || ray_d_x < -1)
//			printf("r_x : %.3f r_y : %.3f\n", ray_d_x, ray_d_y);
//		printf("r_x2 : %f r_y2 : %f %d\n", ray_d_x, ray_d_y, x);
		delta_dist_x = fabs(1.0 / ray_d_x);
		delta_dist_y = fabs(1.0 / ray_d_y);
//		delta_dist_x = sqrt(1 + (ray_d_y * ray_d_y) / (ray_d_x * ray_d_x));
//		delta_dist_y = sqrt(1 + (ray_d_x * ray_d_x) / (ray_d_y * ray_d_y));
//		printf("delta_x : %f delta_y : %f\n", delta_dist_x, delta_dist_y);
		if (ray_d_x < 0)
		{
			step_x = -1;
			side_dist_x = (m->pc.pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - m->pc.pos_x) * delta_dist_x;
		}
		if (ray_d_y < 0)
		{
			step_y = -1;
			side_dist_y = (m->pc.pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - m->pc.pos_y) * delta_dist_y;
		}
//		printf("dist_x_s : %f dist_y_s : %f x : %d\n", side_dist_x, side_dist_y, x);
//		printf(" x %.3d y %.3d x :%d\n", map_x, map_y, x);
		while (find_wall == 0 && map_x < m->area.map_w && map_y < m->area.map_h)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (map_x < m->area.map_w && map_y < m->area.map_h && m->area.map[map_y][map_x] != '0')
				find_wall = 1;
		}
//		printf("dist_x_f : %f dist_y_f : %f\n", side_dist_x, side_dist_y);
		if (side == 0)
			dist_w = side_dist_x - delta_dist_x;
		else
			dist_w = side_dist_y - delta_dist_y;
		ceil = (int)((float)(m->win.y / 2.0) - (float)m->win.y / ((float)dist_w));
		floorr = m->win.y - ceil;
		int line_height = (int)(m->win.y / dist_w);
		int ceil = -line_height / 2 + m->win.y / 2;
		if (ceil < 0)
			ceil = 0;
		int floorr = line_height / 2 + m->win.y / 2;
		if (floorr >= m->win.y)
			floorr = m->win.y - 1;
//		printf("dist : %.3f x : %d\n ", dist_w, x);
//		printf("x : %f y : %f\n", m->pc.pos_x, m->pc.pos_y);
		fon.a = 0;
		fon.r = 0;
		fon.g = 51;
		fon.b = 153;

		fon_n.a = 0;
		fon_n.r = 0;
		fon_n.g = 51;
		fon_n.b = 0;

		m->ray_c.x_for_get = m->pc.pos_x + ray_d_x * dist_w;
		m->ray_c.y_for_get = m->pc.pos_y + ray_d_y * dist_w;
		m->ray_c.x = x;
		m->ray_c.floor = floorr;
		m->ray_c.ceil = ceil;
		m->ray_c.dist_w = dist_w;
		m->ray_c.fon_n = fon_n;
		m->ray_c.fon = fon;
		m->ray_c.wall = m->area.wall;
		m->ray_c.sp = m->area.drow;

		double wallX;
		if (side == 0)
			wallX = m->pc.pos_y + dist_w * ray_d_y;
		else
			wallX = m->pc.pos_x + dist_w * ray_d_x;
		wallX = wallX - floor(wallX);
		int texX = (int)(wallX * (double)(m->area.wall.size.x));
		if(side == 0 && ray_d_x > 0)
			texX = ray_d_x - texX - 1;
		if(side == 1 && ray_d_y < 0)
			texX = ray_d_y - texX - 1;
		double step = 1.0 * m->area.wall.size.y / line_height;
		double texPos = (ceil - m->win.y / 2 + line_height / 2) * step;
		double distWall, distPlayer, currentDist;
		y = ceil - 1;
		if (ceil < 0)
			printf("%d\n", ceil);
		while (++y <= floorr) //отрисовка полосы
		{
//			break;
			int texY = (int)texPos;// & (1000 - 1);
			texPos += step;
			if (texY < 0)
				texY += 1000;
			if (texX < 0)
				texX += 1001;
			if (texY >= 1000)
				texY -= 1000;
			if (texX >= 1000)
				texX -= 1000;
//			texY = texY / 2;
//			texX =  texX / 2;
//			printf("tex_x %d tex_y %d y %d x %d\n", texY, texX, y, x);
			dark(&m->area.drow.pixels[(m->area.drow.size.x * y + x) * 4], &m->area.wall.pixels[(m->area.wall.size.x * texY + texX) * 4], dist_w);
//			m->area.drow.pixels[(m->area.drow.size.x * y + x) * 4] = m->area.wall.pixels[(m->area.wall.size.x * texY + texX) * 4];
//			m->area.drow.pixels[(m->area.drow.size.x * y + x) * 4 + 1] = m->area.wall.pixels[(m->area.wall.size.x * texY + texX) * 4 + 1];
//			m->area.drow.pixels[(m->area.drow.size.x * y + x) * 4 + 2] = m->area.wall.pixels[(m->area.wall.size.x * texY + texX) * 4 + 2];
//			m->area.drow.pixels[(m->area.drow.size.x * y + x) * 4 + 3] = 0 ;
//			break;
		}
//		printf("wallX %f \n", wallX);
		if(side == 0 && ray_d_x > 0)
		{
			floorXWall = map_x;
			floorYWall = map_y + wallX;
		}
		else if(side == 0 && ray_d_x < 0)
		{
			floorXWall = map_x + 1.0;
			floorYWall = map_y + wallX;
		}
		else if(side == 1 && ray_d_y > 0)
		{
			floorXWall = map_x + wallX;
			floorYWall = map_y;
		}
		else
		{
			floorXWall = map_x + wallX;
			floorYWall = map_y + 1.0;
		}
//		if (side_dist_x > 20)
//			printf("side x %.1f side y %.1f\n", side_dist_x, side_dist_y);
//		printf("fx %.1f fy %.1f \n", floorXWall, floorYWall);

		distWall = dist_w;
		distPlayer = 0.0;

		if (floorr < 0)
			floorr = m->win.y;
		y = floorr;
		while (++y < m->win.y) //отрисовка полосы
		{
//			break ;
			currentDist = m->win.y / (2.0 * y - m->win.y); //you could make a small lookup table for this instead
			double weight = (currentDist) / (distWall); //точное расположение пола
//			if (weight > 1)
//				printf("distPl %f \n", weight);
//			printf("fx %.1f fy %f \n", currentDist, dist_w);
			double currentFloorX = weight * floorXWall + (1.0 - weight) * m->pc.pos_x;
			double currentFloorY = weight * floorYWall + (1.0 - weight) * m->pc.pos_y;
//			printf("cx %.3f cy %.3f \n", floorXWall, floorYWall);
//			printf("cx %.3f cy %.3f \n", currentFloorX, currentFloorY);
			int floorTexX, floorTexY;
			floorTexX = (int)(currentFloorX * m->area.wall.size.x) % m->area.wall.size.x;
			floorTexY = (int)(currentFloorY * m->area.wall.size.y) % m->area.wall.size.y;
//			printf("fx %d fy %d :: \n", floorTexX, floorTexY);
			dark(&m->area.drow.pixels[(m->area.drow.size.x * y + x) * 4], &m->area.wall.pixels[(m->area.wall.size.x * floorTexY + floorTexX) * 4], currentDist); //floor

			dark(&m->area.drow.pixels[(m->area.drow.size.x * (m->area.wall.size.y - y) + x) * 4], &m->area.wall.pixels[(m->area.wall.size.x * floorTexY + floorTexX) * 4], currentDist); //ceil
		}
//		y = -1;
//		while (++y < m->win.y / 10) //отрисовка полосы
//		{
//			ray_c[y].x_for_get = m->pc.pos_x + ray_d_x * dist_w;
//			ray_c[y].y_for_get = m->pc.pos_y + ray_d_y * dist_w;
//			ray_c[y].x = x;
//			ray_c[y].floor = floor;
//			ray_c[y].ceil = ceil;
//			ray_c[y].dist_w = dist_w;
//			ray_c[y].fon_n = fon_n;
//			ray_c[y].fon = fon;
//			ray_c[y].wall = m->area.wall;
//			ray_c[y].sp = m->area.drow;
//			ray_c[y].y = y * 10;
//			m->ray_c.y = y * 10;
//			draw_line((void *)&m->ray_c); //block_no
//			pthread_create(&ray_c[y].pthr, NULL, draw_line, (void *)&ray_c[y]);
//			pthread_join(ray_c[y].pthr, NULL);
//			if (y <= ceil)
//				my_put_pixel(m->area.drow.pixels, x, y, fon);
//			else if (y > ceil && y <= floor)
//			{
//				wall = get_color_wall(m, m->ray_c.x_for_get, m->ray_c.y_for_get, floor - ceil, y - ceil, dist_w);
//				my_put_pixel(m->area.drow.pixels, x, y, wall);
//			}
//			else
//			{
//				my_put_pixel(m->area.drow.pixels, x, y, fon_n);
//			}
//		}
//		int yy = 0;
//		while (m->area.map[yy])
//		{
//			ft_putstr_fd(m->area.map[yy],1);
//			ft_putstr_fd("\n",1);
//			yy++;
//		}
//		ft_putstr_fd("\n",1);
	}
//	sleep(5);
	return (1);
}

int	check_color(int x, int y, t_image *all, t_color m_wall)
{
	char	*pixels;

	pixels = all->pixels;
	if (pixels[(1500 * y + x) * 4] != m_wall.b)
		return (0);
	else if (pixels[(1500 * y + x) * 4 + 1] != m_wall.g)
		return (0);
	else if (pixels[(1500 * y + x) * 4 + 2] != m_wall.r)
		return (0);
//	if (pixels[(1500 * y + x) * 4 + 3] != m_wall.a)
//		return (0);
//	pixels[(1500 * y + x) * 4] = color.b;
//	pixels[(1500 * y + x) * 4 + 1] = color.g;
//	pixels[(1500 * y + x) * 4 + 2] = color.r;
//	pixels[(1500 * y + x) * 4 + 3] = color.a;
	return (1);
}

int	draw_minimap(t_main *m)
{
	int			x;
	int			y;
	int			x_ch;
	int			y_ch;
	int			x_h;
	int			y_h;
	float		x_a;
	float		y_a;
	float		i;
	t_color		mmap_w;
	t_color		mmap_p;
	t_color		mmap_e;
	int			rev;
	int			iden;
	float		luch;

	i = 0.1f;
	y = 4;
	mmap_w.a = 200;
	mmap_w.r = 2;
	mmap_w.g = 0;
	mmap_w.b = 113;

	mmap_p.a = 100;
	mmap_p.r = 135;
	mmap_p.g = 246;
	mmap_p.b = 255;

	mmap_e.a = 200;
	mmap_e.r = 0;
	mmap_e.g = 5;
	mmap_e.b = 0;
	y = -1;
	iden = 0;
	while (++y < (m->area.map_h * 10) - 5)
	{
		x = -1;
		while (++x < m->area.map_w * 10)
		{
//			rev = (int)m->area.map_h - y / 10;
			rev = y / 10;
			y_h = (rev * 10 + 5);
			if (m->area.map[y / 10][x / 10] == '1')
			{
				rev = 0;
				while (rev < 10)
				{
					my_put_pixel(m->area.drow.pixels, x + 5, y_h + rev, mmap_w);
					rev++;
					iden = 1;
				}
			}
//			else
//			{
//				rev = 0;
//				while (rev < 10)
//				{
//					my_put_pixel(m->area.drow.pixels, x + 5, y_h + rev, mmap_e);
//					rev++;
//					iden = 1;
//				}
//			}
		}
		if (iden == 1)
		{
			y += 9;
			iden = 0;
		}
	}
	y = 0;
	while (y < 5)
	{
		x = 0;
		while (x < 5)
		{
			x_h = (int)m->pc.pos_x * 10 + x + 5;
			rev = (int)(m->pc.pos_y);
			y_h = (rev * 10 + 5 + y);
			my_put_pixel(m->area.drow.pixels, x_h, y_h, mmap_p);
			luch = m->pc.pos_a - m->pc.view_a / 2;
			while (luch <= (m->pc.pos_a + m->pc.view_a / 2) && luch >= (m->pc.pos_a - m->pc.view_a / 2))
			{
				i = 0;
				while (i < 90.0f && y == 2 && x == 2)
				{
					x_a = cosf(luch) * i;
					y_a = sinf(luch) * i;
					if (!check_color(x_h + (int)(x_a), y_h + (int)(y_a), &m->area.drow, mmap_w))
						my_put_pixel(m->area.drow.pixels, x_h + (int)(x_a), y_h + (int)(y_a), mmap_p);
					else
						break ;
					i += 1.0f;
				}
				luch += 0.005f;
			}
//			while (i < 90.0f && y == 5 && x == 5)
//			{
//				x_a = sinf(m->pc.pos_a - m->pc.view_a / 2) * i;
//				y_a = cosf(m->pc.pos_a - m->pc.view_a / 2) * i;
//				if (!check_color(x_h + (int)(x_a), y_h - (int)(y_a), &m->area.drow, mmap_w))
//					my_put_pixel(m->area.drow.pixels, x_h + (int)(x_a), y_h - (int)(y_a), mmap_p);
//				else
//					break ;
//				i += 1.0f;
//			}
//			i = 0;
//			while (i < 90.0f && y == 5 && x == 5)
//			{
//				x_a = sinf(m->pc.pos_a + m->pc.view_a / 2) * i;
//				y_a = cosf(m->pc.pos_a + m->pc.view_a / 2) * i;
//				if (!check_color(x_h + (int)(x_a), y_h - (int)(y_a), &m->area.drow, mmap_w))
//					my_put_pixel(m->area.drow.pixels, x_h + (int)(x_a), y_h - (int)(y_a), mmap_p);
//				else
//					break ;
//				i += 1.0f;
//			}
			x++;
		}
		y++;
	}
//	x = (int)sinf(m->pc.pos_a);
//	y = (int)cosf(m->pc.pos_a);
//	x *= (int)m->pc.pos_x;
//	y *= (int)m->pc.pos_y;
//	x *= 10;
//	y *= 10;
//	i = -1;
//	while (++i < 30)
//	{
//		my_put_pixel(m->area.drow.pixels, x * i, y * i + 800, mmap_p);
//	}
}

int	mouse_left(t_main *m)
{
	if (m->pc.mana >= 1)
	{
		m->pc.mana = m->pc.mana - 1;
		m->magic.cast = 1;
		m->win.draw_w = 1;
	}
	else
	{
		m->pc.mana = m->pc.mana;
		m->magic.cast = 0;
	}
	return (1);
}

int	mouse_right(t_main *m)
{
	if (m->pc.mana >= 40)
		m->pc.mana = m->pc.mana - 40;
	else
		m->pc.mana = m->pc.mana;
	return (1);
}

int	mouse_circle(t_main *main)
{
	return (1);
}

int	mouse_circle_top(t_main *main)
{
	t_magic_lst	*l1;
	l1 = *main->magic.magic_lst;
	l1 = l1->next;
	*main->magic.magic_lst = l1;
	main->keys.key_top = 0;
	return (1);
}

int	mouse_circle_bot(t_main *main)
{
	(*main->magic.magic_lst)=(*main->magic.magic_lst)->prev;
	main->keys.key_bot = 0;
	return (1);
}

int	check_button(t_main *m)
{
	if (m->keys.key_left == 1)
		mouse_left(m);
	if (m->keys.key_top == 1)
		mouse_circle_top(m);
	if (m->keys.key_bot == 1)
		mouse_circle_bot(m);
}

int	draw_spell(t_main *m)
{
	t_magic_lst	*l1;
//	t_magic_lst	*l2;

//	if (m->pc.mana > 1)
//		my_put_image(&m->area.drow, &(*m->magic.magic_lst)->next->sp_magic, 300, 300);
//	l1 = *m->magic.magic_lst;
//	l1 = l1->next;
//	*m->magic.magic_lst = l1;
	return (0);
}

int	draw_ceil_floor(t_main *m)
{
	int	y;
	int	x;

	y = -1;
	float poz_z = (float)m->win.y / 2;
	while(++y < m->win.y)
	{
		float rayDirX0 = cosf(m->pc.pos_a) - m->pc.plane_x;
		float rayDirY0 = sinf(m->pc.pos_a) - m->pc.plane_y;
		float rayDirX1 = cosf(m->pc.pos_a) + m->pc.plane_x;
		float rayDirY1 = sinf(m->pc.pos_a) + m->pc.plane_y;

		int p = y - m->win.y / 2;
		float row_dist = poz_z / (float)p;
//		printf("row_dis %f\n", row_dist);
//		printf("poz_z %f %d\n", poz_z, p);
//		break;

		float floorStepX = row_dist * (rayDirX1 - rayDirX0) / (float)m->win.x;
		float floorStepY = row_dist * (rayDirY1 - rayDirY0) / (float)m->win.x;

		double floorX = m->pc.pos_x + row_dist * rayDirX0;
		double floorY = m->pc.pos_y + row_dist * rayDirY0;

		x = -1;
//		printf("x0:%f y0:%f\n", rayDirX0, rayDirY0);
//		printf("row_dis %d\n", row_dist);
		while (++x < m->win.x)
		{
//			printf("s_x:%d s_y:%d\n", m->area.wall.size.x, m->area.wall.size.y);
//			printf("f_x:%f f_y:%f\n", floorX, floorY);
			int f_x = (int)floorX;
			int f_y = (int)floorY;
			int tx = (int)(m->area.wall.size.x * (floorX - f_x)) & (m->area.wall.size.x - 1);
			if (tx < 0)
				tx = -tx;
			int ty = (int)(m->area.wall.size.y * (floorY - f_y)) & (m->area.wall.size.y - 1);
			if (ty < 0)
				ty = -ty;
//			printf("x:%d y:%d\n", tx, ty);

			floorX += floorStepX;
			floorY += floorStepY;

			t_color	floor_color;
			float dark_c = fabsf(0.5f / row_dist);
			if (dark_c > 1)
				dark_c = 1;
//			printf("%f\n", dark_c);
			floor_color.b = (int)m->area.wall.pixels[(m->area.wall.size.x * ty + tx) * 4];
			if (floor_color.b < 0)
				floor_color.b += 255;
			floor_color.b *= dark_c;
//			printf("%d\n", floor_color.b);
			floor_color.g = (int)m->area.wall.pixels[((m->area.wall.size.x * ty + tx) * 4) + 1];
			if (floor_color.g < 0)
				floor_color.g += 255;
			floor_color.g *= dark_c;
			floor_color.r = (int)m->area.wall.pixels[(m->area.wall.size.x * ty + tx) * 4 + 2];
			if (floor_color.r < 0)
				floor_color.r += 255;
			floor_color.r *= dark_c;
			floor_color.a = (int)m->area.wall.pixels[(m->area.wall.size.x * ty + tx) * 4 + 3];
//			break;

			my_put_pixel(m->area.drow.pixels, x, y, floor_color);
		}
	}
	return (1);
}

int	draw_type_magic(t_main *m)
{
	my_put_image(&m->area.drow, &(*m->magic.magic_lst)->icon_m, 0, m->win.y - 100);
	return (1);
}

int	draw_all(t_main *m)
{
	mlx_clear_window(m->win.mlx, m->win.win);
	if (m->win.draw_w == 1)
	{
//		draw_ceil_floor(m);
		draw_wall(m);
		my_put_image(&m->area.drow, &m->pc.left_sp, 0, m->win.y - 800); //левая рука
		draw_minimap(m);
		my_put_image(&m->area.drow, &m->pc.mana_sp, 100, 925); //рамка от маны
		m->win.draw_w = 0;
	}
	check_button(m);
	draw_type_magic(m);
	if (m->magic.cast == 1)
		m->magic.cast = draw_spell(m);
//		draw_hands(m);
	draw_mana(m);
	mlx_put_image_to_window(m->win.mlx, m->win.win, m->area.drow.r, 0, 0);
//	mlx_put_image_to_window(m->win.mlx, m->win.win, m->pc.left_sp.r, 0, m->win.y - 534);
	mlx_string_put(m->win.mlx, m->win.win, 112, 946, 6750207, "MANA");
	mlx_string_put(m->win.mlx, m->win.win, 155, 946, 6750207, ft_itoa(m->pc.mana));
	return (1);
}

int	loop_h(void *main)
{
	static int	n;
	t_main		*m;

	m = (t_main *)main;
	draw_all(m);
//	check_key(key, m);
	mana(m);
	return (1);
}

int	make_pc(t_pc *pc, t_main *m)
{
	pc->mana_sp = ft_new_sprite(m->win.mlx, "../mana.xpm");
	pc->left_sp = ft_new_sprite(m->win.mlx, "../left_hand.xpm");
	pc->mana = 50;
	pc->pos_a = 1.571f;
	pc->pos_x = 1.1f;
	pc->pos_y = 1.1f;
	pc->depth = 30.0f;
	pc->view_a = 1.05f;
	pc->plane_x = 0.660f;
	pc->plane_y = -0.019f;
	return (1);
}

//int	mouse_move(t_main *main, int x, int y)
//{
//	ft_putnbr_fd(x, 1);
//	ft_putchar_fd('\n', 1);
//	ft_putnbr_fd(y, 1);
//	ft_putchar_fd('\n', 1);
//	return (1);
//}

int	mouse_h(int key, int x, int y, t_main *main)
{
	printf("x : %f\ny : %f\na : %f\n", main->pc.pos_x, main->pc.pos_y, main->pc.pos_a);
	if (key == 1)
		mouse_left(main);
	else if (key == 2)
		mouse_right(main);
	else if (key == 3)
		mouse_circle(main);
	else if (key == 5)
		mouse_circle_top(main);
	else if (key == 4)
		mouse_circle_bot(main);
//	mouse_move(main, x, y);
	return (1);
}

int	make_area(t_area *area, t_main *main)
{
	char	*str;
	int		i;
	int		i_r;

	str =       ft_strdup("1111111111 ");
	str = ft_strjoin(str, "1010000001 ");
	str = ft_strjoin(str, "1010000001 ");
	str = ft_strjoin(str, "1010000001 ");
	str = ft_strjoin(str, "1010000001 ");
	str = ft_strjoin(str, "1010000001 ");
	str = ft_strjoin(str, "1010000001 ");
	str = ft_strjoin(str, "1010000001 ");
	str = ft_strjoin(str, "1000000001 ");
	str = ft_strjoin(str, "1000000001 ");
	str = ft_strjoin(str, "1000000001 ");
	str = ft_strjoin(str, "1000000001 ");
	str = ft_strjoin(str, "1111111111");
	area->map = ft_split(str, ' ');
	free(str);
	area->map_h = 13;
	area->map_w = 10;
//	area->map_r = malloc(sizeof(char *) * area->map_h + 1);
//	i = 0;
//	i_r = area->map_h - 1;
//	while (i < area->map_h)
//	{
//		area->map_r[i_r] = area->map[i];
//		i_r--;
//		i++;
//	}
//	area->map_r[i] = NULL;
//	i = 0;
//	while (area->map_r[i])
//	{
//		ft_putstr_fd(area->map_r[i], 1);
//		i++;
//	}
	area->drow = ft_new_sprite(main->win.mlx, "../all.xpm");
	area->wall = ft_new_sprite(main->win.mlx, "../wall.xpm");
//	area->pika = ft_new_sprite(main->win.mlx, "/Users/kdakota/CLion_deb/CUB/pika_b.xpm");
	return (1);
}

int	move_mouse(int x, int y, t_main *m)
{
	static int	change;

	if (x >= 0 && x <= m->win.x && y >= 0 && y <= m->win.y && change != x)
	{
		if (x > change)
			key_E(m);
		else if (x < change)
			key_Q(m);
	}
	change = x;
//	ft_putnbr_fd(x, 1);
//	ft_putnbr_fd(y, 1);
}

int	mouse_button_pr(int key, int x, int y, t_main *m)
{
//	printf("%d\n%d\n%d\n", key, x, y);
	if (key == 1)
		m->keys.key_left = 1;
	else if (key == 2)
		m->keys.key_right = 1;
	else if (key == 3)
		m->keys.key_mid = 1;
	else if (key == 5)
		m->keys.key_top = 1;
	else if (key == 4)
		m->keys.key_bot = 1;
	m->keys.x = x;
	m->keys.y = y;
	return (1);
}

int	mouse_button_re(int key, int x, int y, t_main *m)
{
//	printf("%d\n%d\n%d\n", key, x, y);
	if (key == 1)
		m->keys.key_left = 0;
//	else if (key == 2)
//		m->keys.key_right = 0;
//	else if (key == 3)
//		m->keys.key_mid = 0;
//	else if (key == 5)
//		m->keys.key_top = 0;
//	else if (key == 4)
//		m->keys.key_bot = 0;
	return (1);
}

int	make_key(t_key *key, t_main *m)
{
	key->key_bot = 0;
	key->key_top = 0;
	key->key_mid = 0;
	key->key_right = 0;
	key->key_left = 0;
	return (1);
}

int	make_magic(t_magic *magic, t_main *main)
{
	t_magic_lst	*lstf;
	t_magic_lst	*lstwa;
	t_magic_lst	*lstt;
	t_magic_lst	*lsta;

	t_m_a		*l_i0;
	t_m_a		*l_i1;
	t_m_a		*l_i2;
	t_m_a		*l_i3;
	t_m_a		*l_i4;

	magic->type = 0;
	magic->cast = 0;
	lstf = malloc(sizeof(t_magic_lst));
	lstwa = malloc(sizeof(t_magic_lst));
	lstt = malloc(sizeof(t_magic_lst));
	lsta = malloc(sizeof(t_magic_lst));
	lstf->type = 1;
	lstwa->type = 1;
	lsta->type = 1;
	lstt->type = 1;
	lstf->icon_m = ft_new_sprite(main->win.mlx, "../fire_ic.xpm");
	lstwa->icon_m = ft_new_sprite(main->win.mlx, "../water_ic.xpm");
	lsta->icon_m = ft_new_sprite(main->win.mlx, "../wind_ic.xpm");
	lstt->icon_m = ft_new_sprite(main->win.mlx, "../earth_ic.xpm");

	lstf->next = lstwa;
	lstwa->next = lstt;
	lstt->next = lsta;
	lsta->next = lstf;

	lstf->prev = lsta;
	lstwa->prev = lstf;
	lstt->prev = lstwa;
	lsta->prev = lstt;

	magic->magic_lst = malloc(sizeof(t_magic_lst *));
	*magic->magic_lst = lstwa;

//	l_i0 = malloc(sizeof(t_m_a));
//	l_i0->sp_magic = ft_new_sprite(main->win.mlx, "../fire_ic.xpm");
//	l_i1 = malloc(sizeof(t_m_a));
//	l_i1->sp_magic = ft_new_sprite(main->win.mlx, "../water_ic.xpm");
//	l_i0->next = l_i1;
//	l_i1->next = l_i0;
//	main->magic.

	return (1);
}

int	main(void)
{
	t_main	main;

	make_win(&main);
	make_pc(&main.pc, &main);
	make_area(&main.area, &main);
	make_key(&main.keys, &main);
	make_magic(&main.magic, &main);
//	mlx_key_hook(main.win.win, key_hook, &main);
	mlx_hook(main.win.win, 2, 1L << 0, check_key, &main);
	mlx_hook(main.win.win, 6, 1L << 6, move_mouse, &main);
	mlx_hook(main.win.win, 4, 1L << 2, mouse_button_pr, &main);
	mlx_hook(main.win.win, 5, 1L << 3, mouse_button_re, &main);
	mlx_loop_hook(main.win.mlx, loop_h, &main);
//	mlx_mouse_hook(main.win.win, mouse_h, &main);
	mlx_loop(main.win.mlx);
	return (0);
}
