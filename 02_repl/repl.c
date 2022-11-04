#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/gpio.h"
#include "hardware/address_mapped.h"
#include "register.h"

#define QTPY_BOOT_PIN 21

typedef struct {
    uint32_t last_serial_byte;
    uint32_t button_is_pressed;
    uint32_t write1_read0_flag;
    uint32_t reg_address;
    uint32_t reg_value;
} user_repl; 

void render_to_console(user_repl status) {
    // adjust console window height to match 'frame size'
    for (uint8_t i=0; i<10; i++) { 
        printf("\n");
    }
    
    printf("register being selected:  0x%08x\n",   status.reg_address);
    printf("register value:           0x%08x\n",   status.reg_value);

    if (status.write1_read0_flag == 0x00000000) {
        printf("wriet/read status:        read");
    } else if (status.write1_read0_flag == 0x00000001) {
        printf("write/read status:        write");
    }
}


int main() {
    uint32_t mask32 = 0x11111111;   // mask used to write register value.
    volatile uint32_t *boot_pin_address = 0xd0000004; // boot pin address

    stdio_init_all();
    gpio_init(QTPY_BOOT_PIN);
    gpio_set_dir(QTPY_BOOT_PIN, GPIO_IN);
    
    user_repl status;
    status.last_serial_byte =  0x00000000;
    status.button_is_pressed = 0x00000000;  // 0 as pressed; 1 as released
    status.write1_read0_flag = 0x00000000;  // 0 as read -- type to change address; 1 as write -- type to change value
    status.reg_address =       0x00000000;
    status.reg_value =         0x00000000;

    while (true) {
        status.last_serial_byte = getchar_timeout_us(0);
        if (status.write1_read0_flag == 0x00000000) {
            switch(status.last_serial_byte) { // poll every cycle
                case '0':
                    status.reg_address = (status.reg_address << 4);
                    break;
                case '1':
                    status.reg_address = (status.reg_address << 4) + 0x1;
                    break;
                case '2':
                    status.reg_address = (status.reg_address << 4) + 0x2;
                    break;
                case '3':
                    status.reg_address = (status.reg_address << 4) + 0x3;
                    break;
                case '4':
                    status.reg_address = (status.reg_address << 4) + 0x4;
                    break;
                case '5':
                    status.reg_address = (status.reg_address << 4) + 0x5;
                    break;
                case '6':
                    status.reg_address = (status.reg_address << 4) + 0x6;
                    break;
                case '7':
                    status.reg_address = (status.reg_address << 4) + 0x7;
                    break;
                case '8':
                    status.reg_address = (status.reg_address << 4) + 0x8;
                    break;
                case '9':
                    status.reg_address = (status.reg_address << 4) + 0x9;
                    break;
                case 'a':
                    status.reg_address = (status.reg_address << 4) + 0xA;
                    break;
                case 'b':
                    status.reg_address = (status.reg_address << 4) + 0xB;
                    break;
                case 'c':
                    status.reg_address = (status.reg_address << 4) + 0xC;
                    break;
                case 'd':
                    status.reg_address = (status.reg_address << 4) + 0xD;
                    break;
                case 'e':
                    status.reg_address = (status.reg_address << 4) + 0xE;
                    break;
                case 'f':
                    status.reg_address = (status.reg_address << 4) + 0xF;
                    break;
                case 'w':
                    status.write1_read0_flag = 0x00000001;
                    break;
            }
        } else if (status.write1_read0_flag == 0x00000001) {
            switch(status.last_serial_byte) { // poll every cycle
                case '0':
                    status.reg_value = (status.reg_value << 4);
                    break;
                case '1':
                    status.reg_value = (status.reg_value << 4) + 0x1;
                    break;
                case '2':
                    status.reg_value = (status.reg_value << 4) + 0x2;
                    break;
                case '3':
                    status.reg_value = (status.reg_value << 4) + 0x3;
                    break;
                case '4':
                    status.reg_value = (status.reg_value << 4) + 0x4;
                    break;
                case '5':
                    status.reg_value = (status.reg_value << 4) + 0x5;
                    break;
                case '6':
                    status.reg_value = (status.reg_value << 4) + 0x6;
                    break;
                case '7':
                    status.reg_value = (status.reg_value << 4) + 0x7;
                    break;
                case '8':
                    status.reg_value = (status.reg_value << 4) + 0x8;
                    break;
                case '9':
                    status.reg_value = (status.reg_value << 4) + 0x9;
                    break;
                case 'a':
                    status.reg_value = (status.reg_value << 4) + 0xA;
                    break;
                case 'b':
                    status.reg_value = (status.reg_value << 4) + 0xB;
                    break;
                case 'c':
                    status.reg_value = (status.reg_value << 4) + 0xC;
                    break;
                case 'd':
                    status.reg_value = (status.reg_value << 4) + 0xD;
                    break;
                case 'e':
                    status.reg_value = (status.reg_value << 4) + 0xE;
                    break;
                case 'f':
                    status.reg_value = (status.reg_value << 4) + 0xF;
                    break;
                case 'r':
                    status.write1_read0_flag = 0x00000000;
                    break;
            }
        }

        if (gpio_get(QTPY_BOOT_PIN)) { // poll every cycle, 0 = "pressed"
            status.button_is_pressed = 0x00000000;
        } else {
            status.button_is_pressed = 0x00000001;
        }

        if (status.button_is_pressed) { // poll every cycle
            if (status.write1_read0_flag == 0x00000000) {    // read the register
                status.reg_value = register_read((volatile uint32_t *) status.reg_address);
            } else if (status.write1_read0_flag == 0x00000001) { // write to register 
                register_write((volatile uint32_t *) status.reg_address, (uint32_t) status.reg_value);
            }
        }

        render_to_console(status);
        sleep_ms(20);
    }
    return 0;
}