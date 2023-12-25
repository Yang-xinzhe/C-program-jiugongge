#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "show.h"
#include "bmp.h"
#include "getch.h"

void shuffle(tag_bmp *array[], int size)
{
	srand(time(NULL)); // 初始化随机数生成器
	for (int i = size - 2; i > 0; i--)
	{
		int j = rand() % (i + 1); // 生成一个随机索引
		// 交换元素
		tag_bmp *temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}

int checkWinCondition(tag_bmp *current[], tag_bmp *correct[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (current[i] != correct[i])
		{
			return 0; // 还未成功
		}
	}
	return 1; // 游戏成功结束
}

int main(int argc, const char *argv[])
{

    //1.framebuffer 初始化 
    screen_info info;
    fb_init(&info);

    //2.加载图片信息 从 硬盘 到 内存 
    char* fileNames[] = {"./pic/1.bmp", "./pic/2.bmp", "./pic/3.bmp", "./pic/4.bmp", "./pic/5.bmp","./pic/6.bmp","./pic/7.bmp","./pic/8.bmp","./pic/9.bmp"};
	// tag_bmp *p = load_bmp("./pic/01.bmp");
    int i;
    tag_bmp *bmpArray[9];
	tag_bmp *correctOrderArray[9];
	tag_bmp *Success = load_bmp("./pic/success.bmp");
	int size = sizeof(bmpArray) / sizeof(bmpArray[0]);
	for (int i = 0; i < 9; ++i)
	{
		bmpArray[i] = load_bmp(fileNames[i]); // 使用不同的文件路径
		if (bmpArray[i] == NULL)
		{
			printf("Failed to load BMP file: %s\n", fileNames[i]);
		}
		correctOrderArray[i] = bmpArray[i];
	}

	// 3.将图片显示
	int x_positions[] = {0, 200, 400, 0, 200, 400, 0, 200, 400};
	int y_positions[] = {0, 0, 0, 200, 200, 200, 400, 400, 400};
	int emptyIndex = 8;
	//shuffle(bmpArray, 9);
	for (int i = 0; i < 9; ++i)
	{
		show_bmp(x_positions[i], y_positions[i], bmpArray[i]);
	}
	while (1)
	{
		char key = getch(); // 获取键盘输入

		int moveIndex = -1; // 将要移动的图片索引

		// 根据按键决定移动哪张图片
		if (key == 'w' && emptyIndex >= 3)
		{ // 向上移动
			moveIndex = emptyIndex - 3;
		}
		else if (key == 's' && emptyIndex < 6)
		{ // 向下移动
			moveIndex = emptyIndex + 3;
		}
		else if (key == 'a' && emptyIndex % 3 > 0)
		{ // 向左移动
			moveIndex = emptyIndex - 1;
		}
		else if (key == 'd' && emptyIndex % 3 < 2)
		{ // 向右移动
			moveIndex = emptyIndex + 1;
		}

		// 如果有有效的移动
		if (moveIndex != -1)
		{
			// 交换空格和选中图片的位置
			tag_bmp *temp = bmpArray[emptyIndex];
			bmpArray[emptyIndex] = bmpArray[moveIndex];
			bmpArray[moveIndex] = temp;

			// 更新空格索引
			emptyIndex = moveIndex;

			// 重新显示九宫格
			for (int i = 0; i < 9; ++i)
			{
				show_bmp(x_positions[i], y_positions[i], bmpArray[i]);
			}
			if (checkWinCondition(bmpArray, correctOrderArray, 9))
			{
				show_bmp(0, 0,Success);
				//break; // 退出循环
			}
		}
	}

	return 0;
}
