#include<linux/init.h> 
#include<linux/kernel.h> 
#include<linux/module.h>
#include <linux/sched.h>
#include<linux/sched/signal.h>

#define MAX_SIZE 50000

static unsigned int visited[MAX_SIZE+1] ;

// for(int i = 0;i<=MAX_SIZE;i++)
// {
// 	visited[i] =0;
// }

void dfs(struct task_struct *init_task)
{
	printk(KERN_INFO "%s\t%d\t%d\t%ld\n",init_task->comm,init_task->pid,(init_task->parent)->pid,init_task->state) ;
	struct list_head *list ;
	struct task_struct *task ;
	list_for_each(list,&init_task->children){
		task = list_entry(list,struct task_struct,sibling) ;
		int pidt = task->pid ;
		if(visited[pidt]==0)
		{
			visited[pidt] = 1 ;
			dfs(task) ;
		}

	}
}

static int simple_init(void)
{
	int i = 0 ;
	while(i<=MAX_SIZE)
	{
		visited[i++] =0;
	}
	
	printk(KERN_INFO "Loading Module\n") ;
	visited[(&init_task)->pid] = 1 ;
	dfs(&init_task) ;
	// static struct task_struct *task ;
	// printk(KERN_INFO "COMMAND\tPID\tSTATE\t") ;
	// for_each_process(task){
	// 	printk(KERN_INFO "%s\t%d\t%ld\n",task->comm,task->pid,task->state) ;
	// } 
	return 0;
}

static void simple_exit(void)
{
	printk(KERN_INFO "(In Microseconds)\n") ;
}

module_init(simple_init) ;
module_exit(simple_exit) ;

MODULE_LICENSE("GPL") ;
MODULE_DESCRIPTION("Simple Module") ;
MODULE_AUTHOR("CIBOLA") ;

