#ifndef __SHOW_H
#define __SHOW_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "bmp.h"
#include <sys/ioctl.h>

#define PI 3.1415926

//=================================
//像素颜色相关的结构体定义和宏定义
//=================================
#define RGB_WITHE	0x00ffffff
#define RGB_BLACK	0x00000000
#define RGB_TRANS	0xff000000     //定义透明色

struct tag_rgb {
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char null;
};

typedef union {
	struct tag_rgb rgb;
	unsigned int l;
} col;

//===================================
//坐标
//===================================
typedef struct {
	int x;
	int y;
} point;

//===================================
//矩形
//===================================
typedef struct {
	int x;
	int y;
	int w;
	int h;
}rect;

//===================================
//图标
//===================================
#define ICON_WIDTH	100
#define ICON_HEIGHT 128

typedef struct tag_icon {
	int type;
	rect m_rect;			//图标所占的区域
	tag_bmp *pbmp;			//图标图片数据
	char name[256];			//图标显示的名字
	col f;					//图标字体
	col bk;					//背景色
	struct tag_icon *next;	//单向链表
} icon;


#define FONT_HEIGHT	28
#define FONT_WIDTH_PER_BYTE 8

//===================================
//===================================
typedef struct {
	int w;
	int h;
	int bits_per_pixel;
}screen_info;

void clr_src(col c);

void fb_init(screen_info *info);
void show_bmp(int x0, int y0, tag_bmp *p);
#endif
