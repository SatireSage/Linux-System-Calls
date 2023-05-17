#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/cred.h>
#include "process_ancestors.h"

int copy_error_process_ancestors(void)
{
	printk("ERROR: Unable to copy data.\n");
	return -EFAULT;
}

SYSCALL_DEFINE3(process_ancestors, struct process_info *, stats, long, size,
		long *, num_filled)
{
	struct task_struct *cur_task;
	struct process_info info_buffer;
	struct list_head *children, *siblings;
	long position = 0;

	if (size <= 0) {
		printk("ERROR: Size must be greater than zero.\n");
		return -EINVAL;
	}

	cur_task = current;

	while (position < size && cur_task->parent != cur_task) {
		info_buffer.pid = cur_task->pid;
		strncpy(info_buffer.name, cur_task->comm,
			ANCESTOR_NAME_LEN - 1);
		info_buffer.name[ANCESTOR_NAME_LEN - 1] = '\0';
		info_buffer.state = cur_task->state;
		info_buffer.uid = cur_task->cred->uid.val;
		info_buffer.nvcsw = cur_task->nvcsw;
		info_buffer.nivcsw = cur_task->nivcsw;
		info_buffer.num_children = 0;
		info_buffer.num_siblings = 0;

		list_for_each (children, &cur_task->children) {
			info_buffer.num_children++;
		}
		list_for_each (siblings, &cur_task->sibling) {
			info_buffer.num_siblings++;
		}

		if (copy_to_user(&stats[position], &info_buffer,
				 sizeof(info_buffer)))
			return copy_error_process_ancestors();
		position++;
		cur_task = cur_task->parent;
	}

	if (copy_to_user(num_filled, &position, sizeof(long)))
		return copy_error_process_ancestors();

	return 0;
}
