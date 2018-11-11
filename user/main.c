#include <stdio.h>
#include <string.h>
#include "rtdef.h"
#include "rtthread.h"
#include "rtservice.h"
#include "rtconfig.h"

rt_uint8_t flag1;
rt_uint8_t flag2;

struct rt_thread rt_flag1_thread;
struct rt_thread rt_flag2_thread;

rt_uint8_t rt_flag1_thread_stack[512];
rt_uint8_t rt_flag2_thread_stack[512];
extern  rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];

void delay(rt_uint32_t count)
{
	for(; count!=0; count--);
}

/* 线程1 */
void flag1_thread_entry(void *p_arg)
{
	for(;;)
	{
			flag1 = 1;
			delay(100);
			flag1 = 0 ;
		  delay(100);
		
		 /* 线程切换， 这里是手动切换 */
		 rt_schedule();
		
	}
	
}

/* 线程1 */
void flag2_thread_entry(void *p_arg)
{
	for(;;)
	{
			flag2 = 1;
			delay(100);
			flag2 = 0 ;
		  delay(100);
		
		  /* 线程切换， 这里是手动切换 */
		 rt_schedule();
		
	}
}
int main(void)
{
	
	
	/* 调度器初始化 */
	rt_system_scheduler_init();

	/* 初始化线程 */
	rt_thread_init(&rt_flag1_thread, 											/* 线程控制块 */
									flag1_thread_entry, 									/* 线程入口地址 */
									RT_NULL, 															/* 线程形参 */
									&rt_flag1_thread_stack[0], 						/* 线程栈起始地址 */
									sizeof(rt_flag1_thread_stack));				/* 线程栈大小，单位为字节 */
	
	/* 将线程插入到就绪表 */
	rt_list_insert_before(&(rt_thread_priority_table[0]), &(rt_flag1_thread.tlist));
	
	/* 初始化线程 */	
	rt_thread_init(&rt_flag2_thread, 											/* 线程控制块 */
									flag2_thread_entry, 									/* 线程入口地址 */
									RT_NULL, 															/* 线程形参 */
									&rt_flag2_thread_stack[0], 						/* 线程栈起始地址 */
									sizeof(rt_flag2_thread_stack));				/* 线程栈大小，单位为字节 */
	
	/* 将线程插入到就绪表 */
	rt_list_insert_before(&(rt_thread_priority_table[1]), &(rt_flag2_thread.tlist));
	
	/* 启动系统调度器 */
	rt_system_scheduler_start();
	
	
}

