/*
 * Programming project on page 99
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>

struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};

static LIST_HEAD(birthday_list);

struct birthday *create_person(int day, int month, int year) {
	struct birthday *person = kmalloc(sizeof(struct birthday), GFP_KERNEL);
	person->day = day;
	person->month = month;
	person->year = year;
	return person;
}

/* This function is called when the module is loaded. */
int simple_init(void)
{
    int i;
    struct birthday *person;
    struct birthday *ptr;
    
    printk(KERN_INFO "Loading Module\n");
    
    for(i = 0; i < 5; i++) {
        person = create_person(i, i, i);
        list_add_tail(&person->list, &birthday_list);
    }

    list_for_each_entry(ptr, &birthday_list, list) {
        /* on each iteration ptr points */
        /* to the next birthday struct */
        printk("Show birthday: %d:%d:%d\n", ptr->day, ptr->month, ptr->year);
    }

    return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void)
{
    struct birthday *ptr, *next;

    printk(KERN_INFO "Removing Module\n");
    
    list_for_each_entry_safe(ptr, next, &birthday_list, list) {
        /* on each iteration ptr points */
        /* to the next birthday struct */
        printk("Remove birthday: %d:%d:%d\n", ptr->day, ptr->month, ptr->year);
        list_del(&ptr->list);
        kfree(ptr);
    }
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Data Structures Module");
MODULE_AUTHOR("Iker Pedrosa");
