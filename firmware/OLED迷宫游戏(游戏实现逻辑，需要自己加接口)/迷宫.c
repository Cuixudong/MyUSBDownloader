//记得添加头文件

/*
程序所需接口：
HAL_GetTick();获取系统计时用于处理坐标闪烁等
OLED_Fill(x1,y1,x2,y2,color);用以绘制方块组成迷宫
OLED_DrawPoint(x1,y1,color);用以绘制最细线的迷宫墙壁
OLED_Clear(color);清屏，不显示
OLED_Refresh_Gram();刷新显示，在这之前oled不显示任何图案，即整帧绘制
MPU_Get_Accelerometer(*x,*y,*z);获取三轴加速度来移动目标点走出 迷宫
TPAD_Scan(0);触摸按键用以返回或重新开始，可以用其他获取点击方法替代
HAL_Delay(t);延时
Show_String(x,y,w,h,str,font,color);显示字符串
*/

//硬件随机数用以迷宫的随机生成
int randint(int p1,int p2)
{
    int t;
    if(p2 > p1)
    {
        t = (RNG_Get_RandomNum() % (p2 - p1)) + p1;
    }
    else if(p1 > p2)
    {
        t = (RNG_Get_RandomNum() % (p1 - p2)) + p2;
    }
    else
    {
        t = p1;
    }
    return t;
}

//存储迷宫的矩阵
__IO mg_gird MapMain[MG_W][MG_H];
//迷宫生成算法，障碍保存到迷宫矩阵中
void Recursive_division(int left, int right, int top, int bottom)
{
    int rand_x,rand_y,rand_yt,rand_yb,rand_xl,rand_xr,direct;
    if ((left < right) && (top < bottom))
    {
        rand_x = randint(left, right-1);
        rand_y = randint(top, bottom-1);
        rand_yt = randint(top,rand_y);
        rand_yb = randint(rand_y+1,bottom);
        rand_xl = randint(left,rand_x);
        rand_xr = randint(rand_x+1,right);
        direct = randint(1,4);
        if (direct == 1)
        {
            MapMain[rand_xr][rand_y].msg[2] = 1;
            MapMain[rand_xr][rand_y+1].msg[0] = 1;
            MapMain[rand_x][rand_yt].msg[3] = 1;
            MapMain[rand_x+1][rand_yt].msg[1] = 1;
            MapMain[rand_x][rand_yb].msg[3] = 1;
            MapMain[rand_x+1][rand_yb].msg[1] = 1;
        }
        else if (direct == 2)
        {
            MapMain[rand_xl][rand_y].msg[2] = 1;
            MapMain[rand_xl][rand_y+1].msg[0] = 1;
            MapMain[rand_x][rand_yt].msg[3] = 1;
            MapMain[rand_x+1][rand_yt].msg[1] = 1;
            MapMain[rand_x][rand_yb].msg[3] = 1;
            MapMain[rand_x+1][rand_yb].msg[1] = 1;
        }
        else if (direct == 3)
        {
            MapMain[rand_xl][rand_y].msg[2] = 1;
            MapMain[rand_xl][rand_y+1].msg[0] = 1;
            MapMain[rand_xr][rand_y].msg[2] = 1;
            MapMain[rand_xr][rand_y+1].msg[0] = 1;
            MapMain[rand_x][rand_yb].msg[3] = 1;
            MapMain[rand_x+1][rand_yb].msg[1] = 1;
        }
        else if (direct == 4)
        {
            MapMain[rand_xl][rand_y].msg[2] = 1;
            MapMain[rand_xl][rand_y+1].msg[0] = 1;
            MapMain[rand_xr][rand_y].msg[2] = 1;
            MapMain[rand_xr][rand_y+1].msg[0] = 1;
            MapMain[rand_x][rand_yt].msg[3] = 1;
            MapMain[rand_x+1][rand_yt].msg[1] = 1;
        }
        Recursive_division(left, rand_x, top, rand_y);
        Recursive_division(left, rand_x, rand_y+1, bottom);
        Recursive_division(rand_x+1, right, rand_y+1, bottom);
        Recursive_division(rand_x+1, right, top, rand_y);
    }
    else if(left < right)
    {
        rand_x = randint(left, right-1);
        MapMain[rand_x][top].msg[3] = 1;
        MapMain[rand_x+1][top].msg[1] = 1;
        Recursive_division(left, rand_x, top, top);
        Recursive_division(rand_x+1, right, top, top);
    }
    else if(top < bottom)
    {
        rand_y = randint(top,bottom-1);
        MapMain[left][rand_y].msg[2] = 1;
        MapMain[left][rand_y+1].msg[0] = 1;
        Recursive_division(left, left, top, rand_y);
        Recursive_division(left, left, rand_y+1, bottom);
    }
}
//绘制迷宫地图
void test_mg(uint16_t x,uint16_t y,uint16_t wid,uint16_t size_x,uint16_t size_y)
{
    int pppp,jjjj;
    
    memset((void *)MapMain,0,sizeof(MapMain));
    
    Recursive_division(0,size_y-1,0,size_x-1);
    MapMain[0][0].msg[0] = 1;
    MapMain[size_y-1][size_x-1].msg[2] = 1;
    
    if(wid<1)wid = 1;
    
    int pi_w = 4 * wid;
    int pi_h = 4 * wid;
    
    for(pppp=0;pppp<size_y;pppp++)
    {
        for(jjjj=0;jjjj<size_x;jjjj++)
        {
            OLED_Fill(jjjj * pi_w + x + 0 * wid,pppp * pi_h + y + 0 * wid,jjjj * pi_w + x + 1 * wid,pppp * pi_h + y + 1 * wid,1);
            OLED_Fill(jjjj * pi_w + x + 3 * wid,pppp * pi_h + y + 0 * wid,jjjj * pi_w + x + 4 * wid,pppp * pi_h + y + 1 * wid,1);
            OLED_Fill(jjjj * pi_w + x + 0 * wid,pppp * pi_h + y + 3 * wid,jjjj * pi_w + x + 1 * wid,pppp * pi_h + y + 4 * wid,1);
            OLED_Fill(jjjj * pi_w + x + 3 * wid,pppp * pi_h + y + 3 * wid,jjjj * pi_w + x + 4 * wid,pppp * pi_h + y + 4 * wid,1);
            if(MapMain[pppp][jjjj].msg[0] == 0)
            {
                OLED_Fill(jjjj * pi_w + x + 0 * wid,pppp * pi_h + y + 1 * wid,jjjj * pi_w + x + 1 * wid,pppp * pi_h + y + 3 * wid,1);
            }
            if(MapMain[pppp][jjjj].msg[1] == 0)
            {
                OLED_Fill(jjjj * pi_w + x + 1 * wid,pppp * pi_h + y + 0 * wid,jjjj * pi_w + x + 3 * wid,pppp * pi_h + y + 1 * wid,1);
            }
            if(MapMain[pppp][jjjj].msg[2] == 0)
            {
                OLED_Fill(jjjj * pi_w + x + 3 * wid,pppp * pi_h + y + 1 * wid,jjjj * pi_w + x + 4 * wid,pppp * pi_h + y + 3 * wid,1);
            }
            if(MapMain[pppp][jjjj].msg[3] == 0)
            {
                OLED_Fill(jjjj * pi_w + x + 1 * wid,pppp * pi_h + y + 3 * wid,jjjj * pi_w + x + 3 * wid,pppp * pi_h + y + 4 * wid,1);
            }
        }
    }
}
//绘制走迷宫当前位置的标记，旋转闪烁的点
void play_cur(uint16_t x,uint16_t y,uint16_t w)
{
    static uint16_t old_x = 0,old_y = 0;
    OLED_Fill(old_x * w * 4 + w ,old_y * w * 4 + w ,\
              old_x * w * 4 + 3 * w ,old_y * w * 4 + 3 * w ,0);
    switch((HAL_GetTick() % 1000) / 250)
    {
        case 0:
        {
            if(w <= 1)
            {
                OLED_DrawPoint(x * w * 4 + w ,y * w * 4 + w ,1);
                OLED_DrawPoint(x * w * 4 + w + 1 ,y * w * 4 + w ,1);
                //OLED_DrawPoint(x * w * 4 + w ,y * w * 4 + w + 1,1);
                OLED_DrawPoint(x * w * 4 + w + 1 ,y * w * 4 + w + 1,1);
            }
            else
            {
                OLED_Fill(x * w * 4 + 1 * w ,y * w * 4 + 1 * w ,\
                          x * w * 4 + 2 * w ,y * w * 4 + 2 * w ,1);
                OLED_Fill(x * w * 4 + 2 * w ,y * w * 4 + 1 * w ,\
                          x * w * 4 + 3 * w ,y * w * 4 + 2 * w ,1);
//                OLED_Fill(x * w * 4 + 1 * w ,y * w * 4 + 2 * w ,\
//                          x * w * 4 + 2 * w ,y * w * 4 + 3 * w ,1);
                OLED_Fill(x * w * 4 + 2 * w ,y * w * 4 + 2 * w ,\
                          x * w * 4 + 3 * w ,y * w * 4 + 3 * w ,1);
            }
        }
            break;
        case 1:
        {
            if(w <= 1)
            {
                //OLED_DrawPoint(x * w * 4 + w ,y * w * 4 + w ,1);
                OLED_DrawPoint(x * w * 4 + w + 1 ,y * w * 4 + w ,1);
                OLED_DrawPoint(x * w * 4 + w ,y * w * 4 + w + 1,1);
                OLED_DrawPoint(x * w * 4 + w + 1 ,y * w * 4 + w + 1,1);
            }
            else
            {
//                OLED_Fill(x * w * 4 + 1 * w ,y * w * 4 + 1 * w ,\
//                          x * w * 4 + 2 * w ,y * w * 4 + 2 * w ,1);
                OLED_Fill(x * w * 4 + 2 * w ,y * w * 4 + 1 * w ,\
                          x * w * 4 + 3 * w ,y * w * 4 + 2 * w ,1);
                OLED_Fill(x * w * 4 + 1 * w ,y * w * 4 + 2 * w ,\
                          x * w * 4 + 2 * w ,y * w * 4 + 3 * w ,1);
                OLED_Fill(x * w * 4 + 2 * w ,y * w * 4 + 2 * w ,\
                          x * w * 4 + 3 * w ,y * w * 4 + 3 * w ,1);
            }
        }
            break;
        case 2:
        {
            if(w <= 1)
            {
                OLED_DrawPoint(x * w * 4 + w ,y * w * 4 + w ,1);
                //OLED_DrawPoint(x * w * 4 + w + 1 ,y * w * 4 + w ,1);
                OLED_DrawPoint(x * w * 4 + w ,y * w * 4 + w + 1,1);
                OLED_DrawPoint(x * w * 4 + w + 1 ,y * w * 4 + w + 1,1);
            }
            else
            {
                OLED_Fill(x * w * 4 + 1 * w ,y * w * 4 + 1 * w ,\
                          x * w * 4 + 2 * w ,y * w * 4 + 2 * w ,1);
//                OLED_Fill(x * w * 4 + 2 * w ,y * w * 4 + 1 * w ,\
//                          x * w * 4 + 3 * w ,y * w * 4 + 2 * w ,1);
                OLED_Fill(x * w * 4 + 1 * w ,y * w * 4 + 2 * w ,\
                          x * w * 4 + 2 * w ,y * w * 4 + 3 * w ,1);
                OLED_Fill(x * w * 4 + 2 * w ,y * w * 4 + 2 * w ,\
                          x * w * 4 + 3 * w ,y * w * 4 + 3 * w ,1);
            }
        }
            break;
        case 3:
        {
            if(w <= 1)
            {
                OLED_DrawPoint(x * w * 4 + w ,y * w * 4 + w ,1);
                OLED_DrawPoint(x * w * 4 + w + 1 ,y * w * 4 + w ,1);
                OLED_DrawPoint(x * w * 4 + w ,y * w * 4 + w + 1,1);
                //OLED_DrawPoint(x * w * 4 + w + 1 ,y * w * 4 + w + 1,1);
            }
            else
            {
                OLED_Fill(x * w * 4 + 1 * w ,y * w * 4 + 1 * w ,\
                          x * w * 4 + 2 * w ,y * w * 4 + 2 * w ,1);
                OLED_Fill(x * w * 4 + 2 * w ,y * w * 4 + 1 * w ,\
                          x * w * 4 + 3 * w ,y * w * 4 + 2 * w ,1);
                OLED_Fill(x * w * 4 + 1 * w ,y * w * 4 + 2 * w ,\
                          x * w * 4 + 2 * w ,y * w * 4 + 3 * w ,1);
//                OLED_Fill(x * w * 4 + 2 * w ,y * w * 4 + 2 * w ,\
//                          x * w * 4 + 3 * w ,y * w * 4 + 3 * w ,1);
            }
        }
            break;
    }
    old_x = x;
    old_y = y;
}
//迷宫游戏逻辑
void mg_play(uint8_t w,uint8_t h,uint8_t wi)
{
    OLED_Clear(0);
    test_mg(0,0,wi,w,h);
    OLED_Refresh_Gram();
    short accx,accy,accz;       //加速度传感器原始数据
    uint8_t curx = 0,cury = 0;
    uint8_t touch_mod = 0;
    int mvx,mvy;
    int cnt = 0;
    while(1)
    {
        MPU_Get_Accelerometer(&accx,&accy,&accz);   //得到加速度传感器数据
        mvx = accx / 1400;
        mvy = -accy / 1400;
        if(TPAD_Scan(0) == 1)
        {
            touch_mod = !touch_mod;
        }
        if(touch_mod)
        {
            if((cnt % 3) == 0)
            {
                //EX_MOVE_POS(mvx,mvy);
            }
        }
        else
        {
            if((cnt % 30) == 0)
            {
                if(mvx > 0)
                if((curx > 0)
                    &&(MapMain[cury][curx].msg[0] == 1)
                //&&(MapMain[curx-1][cury].msg[2] == 1)
                )
                {
                    curx -= 1;
                }
                if(mvx < 0)
                if((curx < w-1)\
                    &&(MapMain[cury][curx].msg[2] == 1)
                //&&(MapMain[curx+1][cury].msg[0] == 1)
                )
                {
                    curx += 1;
                }
                if(mvy > 0)
                if((cury > 0)\
                    &&(MapMain[cury][curx].msg[1] == 1)
                //&&(MapMain[curx][cury-1].msg[3] == 1)
                )
                {
                    cury -= 1;
                }
                if(mvy < 0)
                if((cury < h-1)\
                    &&(MapMain[cury][curx].msg[3] == 1)
                //&&(MapMain[curx][cury+1].msg[1] == 1)
                )
                {
                    cury += 1;
                }
            }
        }
        cnt ++;
        HAL_Delay(5);
        play_cur(curx,cury,wi);
        OLED_Refresh_Gram();
        if((curx == (w-1))&&(cury == (h-1)))
        {
            Show_String(16+OLED_CUR_POS_X,16+OLED_CUR_POS_Y,128,64,"恭喜你过关，",16,1);
            Show_String(16+OLED_CUR_POS_X,32+OLED_CUR_POS_Y,128,64,"触摸按键继续",16,1);
            OLED_Refresh_Gram();
            while(1)
            {
                if(TPAD_Scan(0) == 1)
                {
                    OLED_Clear(0);
                    test_mg(0,0,wi,w,h);
                    OLED_Refresh_Gram();
                    curx = 0,cury = 0;
                    break;
                }
            }
        }
    }
}

