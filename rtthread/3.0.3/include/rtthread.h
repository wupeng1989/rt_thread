#ifndef __RT_THREAD_H__
#define __RT_THREAD_H__


#ifdef __cplusplus
extern "C" {
#endif
	
rt_err_t rt_thread_init(struct rt_thread *thread,
                        void (*entry)(void *parameter),
                        void             *parameter,
                        void             *stack_start,
                        rt_uint32_t       stack_size);	
	

												
void rt_schedule(void);												
void rt_system_scheduler_init(void);
void rt_system_scheduler_start(void);												
#ifdef __cplusplus
}
#endif

#endif		
