#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>
#include <linux/uaccess.h>

static int state;
static int gpio_pin = 49; 
static struct kobject *led_kobj;

static ssize_t state_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
    return sprintf(buf, "%d\n", state);
}

static ssize_t state_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count) {
    int new_state;
    sscanf(buf, "%du", &new_state);

    if (new_state == 0) {
        gpio_set_value(gpio_pin, 0);
        state = 0;
    } else {
        gpio_set_value(gpio_pin, 1);
        state = 1;
    }

    return count;
}

static struct kobj_attribute state_attribute = __ATTR(state, 0660, state_show, state_store);

static struct attribute *attrs[] = {
    &state_attribute.attr,
    
};

static struct attribute_group attr_group = {
    .attrs = attrs,
};

static int __init led_init(void) {
    int retval;

    
    if (!gpio_is_valid(gpio_pin)) {
        pr_err("Invalid GPIO %d\n", gpio_pin);
        return -ENODEV;
    }

    
    retval = gpio_request(gpio_pin, "sysfs-led");
    if (retval) {
        pr_err("Failed to request GPIO %d\n", gpio_pin);
        return retval;
    }

    
    gpio_direction_output(gpio_pin, state);

    
    led_kobj = kobject_create_and_add("led", kernel_kobj);
    if (!led_kobj) {
        gpio_free(gpio_pin);
        pr_err("Failed to create kobject\n");
        return -ENOMEM;
    }

    
    retval = sysfs_create_group(led_kobj, &attr_group);
    if (retval) {
        kobject_put(led_kobj);
        gpio_free(gpio_pin);
        pr_err("Failed to create sysfs group\n");
        return retval;
    }

    return 0;
}

static void __exit led_exit(void) {
    kobject_put(led_kobj);
    gpio_set_value(gpio_pin, 0); 
    gpio_free(gpio_pin);
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Meenal shrivastava");
MODULE_DESCRIPTION("A simple sysfs-based GPIO driver for BBB");

