#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>
#include <linux/string.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

int template_init(void);
void template_exit(void);
module_init(template_init);
module_exit(template_exit);

 // #define __NR_CLOSE (__NR_SYSCALL_BASE+ 6) 

#if defined(__i386__)
#define START_CHECK 0xc0000000
#define END_CHECK 0xd0000000
typedef unsigned int psize;
#else
#define START_CHECK 0xffffffff81000000
#define END_CHECK 0xffffffffa2000000
typedef unsigned long psize;
#endif

psize *sys_call_table;


psize **find(void) {
 psize **sctable;
 psize i = START_CHECK;
 while (i < END_CHECK) {
  sctable = (psize **) i;
  if (sctable[__NR_close] == (psize *) sys_close) {
   return &sctable[0];
  } 
  i += sizeof(void *);
 }
 return NULL;
}

int template_init(void) {
	if (sys_call_table = (psize *) find()) {
	 printk("rooty: sys_call_table found at %p\n",sys_call_table);
	} else {
	 printk("rooty: sys_call_table not found\n");
	}
	return 0;
}

void template_exit(void) {
	// printf("template :: module removed\n");
	printk("template :: module removed\n");
}
