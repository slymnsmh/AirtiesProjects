#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/random.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Suleyman Semih Demir");
MODULE_DESCRIPTION("Module that prints a random number to dmesg.");
MODULE_VERSION("1.0");

static int __init lkm_example_init(void) {
	int i, lessthan100;

	printk("Running...!\n");
	
	get_random_bytes(&i, sizeof(i));
	
	lessthan100 = i % 100;
	
	printk("Random number: %d\n", lessthan100);
	
	return 0;
}
static void __exit lkm_example_exit(void) {
	printk("Module closed!\n");
}

module_init(lkm_example_init);
module_exit(lkm_example_exit);