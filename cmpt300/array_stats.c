#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include "array_stats.h"

int copy_error_array_stats(void)
{
	printk("ERROR: Unable to copy data.\n");
	return -EFAULT;
}

SYSCALL_DEFINE3(array_stats, struct array_stats *, stats, long *, data, long,
		size)
{
	int position = 0;
	long struct_min, struct_max, struct_sum, array_value = 0;

	if (size <= 0) {
		printk("ERROR: Size must be greater than zero.\n");
		return -EINVAL;
	}

	if (copy_from_user(&array_value, &data[0], sizeof(long)) != 0)
		return copy_error_array_stats();

	struct_min = array_value;
	struct_max = array_value;
	struct_sum = array_value;

	for (position = 1; position < size; position++) {
		if (copy_from_user(&array_value, &data[position],
				   sizeof(long)) != 0)
			return copy_error_array_stats();
		struct_min = min(struct_min, array_value);
		struct_max = max(struct_max, array_value);
		struct_sum += array_value;
	}

	if (copy_to_user(&stats->min, &struct_min, sizeof(long)) != 0)
		return copy_error_array_stats();

	if (copy_to_user(&stats->max, &struct_max, sizeof(long)) != 0)
		return copy_error_array_stats();

	if (copy_to_user(&stats->sum, &struct_sum, sizeof(long)) != 0)
		return copy_error_array_stats();

	return 0;
}
