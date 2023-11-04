#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"

struct color colors[] = {
	70, 67, 131,
	13, 159, 185,
	135, 63, 132,
	70, 251, 111,
	150, 15, 240,
	51, 22, 214,
	206, 19, 173,
};

int main() {
	u8 *r = (u8 *) malloc(IMG_WIDTH*IMG_HEIGHT);
	u8 *g = (u8 *) malloc(IMG_WIDTH*IMG_HEIGHT);
	u8 *b = (u8 *) malloc(IMG_WIDTH*IMG_HEIGHT);

	init_world(IMG_WIDTH, IMG_HEIGHT, XMAX, XMIN, YMAX, YMIN,
		INIT_VX, INIT_VY);

	char fpath[FPATH_LENGTH_MAX];
	u32 steps = (u32) (TIME/DT);
	if (ANIMATION) {
		if (steps/FRAMESKIP > N_FRAMES_MAX) return -1;
		for (int i = 0; i < steps + 1; i++) {
			if (i % FRAMESKIP == 0) {
				set_colors(r, g, b, colors);
				sprintf(fpath, "%s/frame%02i.bmp", DIR_PATH, i/FRAMESKIP);
				make_bmp(fpath, IMG_WIDTH, IMG_HEIGHT, r, g, b);
			}
			rk4(DT);
		}
	} else {
		for (int i = 0; i < steps; i++)
			rk4(DT);

		set_colors(r, g, b, colors);
		sprintf(fpath, "%s/%gtime,%gdt.bmp",
			DIR_PATH, TIME, DT);
		make_bmp(fpath, IMG_WIDTH, IMG_HEIGHT, r, g, b);
	}

	return 0;
}