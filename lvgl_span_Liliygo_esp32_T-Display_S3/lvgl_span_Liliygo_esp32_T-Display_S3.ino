/*lvgl meter sample on Lilygo T-Display S3
 * lvgl 8.3 is used
 * 
 * author: Rudi Ackermann
 * June 2023
 */

#include <TFT_eSPI.h>
#include <lvgl.h>

lv_disp_drv_t disp_drv;
lv_indev_drv_t indev_drv;


/*Change to screen resolution - here for tft.setRotation(1 and 3)
  for tft.setRotation(0 and 2) use width=170 and height=320 
  and use different label length
*/
static const uint16_t screenWidth = 320;
static const uint16_t screenHeight = 170;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];

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
    tft.fillScreen(TFT_YELLOW);

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
    // change background color of actual screen
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_make(0, 0, 0) , LV_PART_MAIN);

//--------------------------------------------------------------------------
   
    /**
     * Create span.
    */
    
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_border_width(&style, 1);
    lv_style_set_border_color(&style, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_pad_all(&style, 2);

    lv_obj_t * spans = lv_spangroup_create(lv_scr_act());
    lv_obj_set_width(spans, 300);
    lv_obj_set_height(spans, 150);
    lv_obj_center(spans);
    lv_obj_add_style(spans, &style, 0);

    lv_spangroup_set_align(spans, LV_TEXT_ALIGN_LEFT);
    lv_spangroup_set_overflow(spans, LV_SPAN_OVERFLOW_CLIP);
    lv_spangroup_set_indent(spans, 18);
    lv_spangroup_set_mode(spans, LV_SPAN_MODE_BREAK);

    lv_span_t * span = lv_spangroup_new_span(spans);
    lv_span_set_text(span, "I try it the first time. ");
    lv_style_set_text_color(&span->style, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_text_decor(&span->style, LV_TEXT_DECOR_UNDERLINE);
    
    span = lv_spangroup_new_span(spans);
    lv_span_set_text_static(span, "I hope I'm lucky. ");
#if LV_FONT_MONTSERRAT_24
    lv_style_set_text_font(&span->style,  &lv_font_montserrat_24);
#endif
    lv_style_set_text_color(&span->style, lv_palette_main(LV_PALETTE_RED));

    span = lv_spangroup_new_span(spans);
    lv_span_set_text_static(span, "LVGL is a powerful, open-source graphics library. ");
    lv_style_set_text_color(&span->style, lv_palette_main(LV_PALETTE_BLUE));

    span = lv_spangroup_new_span(spans);
    lv_span_set_text_static(span, "not so easy to use. ");
    lv_style_set_text_color(&span->style, lv_palette_main(LV_PALETTE_INDIGO));
#if LV_FONT_MONTSERRAT_20
    lv_style_set_text_font(&span->style, &lv_font_montserrat_20);
#endif
    lv_style_set_text_decor(&span->style, LV_TEXT_DECOR_UNDERLINE);

    span = lv_spangroup_new_span(spans);
    lv_span_set_text(span, "It sometimes works as I want it. I have a dream that hope to come true. ");
    lv_style_set_text_color(&span->style, lv_palette_main(LV_PALETTE_LIME));
    lv_style_set_text_decor(&span->style, LV_TEXT_DECOR_STRIKETHROUGH);
    lv_style_set_text_opa(&span->style, LV_OPA_80);

    span = lv_spangroup_new_span(spans);
    lv_span_set_text(span, "I'll never give up! I try again and again, til it works!");
    lv_style_set_text_color(&span->style, lv_palette_main(LV_PALETTE_DEEP_ORANGE));

    lv_spangroup_refr_mode(spans);

//--------------------------------------------------------------------------
}

void loop()
{
    lv_task_handler();
    delay(5);
}
