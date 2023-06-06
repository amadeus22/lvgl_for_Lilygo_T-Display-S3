/*lvgl sample for simple object on Lilygo T-Display S3
 * here rectangle with shadow
 * 
 * author: Rudi Ackermann
 * June 2023
 * 
 * does not work yet!!!
 */

#include <TFT_eSPI.h>
#include "lvgl.h"

lv_disp_drv_t disp_drv;
lv_indev_drv_t indev_drv;

lv_obj_t *screenMain;
lv_obj_t *label;

char txt[100];
lv_obj_t *label_1; //  x,y label
lv_obj_t *label_2; //  x,y label

/*Change to screen resolution - here for tft.setRotation(1 and 3)
  for tft.setRotation(0 and 2) use width=170 and height=320 
  and use different label length
*/
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 170;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 10 ];

TFT_eSPI tft = TFT_eSPI(); /* TFT instance */

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)&color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}

void setup()
{
    tft.init();
    tft.setRotation(1);

    lv_init();

    lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10);

    /*Initialize the display*/
    lv_disp_drv_init(&disp_drv);
    /*Change the following line to the display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    //--------------------------------------------------------------------------

    #define BUF_W 80
    #define BUF_H 40
    
    lv_color_t buf[BUF_W * BUF_H];
    lv_color_t * buf_p = buf;
    uint16_t x, y;
    for(y = 0; y < BUF_H; y++) {
        lv_color_t c = lv_color_mix(LV_COLOR_MAKE(0, 0, 255), LV_COLOR_MAKE(255, 0, 0), (y * 255) / BUF_H);
        for(x = 0; x < BUF_W; x++){
            (*buf_p) =  c;
            buf_p++;
        }
    }
    
    lv_area_t a;
    a.x1 = 10;
    a.y1 = 40;
    a.x2 = a.x1 + BUF_W - 1;
    a.y2 = a.y1 + BUF_H - 1;
    my_disp_flush(NULL, &a, buf);
    
    //--------------------------------------------------------------------------

}

void loop()
{
    lv_task_handler();
    delay(5);
}
