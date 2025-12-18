/*
 *  hello.c - The simplest kernel module.
 *  Logs a hello message when loaded and a goodbye when unloaded.
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */

MODULE_LICESE("GPL")

int init_module(void)
{
    /* Kernel log on module insertion. */
    printk(KERN_INFO "Hello world.\n");

    /*
     * A non 0 return means init_module failed; module can't be loaded.
     */
    return 0;
}

void cleanup_module(void)
{
    /* Kernel log on module removal. */
    printk(KERN_INFO "Goodbye world.\n");
}
