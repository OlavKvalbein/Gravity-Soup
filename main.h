#include <stdint.h>

#define DBGF(x) printf(#x " = %g\n", x);
#define DBGI(x) printf(#x " = %i\n", x);
#define HERE printf("got here\n");

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef double f64;

struct point { f64 x; f64 y; };
struct color { u8 r; u8 g; u8 b; };

void make_bmp(char *fpath, u32 width, u32 height, u8 *r, u8 *g, u8 *b);
void init_world(
	u32 width, u32 height, f64 xmax, f64 xmin, f64 ymax, f64 ymin,
	f64 init_vx, f64 init_vy
	);
void set_colors(u8 *r, u8 *g, u8 *b, struct color *colors);
void euler(f64 dt);
void rk4(f64 dt);

// *************
// Configuration
// *************
#define FPATH_LENGTH_MAX	150
#define N_FRAMES_MAX		99

#define DIR_PATH	"images/clamp25"
#define IMG_WIDTH	800
#define IMG_HEIGHT	800
#define ANIMATION	true
#define FRAMESKIP	5

#define INIT_VX		-0.1
#define INIT_VY		-0.2
#define DT			0.01
#define TIME		3.0
#define XMAX		1.0
#define XMIN		-1.0
#define YMAX		1.0
#define YMIN		-1.0

#define FORCE_CONST	1.0
#define ACC_MAX 		25.0