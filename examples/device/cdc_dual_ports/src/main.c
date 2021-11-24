/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "bsp/board.h"
#include "tusb.h"

uint32_t get_time_ms(){
    return to_ms_since_boot(get_absolute_time());
}

int main(void)
{
    // board_init();
    tusb_init();

    char buf[500];

    while (1) {
        tud_task(); // tinyusb device task

        if (get_time_ms() % 20 == 0 && tud_cdc_n_connected(0)) {
            snprintf(buf, sizeof(buf), "TIME: %.2f test test test test test\n",
                get_time_ms() / 1000.0);
            tud_cdc_n_write_str(0, buf);
            tud_cdc_n_write_flush(0);
        }

        if (tud_cdc_n_connected(1) && tud_cdc_n_available(1) > 0) {
            uint8_t buf[64];
            uint32_t count = tud_cdc_n_read(1, buf, sizeof(buf));
            tud_cdc_n_write(1, buf, count);
            tud_cdc_n_write_flush(1);
        }

    }

    return 0;
}