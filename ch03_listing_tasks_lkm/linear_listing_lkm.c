/*
 * Programming project on page 160
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>

/* This function is called when the module is loaded. */
int simple_init(void)
{
    struct task_struct *task;
    
    printk(KERN_INFO "Loading Linear List Tasks Module\n");
    
    for_each_process(task) {
        /* on each iteration task points to the next task */
        printk(KERN_INFO "Task name %s, state %ld and process id %d\n", task->comm, task->state, task->pid);
    }
    
    return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void)
{
    printk(KERN_INFO "Removing Linear List Tasks Module\n");
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Linear List Tasks");
MODULE_AUTHOR("Iker Pedrosa");
