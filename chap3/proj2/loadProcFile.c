#include<linux/init.h> 
#include<linux/kernel.h> 
#include<linux/module.h>
#include<linux/proc_fs.h>
#include<linux/uaccess.h>
// #include<linux/jiffies.h>
// #include<linux/hash.h>
#include <linux/slab.h>

#define BUFFER_SIZE 128
#define PROC_NAME "hell"

ssize_t proc_read(struct file *file,char __user *usr_buf,size_t count,loff_t *pos) ;

ssize_t proc_write(struct file *file,const char __user *usr_buf,size_t count,loff_t *pos) ;
// ssize t proc read(struct file *file,char __user *usr_buf,size_t count,loff_t *pos);

static struct file_operations proc_ops = {
	.owner = THIS_MODULE,
	.read = proc_read,
	.write = proc_write,
} ;

static int proc_init(void)
{
	// jif = jiffies ;
	proc_create(PROC_NAME,0666,NULL,&proc_ops) ;
	return 0 ;
}

static void proc_exit(void)
{
	remove_proc_entry(PROC_NAME,NULL) ;
}

ssize_t proc_read(struct file *file,char __user *usr_buf,size_t count,loff_t *pos)
{
	int rv = 0 ;
	char buffer[BUFFER_SIZE] ;
	static int completed = 0 ;

	if(completed)
	{
		completed = 0 ;
		return 0 ;
	}
	completed = 1;
	rv = sprintf(buffer,"HELLO WORLD\n") ;
	
	// rv = sprintf(buffer,"Time Elapsed in Seconds %lu",(jiffies-jif)/HZ) ;
	copy_to_user(usr_buf,buffer,rv) ;
	return rv ;
}

ssize_t proc_write(struct file *file,const char __user *usr_buf,size_t count,loff_t *pos)
{
	// int rv = 0;
	char *k_mem ;
	// printk(KERN_INFO "COUNT %lu\n",count) ;
	k_mem = kmalloc(count,GFP_KERNEL) ;
	copy_from_user(k_mem,usr_buf,count) ;
	// unsigned int pid ;
	
	// kstrtouint(k_mem,0,&pid) ;
	// printk(KERN_INFO "PID VALUE %u",pid) ;
	kfree(k_mem) ;
	return count ;
}

module_init(proc_init) ;
module_exit(proc_exit) ;

MODULE_LICENSE("GPL") ;
MODULE_DESCRIPTION("Hello Module") ;
MODULE_AUTHOR("CIBOLA") ;

