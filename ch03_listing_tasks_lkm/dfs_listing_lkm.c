/*
 * Programming project on page 161
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>

void dfs(struct task_struct *task)
{
    struct task_struct *child;
    struct list_head *list;
    
    printk(KERN_INFO "Task name %s, state %ld and process id %d\n", task->comm, task->state, task->pid);
    
    list_for_each(list, &task->children) {
        child = list_entry(list, struct task_struct, sibling);
        /* child points to the next child in the list */
        dfs(child);
    }
}

/* This function is called when the module is loaded. */
int simple_init(void)
{
    printk(KERN_INFO "Loading DFS List Tasks Module\n");
    
    dfs(&init_task);
    
    return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void)
{
    printk(KERN_INFO "Removing DFS List Tasks Module\n");
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("DFS List Tasks");
MODULE_AUTHOR("Iker Pedrosa");
