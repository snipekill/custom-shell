#include<linux/init.h> 
#include<linux/kernel.h> 
#include<linux/module.h>
#include <linux/sched.h>
#include<linux/list.h>
#include<linux/sched/signal.h>
#include <linux/slab.h>
#include<linux/moduleparam.h>

static int start = 25 ;

module_param(start,int,0) ;

static struct color {
	int red ;
	int green ;
	int blue ;
	struct list_head list ;
} ;

// static struct list_head color_list ;

static LIST_HEAD(color_list) ;


static int simple_init(void)
{
	printk(KERN_INFO "Loading Module\n") ;
	struct color *violet;
	int temp =start ;
	do
	{
		start = temp ;
		violet = kmalloc(sizeof(*violet), GFP_KERNEL); 
		violet->red = start;
		violet->blue = start;
		violet->green = start;
		INIT_LIST_HEAD(&violet->list);
		list_add_tail(&violet->list, &color_list);
		if(temp%2)
			temp = (3*temp)+1 ;
		else 
			temp = temp/2 ;
	}while(start!=1) ;
	
	struct color *ptr;
	list_for_each_entry(ptr, &color_list, list) { /* on each iteration ptr points */
		printk(KERN_INFO "RED %d\tGREEN %d\tBLUE %d\n",ptr->red,ptr->green,ptr->blue) ;
	}
	return 0;
}

static void simple_exit(void)
{
	printk(KERN_INFO "(In Microseconds)\n") ;
	struct color *ptr, *next;
	list_for_each_entry_safe(ptr,next,&color_list,list) { 
		printk(KERN_INFO "DELETING FOR VALUES RED %d\tGREEN %d\tBLUE %d\n",ptr->red,ptr->green,ptr->blue) ;
		list_del(&ptr->list);
		kfree(ptr);
	}
	printk(KERN_INFO "NOW AFTER DELETING THE LIST\n") ;
	list_for_each_entry(ptr, &color_list, list) { /* on each iteration ptr points */
		printk(KERN_INFO "RED %d\tGREEN %d\tBLUE %d\n",ptr->red,ptr->green,ptr->blue) ;
	}
	printk(KERN_INFO "LIST END\n") ;
}

module_init(simple_init) ;
module_exit(simple_exit) ;

MODULE_LICENSE("GPL") ;
MODULE_DESCRIPTION("Simple Module") ;
MODULE_AUTHOR("CIBOLA") ;

