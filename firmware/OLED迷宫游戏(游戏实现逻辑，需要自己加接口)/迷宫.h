#ifndef __MG_H
#define __MG_H

//调用方法：mg_play(14,24,2);

//最大迷宫宽高，是地图块的大小（地图复杂度），不是屏幕大小
#define MG_W 32
#define MG_H 64
typedef struct
{
    uint8_t msg[5];
}mg_gird;

extern __IO mg_gird MapMain[MG_W][MG_H];

int randint(int p1,int p2);
void Recursive_division(int left, int right, int top, int bottom);
void test_mg(uint16_t x,uint16_t y,uint16_t wid,uint16_t size_x,uint16_t size_y);
void play_cur(uint16_t x,uint16_t y,uint16_t w)
void mg_play(uint8_t w,uint8_t h,uint8_t wi);

#endif

