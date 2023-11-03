#include <stdlib.h>
#include <stdio.h>
#include "main.h"

#define BMP_HEADER_SIZE 14
#define DIB_HEADER_SIZE 40

static struct BMP_header {
	u8 id1; u8 id2; u32 filesize; u16 app1; u16 app2; u32 offset;
} bmp = {
	'B', 'M', 0, 0, 0, BMP_HEADER_SIZE + DIB_HEADER_SIZE,
};

static struct DIB_header {
	u32 size; u32 width; u32 height; u16 n_planes; u16 bits_per_pixel;
	u32 compression; u32 array_size; u32 print_res_x; u32 print_res_y;
	u32 n_colors; u32 n_important_colors;
} dib = {
	DIB_HEADER_SIZE, 0, 0, 1, 24, 0, 0, 2835, 2835, 0, 0,
};

// Sometimes apps incorrectly display very small bitmaps it seems.
void make_bmp(char *fpath, u32 width, u32 height, u8 *r, u8 *g, u8 *b) {
	// finalize header data
	dib.width = width;
	dib.height = height;
	u32 linesize = width*3 + (width*3)%4;
	dib.array_size = height*linesize;
	bmp.filesize = BMP_HEADER_SIZE + DIB_HEADER_SIZE
		+ dib.array_size;

	// pixel array
	u8 *array = (u8 *) malloc(dib.array_size);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			size_t idx = width*(height - i - 1) + j;
			// bgr instead of rgb??!!
			array[linesize*i + 3*j] = b[idx];
			array[linesize*i + 3*j + 1] = g[idx];
			array[linesize*i + 3*j + 2] = r[idx];
		}
	}

	// Write bmp file
	FILE *fp = fopen(fpath, "wb");
	#define W8(a) { fputc((u8)(a), fp); }
	#define W16(a) { fwrite((u8 *) &(a), 1, 2, fp); }
	#define W32(a) { fwrite((u8 *) &(a), 1, 4, fp); }

	// BMP header - 14 bytes
	W8(bmp.id1) W8(bmp.id2)
	W32(bmp.filesize)
	W16(bmp.app1) W16(bmp.app2)
	W32(bmp.offset)
	// DIB header - 40 bytes
	W32(dib.size)
	W32(dib.width)
	W32(dib.height)
	W16(dib.n_planes)
	W16(dib.bits_per_pixel)
	W32(dib.compression)
	W32(dib.array_size)
	W32(dib.print_res_x)
	W32(dib.print_res_y)
	W32(dib.n_colors)
	W32(dib.n_important_colors)
	// Bitmap data
	fwrite(array, 1, dib.array_size, fp);
	
	fclose(fp);
}