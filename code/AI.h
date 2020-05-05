#ifndef AI_H
#define AI_H

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include<time.h>
#include <string.h>
using namespace std;

//定义单个火柴数位变化标志
#define FLAG_KEEP     0      //不移动
#define FLAG_MINUS   10      //减一根火柴
#define FLAG_ADD    100      //加一根火柴
#define FLAG_SELF  1000      //拿一根放到自身其他地方

//定义合法移动（六个火柴数位）
#define MOVE_TO_ANOTHER 110   // 10 + 100 + 0*4，从一个火柴数位拿一根，放到另一个火柴数位上
#define MOVE_TO_SELF    1000  // 1000 + 0*5，自己拿一根放自己身上其他位置
#define MOVE_FROM_PLUS  100   // 100 + 0*5，从加号上拿一根放一个数身上
#define MOVE_TO_MINUS   10    // 10+0*5,从一个火柴数位拿一根，放到减号上

//定义移动火柴后的等式状态
#define SYMBOL_ERROR    0    //非法移动
#define SYMBOL_ADD      1    //不从加号取火柴||从一个火柴数位取火柴给到减号
#define SYMBOL_MINUS    2    //不从减号取火柴||从加号取火柴给到一个火柴数位
#define SYMBOL_MUTIPLE  3    //不从乘号取火柴

char SCANF_SIGNAL;  //由玩家输入'+','-','*'
int mode;//游戏模式，设成全局变量，以便共享
char checkSignal;
int* output=new int [6];
char signal_output[4];

//定义火柴数位结构体
struct MATCH_NUM
{
public:
    int matchflag;
    int matchdata;
};

//定义状态空间，并返回状态个数
int GetnumAfterMove(int number, MATCH_NUM* afterMatch)
{
    int StateCount = 0;
    switch (number)
    {
    case 0:
    {
        afterMatch[0].matchflag = FLAG_KEEP; afterMatch[0].matchdata = 0;
        afterMatch[1].matchflag = FLAG_ADD; afterMatch[1].matchdata = 8;
        afterMatch[2].matchflag = FLAG_SELF; afterMatch[2].matchdata = 6;
        afterMatch[3].matchflag = FLAG_SELF; afterMatch[3].matchdata = 9;
        StateCount = 4;
        break;
    }

    case 1:
    {
        afterMatch[0].matchflag = FLAG_KEEP; afterMatch[0].matchdata = 1;
        afterMatch[1].matchflag = FLAG_ADD; afterMatch[1].matchdata = 7;
        StateCount = 2;
        break;
    }

    case 2:
    {
        afterMatch[0].matchflag = FLAG_KEEP; afterMatch[0].matchdata = 2;
        afterMatch[1].matchflag = FLAG_SELF; afterMatch[1].matchdata = 3;
        StateCount = 2;
        break;
    }

    case 3:
    {
        afterMatch[0].matchflag = FLAG_KEEP; afterMatch[0].matchdata = 3;
        afterMatch[1].matchflag = FLAG_ADD; afterMatch[1].matchdata = 9;
        afterMatch[2].matchflag = FLAG_SELF; afterMatch[2].matchdata = 2;
        afterMatch[3].matchflag = FLAG_SELF; afterMatch[3].matchdata = 5;
        StateCount = 4;
        break;
    }

    case 4:
    {
        afterMatch[0].matchflag = FLAG_KEEP; afterMatch[0].matchdata = 4;
        StateCount = 1;
        break;
    }

    case 5:
    {
        afterMatch[0].matchflag = FLAG_KEEP; afterMatch[0].matchdata = 5;
        afterMatch[1].matchflag = FLAG_ADD; afterMatch[1].matchdata = 6;
        afterMatch[2].matchflag = FLAG_ADD; afterMatch[2].matchdata = 9;
        afterMatch[3].matchflag = FLAG_SELF; afterMatch[3].matchdata = 3;
        StateCount = 4;
        break;
    }

    case 6:
    {
        afterMatch[0].matchflag = FLAG_KEEP; afterMatch[0].matchdata = 6;
        afterMatch[1].matchflag = FLAG_ADD; afterMatch[1].matchdata = 8;
        afterMatch[2].matchflag = FLAG_MINUS; afterMatch[2].matchdata = 5;
        afterMatch[3].matchflag = FLAG_SELF; afterMatch[3].matchdata = 0;
        afterMatch[4].matchflag = FLAG_SELF; afterMatch[4].matchdata = 9;
        StateCount = 5;
        break;
    }

    case 7:
    {
        afterMatch[0].matchflag = FLAG_KEEP; afterMatch[0].matchdata = 7;
        afterMatch[1].matchflag = FLAG_MINUS; afterMatch[1].matchdata = 1;
        StateCount = 2;
        break;
    }

    case 8:
    {
        afterMatch[0].matchflag = FLAG_KEEP; afterMatch[0].matchdata = 8;
        afterMatch[1].matchflag = FLAG_MINUS; afterMatch[1].matchdata = 6;
        afterMatch[2].matchflag = FLAG_MINUS; afterMatch[2].matchdata = 9;
        afterMatch[3].matchflag = FLAG_MINUS; afterMatch[3].matchdata = 0;
        StateCount = 4;
        break;
    }

    case 9:
    {
        afterMatch[0].matchflag = FLAG_KEEP; afterMatch[0].matchdata = 9;
        afterMatch[1].matchflag = FLAG_ADD; afterMatch[1].matchdata = 8;
        afterMatch[2].matchflag = FLAG_MINUS; afterMatch[2].matchdata = 3;
        afterMatch[3].matchflag = FLAG_SELF; afterMatch[3].matchdata = 6;
        afterMatch[4].matchflag = FLAG_MINUS; afterMatch[4].matchdata = 5;
        afterMatch[5].matchflag = FLAG_SELF; afterMatch[5].matchdata = 0;
        StateCount = 6;
        break;
    }
    default:
    {
        break;
    }

    }
    return StateCount;
}

//给出合法移动后的等式符号类型
char CheckMatchMove(int flag1, int flag2, int flag3, int flag4, int flag5, int flag6)
{
    char csymbol = SYMBOL_ERROR;
    int matchflagSum = flag1 + flag2 + flag3 + flag4 + flag5 + flag6;
    if (SCANF_SIGNAL == '+')
    {
        if (matchflagSum == MOVE_TO_ANOTHER)
            csymbol = SYMBOL_ADD;
        else if (matchflagSum == MOVE_TO_SELF)
            csymbol = SYMBOL_ADD;
        else if (matchflagSum == MOVE_FROM_PLUS)
            csymbol = SYMBOL_MINUS;
    }

    else if (SCANF_SIGNAL == '-')
    {
        if (matchflagSum == MOVE_TO_ANOTHER)
            csymbol = SYMBOL_MINUS;
        else if (matchflagSum == MOVE_TO_SELF)
            csymbol = SYMBOL_MINUS;
        else if (matchflagSum == MOVE_TO_MINUS)
            csymbol = SYMBOL_ADD;
    }

    else if (SCANF_SIGNAL == '*')
    {
        if (matchflagSum == MOVE_TO_ANOTHER)
            csymbol = SYMBOL_MUTIPLE;
        else if (matchflagSum == MOVE_TO_SELF)
            csymbol = SYMBOL_MUTIPLE;
    }
    return csymbol;
}

typedef  MATCH_NUM* M; //仅为了下面函数参数简洁


//输出满足移动规则且使得等式成立的式子
int printResult(M match1, M match2, M match3, M match4, M match5, M match6)
{

    int* data = new int[7];
    data[0]=0;
    int flag1 = match1->matchflag;    data[1] = match1->matchdata;
    int flag2 = match2->matchflag;    data[2]= match2->matchdata;
    int flag3 = match3->matchflag;    data[3] = match3->matchdata;
    int flag4 = match4->matchflag;    data[4] = match4->matchdata;
    int flag5 = match5->matchflag;    data[5] = match5->matchdata;
    int flag6 = match6->matchflag;    data[6] = match6->matchdata;

    char cSymbol = CheckMatchMove(flag1, flag2, flag3, flag4, flag5, flag6);
    if ((cSymbol == SYMBOL_ADD) && (data[1] * 10 + data[2] + data[3] * 10 + data[4] == data[5] * 10 + data[6]))
    {
        if (mode == 1)
        {
            output[0]=data[1]; output[1]=data[2]; output[2]=data[3]; output[3]=data[4]; output[4]=data[5]; output[5]=data[6];
            signal_output[0]='+';

        }
        checkSignal = '+';
        data[0]++;
    }
    else if ((cSymbol == SYMBOL_MINUS) && (data[1] * 10 + data[2] - data[3] * 10 - data[4] == data[5] * 10 + data[6]))
    {
        if (mode == 1)
        {
            output[0]=data[1]; output[1]=data[2]; output[2]=data[3]; output[3]=data[4]; output[4]=data[5]; output[5]=data[6];
            signal_output[0]='-';
        }
        checkSignal = '-';
        data[0]++;
    }
    else if ((cSymbol == SYMBOL_MUTIPLE) && ((data[1] * 10 + data[2]) * (data[3] * 10 + data[4]) == data[5] * 10 + data[6]))
    {
        if (mode == 1)
        {
            output[0]=data[1]; output[1]=data[2]; output[2]=data[3]; output[3]=data[4]; output[4]=data[5]; output[5]=data[6];
            signal_output[0]='x';
        }
        checkSignal = '*';
        data[0]++;
    }
    else
        data[0]--;
    return data[0];
}

//开始游戏，函数内部不断遍历搜索
bool play(int data1, int data2, int data3, int data4, int data5, int data6)
{
    int COUNT=0;
    //六重循环 （本题搜索空间较小，最多10^6次运算,在statecount限制下会更小,故可行）
    int loop1, loop2, loop3, loop4, loop5, loop6;

    MATCH_NUM matchStick1[10];
    MATCH_NUM matchStick2[10];
    MATCH_NUM matchStick3[10];
    MATCH_NUM matchStick4[10];
    MATCH_NUM matchStick5[10];
    MATCH_NUM matchStick6[10];

    int StateCount1 = GetnumAfterMove(data1, matchStick1);
    int StateCount2 = GetnumAfterMove(data2, matchStick2);
    int StateCount3 = GetnumAfterMove(data3, matchStick3);
    int StateCount4 = GetnumAfterMove(data4, matchStick4);
    int StateCount5 = GetnumAfterMove(data5, matchStick5);
    int StateCount6 = GetnumAfterMove(data6, matchStick6);

    for (loop1 = 0; loop1 < StateCount1; loop1++)
    {
        for (loop2 = 0; loop2 < StateCount2; loop2++)
        {
            for (loop3 = 0; loop3 < StateCount3; loop3++)
            {
                for (loop4 = 0; loop4 < StateCount4; loop4++)
                {
                    for (loop5 = 0; loop5 < StateCount5; loop5++)
                    {
                        for (loop6 = 0; loop6 < StateCount6; loop6++)
                        {
                           COUNT+= printResult(&matchStick1[loop1], &matchStick2[loop2], &matchStick3[loop3],
                                &matchStick4[loop4], &matchStick5[loop5], &matchStick6[loop6]);
                        }
                    }
                }
            }
        }
    }

    if ((COUNT== -StateCount1 * StateCount2 * StateCount3 * StateCount4 * StateCount5 * StateCount6))
        return false;
    else
        return true;
}


MATCH_NUM* move(int* num, MATCH_NUM* matchstick[6])
{
    int* a = new int[6];
    matchstick[6] = new MATCH_NUM[6]; //6行6列
    for ( int i = 0; i < 6; i++)
    {
        matchstick[i][0].matchdata = num[i];
        for ( int j = 0; j < GetnumAfterMove(num[i], matchstick[i]); j++)
        {
            a[i]= GetnumAfterMove(num[i], matchstick[i]);
        }
    }
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < GetnumAfterMove(num[i], matchstick[i]); j++)
        {
            for (int z = 1; z < 36; z++)
            {
                switch(matchstick[i][j].matchflag+matchstick[(i+(j+z)/a[i])%6][(j+z)%a[i]].matchflag)
                    case MOVE_TO_ANOTHER:
                        matchstick[i][0].matchdata = matchstick[i][j].matchdata;
                        matchstick[(i + (j + z) / a[i]) % 6][0].matchdata = matchstick[(i + (j + z) / a[i]) % 6][(j + z) % a[i]].matchdata;
                        break;
                        return matchstick[6];


            }
        }
    }


}

#endif // AI_H
