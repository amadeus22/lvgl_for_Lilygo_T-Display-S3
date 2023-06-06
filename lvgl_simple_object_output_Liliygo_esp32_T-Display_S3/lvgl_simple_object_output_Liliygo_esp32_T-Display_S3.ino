/*lvgl sample for simple object on Lilygo T-Display S3
 * here rectangle with shadow
 * lvgl 8.3 is used
 * 
 * author: Rudi Ackermann
 * June 2023
 */

#include <TFT_eSPI.h>
#include "lvgl.h"

lv_disp_drv_t disp_drv;
lv_indev_drv_t indev_drv;

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

    lv_obj_t * obj1;  // simple rounded rectangle
    obj1 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj1, 80, 40);
    lv_obj_align(obj1, LV_ALIGN_CENTER, -80, -30);

    static lv_style_t style_shadow;
    lv_style_init(&style_shadow);
    lv_style_set_shadow_width(&style_shadow, 10);
    lv_style_set_shadow_spread(&style_shadow, 5);
    lv_style_set_shadow_color(&style_shadow, lv_palette_main(LV_PALETTE_BLUE));

    lv_obj_t * obj2;  // rounded rectangle with shadow around
    obj2 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj2, 85, 85);
    lv_obj_add_style(obj2, &style_shadow, 0);
    lv_obj_align(obj2, LV_ALIGN_CENTER, 50, 0);

}

void loop()
{
    lv_task_handler();
    delay(5);
}
