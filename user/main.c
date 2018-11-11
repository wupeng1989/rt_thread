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

/* �߳�1 */
void flag1_thread_entry(void *p_arg)
{
	for(;;)
	{
			flag1 = 1;
			delay(100);
			flag1 = 0 ;
		  delay(100);
		
		 /* �߳��л��� �������ֶ��л� */
		 rt_schedule();
		
	}
	
}

/* �߳�1 */
void flag2_thread_entry(void *p_arg)
{
	for(;;)
	{
			flag2 = 1;
			delay(100);
			flag2 = 0 ;
		  delay(100);
		
		  /* �߳��л��� �������ֶ��л� */
		 rt_schedule();
		
	}
}
int main(void)
{
	
	
	/* ��������ʼ�� */
	rt_system_scheduler_init();

	/* ��ʼ���߳� */
	rt_thread_init(&rt_flag1_thread, 											/* �߳̿��ƿ� */
									flag1_thread_entry, 									/* �߳���ڵ�ַ */
									RT_NULL, 															/* �߳��β� */
									&rt_flag1_thread_stack[0], 						/* �߳�ջ��ʼ��ַ */
									sizeof(rt_flag1_thread_stack));				/* �߳�ջ��С����λΪ�ֽ� */
	
	/* ���̲߳��뵽������ */
	rt_list_insert_before(&(rt_thread_priority_table[0]), &(rt_flag1_thread.tlist));
	
	/* ��ʼ���߳� */	
	rt_thread_init(&rt_flag2_thread, 											/* �߳̿��ƿ� */
									flag2_thread_entry, 									/* �߳���ڵ�ַ */
									RT_NULL, 															/* �߳��β� */
									&rt_flag2_thread_stack[0], 						/* �߳�ջ��ʼ��ַ */
									sizeof(rt_flag2_thread_stack));				/* �߳�ջ��С����λΪ�ֽ� */
	
	/* ���̲߳��뵽������ */
	rt_list_insert_before(&(rt_thread_priority_table[1]), &(rt_flag2_thread.tlist));
	
	/* ����ϵͳ������ */
	rt_system_scheduler_start();
	
	
}

