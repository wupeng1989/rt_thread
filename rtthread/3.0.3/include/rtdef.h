#ifndef  __RT_DEF_H__
#define  __RT_DEF_H__


/* rt-thead �����������Ͷ��� */
typedef signed char rt_int8_t;
typedef signed short rt_int16_t;
typedef signed long rt_int32_t;
typedef unsigned char rt_uint8_t;
typedef unsigned short rt_uint16_t;
typedef unsigned long rt_uint32_t;
typedef int	rt_bool_t;

/* 32 bit cpu */
typedef long rt_base_t;
typedef unsigned long rt_ubase_t;

typedef rt_base_t rt_err_t;
typedef rt_uint32_t rt_time_t;
typedef rt_uint32_t rt_tick_t;
typedef rt_base_t rt_flag_t;
typedef rt_ubase_t rt_size_t;
typedef rt_ubase_t rt_dev_t;
typedef rt_base_t rt_off_t;

/* ������������ */
#define RT_TRUE 1
#define RT_FALSE 0

#ifdef __CC_ARM 

#define rt_inline	static __inline
#define ALIGN(n)	__attribute__((aligned(n))

#elif defined (__IAR_SYSTEMS_ICC)
#definde rt_inline static inline
#define ALIGN(n)	PRAGMA(data_alignment=n)

#elif defind (__GNUC__)

#define rt_inline static __inline
#define ALGIN(n)	__attribute__((aligned(n)))

#else
#error not supported tool chain
#endif


#define RT_ALIGN(size, align) (((size) + (align) -1) & ~((align) -1 ))
#define RT_ALIGN_DOWN(size, align) ((size) & ~((align) -1))

#define RT_NULL (0)


#define RT_EOK			0 	/* There is no error */
#define RT_ERROR		1		/* A generic error happens */
#define RT_ETIMEOUT	2		/* Time out */
#define RT_EFULL		3 	/* The resource is full */
#define RT_EEMPYT		4		/* The resource is empyt */
#define RT_ENOMEM		5		/* No memory */
#define RT_ENOSYS		6		/* No system */
#define RT_EBUSY		7   /* Busy */
#define RT_EIO			8	  /* IO error */
#define RT_EINTR		9 	/* Interrupted system call */
#define RT_EINVAl		10	/* Invalid argument */


struct rt_list_node
{
	struct rt_list_node *next;		/* point to next node */
	struct rt_list_node *prev;		/* point to prev node */
};

typedef struct rt_list_node rt_list_t;


struct rt_thread
{
	void 				*sp;	/* �߳�ջָ�� */
	void 				*entry;	/* �߳���ڵ�ַ */
	void 				*parameter;	/* �߳��β� */
	void 				*stack_addr;	/* �߳�ջ��ʼ��ַ */
	rt_uint32_t stack_size;	/*�߳�ջ��С����λΪ�ֽ�*/
	
	rt_list_t	list;		/* the object list */
	rt_list_t tlist	;	/* the thread list */
	
};

typedef struct rt_thread *rt_thread_t;





#endif 
