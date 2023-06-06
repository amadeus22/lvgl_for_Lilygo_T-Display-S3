/*lvgl sample for text output on Lilygo T-Display S3
 * here centered text and scrolling text
 * lvgl 8.3 is used
 * 
 * author: Rudi Ackermann
 * June 2023
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

    label_1 = lv_label_create(lv_scr_act());  // full screen as the parent
    lv_label_set_text(label_1, "#0000ff Re-color# #ff00ff words# #ff0000 of a# label, align the lines to the center "
                      "and wrap long text automatically.");   // set label text
    lv_label_set_recolor(label_1, true);
    lv_obj_set_width(label_1, 300);  //Set smaller width to make the lines wrap
    //lv_obj_align(label_1, LV_ALIGN_TOP_LEFT, 20, 50); // LV_LABEL_ALIGN_LEFT/RIGHT/CENTER
    lv_obj_set_style_text_align(label_1, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(label_1, LV_ALIGN_CENTER, 0, -40);

    label_2 = lv_label_create(lv_scr_act());
    lv_label_set_long_mode(label_2, LV_LABEL_LONG_SCROLL_CIRCULAR);  // Circular scroll
    lv_obj_set_width(label_2, 150);
    lv_label_set_text(label_2, "This is a circularly scrolling text. ");
    lv_obj_align(label_2, LV_ALIGN_CENTER, 0, 40);

}

void loop()
{
    lv_task_handler();
    delay(5);
}
