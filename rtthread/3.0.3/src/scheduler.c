#include "rtdef.h"
#include "rtconfig.h"
#include "rtservice.h"
#include "rtthw.h"

struct rt_thread *rt_current_thread;

rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];

void rt_system_scheduler_init(void)
{
	register rt_base_t offset;
	
	/* 线程就绪列表初始化 */
	for(offset = 0; offset < RT_THREAD_PRIORITY_MAX; offset++)
	{
		rt_list_init(&rt_thread_priority_table[offset]);
	}
	
	/* 初始化当前线程控制块指针 */
	rt_current_thread = RT_NULL;
	
}


void rt_system_scheduler_start(void)
{
	register struct rt_thread *to_thread;
	
	/* 手动指定第一个运行的线程 */
	to_thread = rt_list_entry(rt_thread_priority_table[0].next,
														struct rt_thread,
														tlist);
														
	rt_current_thread = to_thread;
  
	/* 切换到第一个线程，该函数在contex_rvds.s中实现。
		 在rth.w声明，用于实现第一次线程切换。当一个汇编函数
		 在C文件中调用的时候，如果有形参，则执行的时候会将
		 形参传入到cpu寄存器r0. */
	rt_hw_context_switch_to((rt_uint32_t)&to_thread->sp);
														
														
}

/* 系统调度 */
void rt_schedule(void)
{
	struct rt_thread *to_thread;
	struct rt_thread *from_thread;
	
	/* 两个线程轮流切换 */
	if( rt_current_thread == rt_list_entry(rt_thread_priority_table[0].next,
																					struct rt_thread,
																					tlist))
	{
			from_thread = rt_current_thread;
			to_thread = rt_list_entry(rt_thread_priority_table[1].next,
																struct rt_thread,
																tlist);
			rt_current_thread = to_thread;
	}
	else
	{
		from_thread = rt_current_thread;
		to_thread = rt_list_entry(rt_thread_priority_table[0].next,
															struct rt_thread,
															tlist);
		rt_current_thread = to_thread;
		
	}
	
	rt_hw_context_switch((rt_uint32_t)&from_thread->sp, (rt_uint32_t)&to_thread->sp);
	
}

