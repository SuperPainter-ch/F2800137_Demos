#include "f28x_project.h"

/* 全局变量定义 */
int i = 0;              /* 计数变量，用于生成数据序列 */
int ScopeBuf[100] = {0}; /* 示波器缓冲区，存储100个数据样本 */
int ScopeCnt = 0;       /* 示波器缓冲区写入计数器 */

/*
 * main.c
 * Demo00_Graph 工程主文件
 * 功能：初始化系统，生成数据序列并存入缓冲区，用于示波器观测
 */
int main(void)
{
    /* 初始化系统时钟和外设 */
    InitSysCtrl();

    /* 初始化外设（如有需要在此添加） */





    /* 初始化外设（如有需要在此添加） */

    /* 初始化PIE控制器，禁用CPU中断 */
    DINT;              /* Disable CPU Interrupts: 禁用CPU中断 */
    InitPieCtrl();     /* 初始化PIE（外设中断扩展器）控制器 */
    IER = 0x0000;      /* 清除中断使能寄存器 */
    IFR = 0x0000;      /* 清除中断标志寄存器 */

    /* 
     * 初始化PIE向量表，将中断处理函数指针加载到对应位置
     * （如果有中断需要，这里会设置ISR函数指针）
     */
    InitPieVectTable();

    /* 使能全局中断(INTM)和实时中断(DBGM) */
    EINT;              /* Enable Global Interrupt: 使能全局中断 */
    ERTM;              /* Enable Real Time Interrupt: 使能实时中断 */

    /* 主循环：永久循环 */
    for(;;)
    {
        /* 将数据写入示波器缓冲区 */
        ScopeBuf[ScopeCnt] = i;

        /* 递增计数变量，每次增加2 */
        i += 2;

        /* 示波器缓冲区指针后移 */
        ScopeCnt++;

        /* 
         * 当计数变量i达到200时，重置为0
         * 实现周期性数据生成（0, 2, 4, ..., 198, 0, 2, ...）
         */
        if(i == 200){
            i = 0;
        }

        /* 
         * 当缓冲区写入计数器达到100时，重置为0
         * 缓冲区满后自动循环，便于观测
         */
        if(ScopeCnt == 100){
            ScopeCnt = 0;
        }

        /* 延迟10000微秒（10毫秒），控制数据采样速率 */
        DELAY_US(10000);
    }

}
