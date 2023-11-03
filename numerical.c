#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"

#define N_GWELLS 4
struct point gwells[] = {
	-0.1, 0.8,
	-0.8, -0.6,
	0.8, 0.0,
	0, 0,
};

f64 *xs, *ys, *vxs, *vys;
u32 w, h, n_points;

void acc(f64 x, f64 y, f64 *ax, f64 *ay) {
	*ax = 0.0; *ay = 0.0;
	for (int i = 0; i < N_GWELLS; i++) {
		f64 dx = gwells[i].x - x;
		f64 dy = gwells[i].y - y;
		f64 dist2 = dx*dx + dy*dy;

		// Newtons law of gravity
		f64 c = FORCE_CONST/(dist2*sqrt(dist2));
		*ax += c*dx;
		*ay += c*dy;
	}
	*ax = fmax(fmin(*ax, ACC_MAX), -ACC_MAX);
	*ay = fmax(fmin(*ay, ACC_MAX), -ACC_MAX);
}

void euler(f64 dt) {
	for (u32 i = 0; i < n_points; i++) {
		f64 ax, ay;
		acc(xs[i], ys[i], &ax, &ay);
		xs[i] += dt*vxs[i];
		ys[i] += dt*vys[i];
		vxs[i] += dt*ax;
		vys[i] += dt*ay;
	}
}

void rk4(f64 dt) {
	for (u32 i = 0; i < n_points; i++) {
		f64 x = xs[i], y = ys[i];
		f64 vx = vxs[i], vy = vys[i];
		f64 ax, ay, bx, by, cx, cy, dx, dy;

		acc(x, y, &ax, &ay);
		acc(x + dt/2*vx, y + dt/2*vy, &bx, &by);
		acc(x + dt/2*(vx + dt/2*ax), y + dt/2*(vy + dt/2*ay), &cx, &cy);
		acc(x + dt*(vx + dt/2*bx), y + dt*(vy + dt/2*by), &dx, &dy);

		xs[i] += dt*(vx + dt/6*(ax + bx + cx));
		ys[i] += dt*(vy + dt/6*(ay + by + cy));
		vxs[i] += dt/6*(ax + 2*bx + 2*cx + dx);
		vys[i] += dt/6*(ay + 2*by + 2*cy + dy);
	}
}

void init_world(
	u32 width, u32 height, f64 xmax, f64 xmin, f64 ymax, f64 ymin,
	f64 init_vx, f64 init_vy/* , u32 n_gwells, struct point *gwells */
	) {
	w = width;
	h = height;
	n_points = w*h;

	xs = (f64 *) malloc(8*n_points);    
	ys = (f64 *) malloc(8*n_points);    
	vxs = (f64 *) malloc(8*n_points);    
	vys = (f64 *) malloc(8*n_points);

	f64 xstep = (xmax - xmin)/w;
	f64 ystep = (ymax - ymin)/h;

	for (u32 i = 0; i < h; i++) {
		for (u32 j = 0; j < w; j++) {
			u32 idx = i*w + j;
			// cartesian coords correspond to middles of pixels.
			xs[idx] = xmin + xstep*(0.5 + j); 
			ys[idx] = ymax - ystep*(0.5 + i); 
			vxs[idx] = init_vx;
			vys[idx] = init_vy;
		}
	}
}

void set_colors(u8 *r, u8 *g, u8 *b, struct color *colors) {
	for (u32 i = 0; i < n_points; i++) {
		f64 x = xs[i]; f64 y = ys[i];

		// finds color index corresponding to minimal distance.
		f64 min_dist2 = INFINITY;
		u32 color_idx;
		for (int j = 0; j < N_GWELLS; j++) {
			f64 dx = gwells[j].x - x;
			f64 dy = gwells[j].y - y;
			f64 dist2 = dx*dx + dy*dy;
			if (dist2 < min_dist2) {
				min_dist2 = dist2;
				color_idx = j;
			}
		}
		
		r[i] = colors[color_idx].r;
		g[i] = colors[color_idx].g;
		b[i] = colors[color_idx].b;
	}
}