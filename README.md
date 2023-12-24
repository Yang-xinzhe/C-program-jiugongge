```
gcc main.c show.c getch.c
```
```
sudo ./a.out
```
# 图片读取
<img width="683" alt="image" src="https://github.com/Yang-xinzhe/C-program-jiugongge/assets/77601178/250b5486-05ab-40e9-8616-6449c45385ce">

使用字符串数组将文件夹下的图片文件名信息保存  
使用指针数组保存bmp图片信息 并将图片读取到数组中  
同时将正确位置的图片所对应的数组下标索引保存进另一个数组 在判断是否完成拼图时会用做判断  

# 位置显示  
<img width="387" alt="image" src="https://github.com/Yang-xinzhe/C-program-jiugongge/assets/77601178/1187fbae-36dd-44ae-8d7a-65cde061723c">

位置的显示与提供的bmp_show函数有关 bmp_show()在show.c文件中定义：  
```C
void show_bmp(int x0, int y0, tag_bmp *p)  
```
由于bmp_show函数中的前两个参数是代表的打印的x轴位置和y轴位置 我选择人工把图片位置排好  
将想要显示的九宫格效果按照在屏幕上打印的位置写进数组（当然我知道这样显得很笨）  
使用循环将图片打印在屏幕上  
# 循环判断  
<img width="446" alt="image" src="https://github.com/Yang-xinzhe/C-program-jiugongge/assets/77601178/7348c784-1629-4b54-86b4-9aee1cdf7b5c">

一开始我是想使用switch的 但是在switch中每个case都要添加判断条件 不然动一下就会报段错误 我还半天debug不出来 后来发现用else if比switch能少写两行而且能在读字符的时候就加判断条件  
# 游戏结束
当每个图片都对应上最开始的位置 就使用bmp_show函数打印一个完成的图片
# 改进的空间
在进while(1)循环的时候我选择的是数组下标为8所对应的图片 在最初的排列中下标为8的图片是一个空白图片 在游戏中应该移动的也是这个空白图片 但是我在进入游戏的时候加入了打乱图片顺序的功能 导致第8位（也就是九宫格最右下角的那张图）不一定是空白图片 但是每次操作的只能是那张图片

位置的显示会不会用二维数组显示会更直观一点 用两个一维数组有些抽象

计时的功能想了一下 感觉有点难 直接放弃
