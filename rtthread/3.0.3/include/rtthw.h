#ifndef __RT_HW_H__
#define __RT_HW_H__
	
#ifdef __cplusplus
extern "C" {
#endif
#include "rtdef.h"
	
rt_uint8_t *rt_hw_stack_init(void       *entry,
                             void       *parameter,
                             rt_uint8_t *stack_addr);

void rt_hw_context_switch(rt_uint32_t from, rt_uint32_t to);
void rt_hw_context_switch_to(rt_uint32_t to);		
														 
#ifdef __cplusplus
}
#endif

#endif
