#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/display.h>
#include <string.h>

void main(void)
{
    const struct device *display_dev;

    printk("Initializing ILI9341 display...\n");

    display_dev = DEVICE_DT_GET(DT_INST(0, ilitek_ili9341));
    if (!device_is_ready(display_dev)) {
        printk("Display device not ready\n");
        return;
    }

    display_blanking_off(display_dev);

    struct display_buffer_descriptor buf_desc;
    uint8_t buf[240 * 20 * 2]; // one line of 240 pixels, RGB565 (2 bytes per pixel)

    memset(buf, 0xFF, sizeof(buf)); // white

    buf_desc.width = 240;
    buf_desc.height = 20;
    buf_desc.pitch = 240;
    buf_desc.buf_size = sizeof(buf);

    display_write(display_dev, 0, 0, &buf_desc, buf);
    printk("White stripe drawn on screen.\n");
}
