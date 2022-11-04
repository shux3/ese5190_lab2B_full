#include "pico/stdlib.h"
#include <stdio.h>
#include "neopixel.h"
#include "hardware/gpio.h"


#define QTPY_BOOT_PIN 21

typedef struct {
    uint32_t last_serial_byte;
    uint32_t button_is_pressed;
    uint32_t light_color;
} Flashlight; 

void render_to_console(Flashlight status) {
    // adjust console window height to match 'frame size'
    for (uint8_t i=0; i<10; i++) { 
        printf("\n");
    }
    printf("button_is_pressed:  0x%08x\n",   status.button_is_pressed);
    printf("light_color:        0x%08x\n",   status.light_color);
}  

int main() {
    volatile uint32_t * addr;
    uint32_t tmp;

    stdio_init_all();
    
    // gpio_init(QTPY_BOOT_PIN);
    addr = (volatile uint32_t *) 0xd0000028;
    *addr = 0x00200000;

    // 39 sio_hw -> gpio_clr = lul << QTPY_BOOT_PIN;
    addr = (volatile uint32_t *) 0xd0000018;
    *addr = 0x00200000;
    
    // 45 gpio_set_dunction
    // hw_xor_bits()
    addr = (volatile uint32_t *) 0x4001c004;
    tmp = 
    addr = (volatile uint32_t *) ((uint32_t) addr | 0x00001000);
    *addr = (uint32_t) tmp;

    // 68 Zero all fields apart from fsel;
    // 74 GPIO_FUNC_SIO
    addr = (volatile uint32_t *) 0x40014054;
    *addr = 0x00000005;

    addr = (volatile uint32_t *) 0xd0000004;
    tmp = (uint32_t) *addr;

    // 82 gpio_set_dir(QTPY_BOOT_PIN, GPIO_IN);
    neopixel_init();

    // 93
    Flashlight status;
    status.last_serial_byte =  0x00000000;
    status.button_is_pressed = 0x00000000;
    status.light_color =       0x000000ff;

    while (true) {
        status.last_serial_byte = getchar_timeout_us(0); // don't block main loop
        switch(status.last_serial_byte) { // poll every cycle
            case 'r':
                status.light_color = 0x00ff0000;
                break;
            case 'g':
                status.light_color = 0x0000ff00;
                break;
            case 'b':
                status.light_color = 0x000000ff;
                break;
            case 'w':
                status.light_color = 0x00ffffff;
                break;
        }
        // gpio_get :
        addr = (volatile uint32_t *) 0xd0000004;
        tmp = (uint32_t) *addr;
        if (tmp & 0x00200000) { // poll every cycle, 0 = "pressed"
            status.button_is_pressed = 0x00000000;
        } else {
            status.button_is_pressed = 0x00000001;
        }
        if (status.button_is_pressed) { // poll every cycle
            neopixel_set_rgb(status.light_color);
        } else {
            neopixel_set_rgb(0x00000000);
        }
        render_to_console(status);
        sleep_ms(10); // don't DDOS the serial console
    }
    return 0;
}                  
