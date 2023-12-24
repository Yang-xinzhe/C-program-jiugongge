#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include "show.h"
#include "bmp.h"

static struct fb_var_screeninfo vinfo;
static char *psrc_mem = NULL;
static char *pmem_mem = NULL;

void fb_init(screen_info *info)
{
	// 打开显卡设备
	int fd = open ("/dev/fb0", O_RDWR);
	if (-1 == fd)
		perror("open fb err!");
	
	// 获得屏幕分辨率信息
	// 显卡是一个具体的设备，设备使用依赖操作系统
	// 关于设备如何使用如何控制，需要查看对应的头文件
	// linux内核提供的头文件，/usr/include/linux
	// 显卡相关头文件 /usr/include/linux/fb.h 
	// ioctl(int d, int request, ...);
	ioctl (fd, FBIOGET_VSCREENINFO, &vinfo);
#if 0
	printf("vir_x = %d, vir_y = %d\n", 
			vinfo.xres_virtual,
			vinfo.yres_virtual);
	printf("xrex = %d, yres = %d\n",
			vinfo.xres,
			vinfo.yres);
	printf("col = %d\n", vinfo.bits_per_pixel);
#endif
	info->w = vinfo.xres;
	info->h = vinfo.yres;
	info->bits_per_pixel = vinfo.bits_per_pixel;

	long src_size = vinfo.xres_virtual * vinfo.yres_virtual * vinfo.bits_per_pixel / 8;

	// 显存映
	psrc_mem = mmap(NULL, src_size, 
			PROT_WRITE | PROT_READ,
			MAP_SHARED, fd, 0);

	pmem_mem = malloc(src_size);

	col bk; 
	bk.l = RGB_WITHE; //白色
	
	clr_src(bk); //清屏
}

// 在屏幕任意位置显示一个点
//
void show_point (int x, int y, col c)
{
	unsigned int *p = (void *)(psrc_mem + ((y * vinfo.xres_virtual + x) * 4));
	*p = c.l; 
} 
/*=========================================
 *显存和内存之间的数据拷贝
 *========================================*/
void copy_screen(rect m_rect, int direct)
{
	unsigned int *psrc, *pdst;
	int x, y;
	for (y = 0; y < m_rect.h; y++) {
		for (x = 0; x < m_rect.w; x++) {
			if (direct == 0) {
				psrc = (void *)(psrc_mem + (((y + m_rect.y) * vinfo.xres_virtual + m_rect.x + x ) * 4));
				pdst = (void *)(pmem_mem + (((y + m_rect.y) * vinfo.xres_virtual + m_rect.x + x ) * 4));
				*pdst = *psrc;
			} else {
				psrc = (void *)(pmem_mem + (((y + m_rect.y) * vinfo.xres_virtual + m_rect.x + x ) * 4));
				pdst = (void *)(psrc_mem + (((y + m_rect.y) * vinfo.xres_virtual + m_rect.x + x ) * 4));
				*pdst = *psrc;
			}
		}
	}
}


/*
 * 在屏上横线
 */
void draw_h_line (int x0, int y0, int width, col c)
{
	int i;
	for (i = 0; i < width; i++) 
		show_point (x0 + i, y0, c);
}


/*
 * 填充矩形
 */
void fill_rect(int x0, int y0, int width, int height, col c)
{
	int i;

	if (c.l == RGB_TRANS) //若填充颜色为透明色，则直接返回
		return ;

	for (i = 0; i < height; i++)
		draw_h_line(x0, y0 + i, width, c);
}

/*
 * 清屏
 */
void clr_src(col c)
{
	fill_rect(0, 0, vinfo.xres, vinfo.yres, c);
}

//=======================================================
//图片显示模块
//=======================================================
//load_bmp 为从硬盘加载一个图片---将图片信息加在到内存 
tag_bmp *load_bmp(char *filename)
{
	BITMAPFILEHEADER head;
	BITMAPINFOHEADER info;
		
	//打开位图
	int bmp_fd = open (filename, O_RDONLY);
	if (-1 == bmp_fd) {
		return NULL;
	}
	
	read (bmp_fd, &head, sizeof(head));// 读图片文件头信息
	read (bmp_fd, &info, sizeof(info));// 读图片图像信息
	
	tag_bmp *p = malloc(sizeof(tag_bmp));
	p->width = info.biWidth;
	p->height = info.biHeight;
	p->data = malloc (p->width * p->height * 3); //分配数据空间
	read (bmp_fd, p->data, info.biWidth * info.biHeight * 3);
	
	close(bmp_fd);

	return p;
}

//show_bmp, 将加载的图片显示在屏幕上
void show_bmp(int x0, int y0, tag_bmp *p)
{
	int i, j;
	
	unsigned char *pdata = p->data;
	for (j = 0; j < p->height; j++) {
		for (i = 0; i < p->width; i ++) {
			//一次取一个点
			col c;
			c.rgb.b = *pdata++;
			c.rgb.g = *pdata++;
			c.rgb.r = *pdata++;
			show_point(x0 + i, p->height - j + y0, c);
		}
	}
}

//释放图片资源
void free_bmp(tag_bmp *p)
{
	free (p->data);
	free (p);
}

