#include<linux/init.h> 
#include<linux/kernel.h> 
#include<linux/module.h>
#include<linux/gcd.h>
#include<linux/hash.h>
#include<asm/param.h>
#include<linux/jiffies.h>

static unsigned long jif ;
static int simple_init(void)
{
	jif = jiffies ;
	printk(KERN_INFO "Loading Module %lu\n",jiffies) ;
	return 0;
}

static void simple_exit(void)
{
	unsigned long hh = ((jiffies-jif)*100) ;
	unsigned long c = 0 ;
	while(hh>0)
	{
		hh = hh - HZ ;
		c++ ;
	}
	printk(KERN_INFO "(In Microseconds) %lu\n",c) ;
}

module_init(simple_init) ;
module_exit(simple_exit) ;

MODULE_LICENSE("GPL") ;
MODULE_DESCRIPTION("Simple Module") ;
MODULE_AUTHOR("CIBOLA") ;

