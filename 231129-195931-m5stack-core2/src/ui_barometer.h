
#ifndef UI_BAROMETER_H
#define UI_BAROMETER_H

#ifdef __cplusplus
extern "C"
{
#endif

  lv_updatable_screen_t barometerScreen;

  static lv_obj_t *pressure_label;
  static lv_obj_t *pressure__title_label;
  static lv_obj_t *temperature_label;
  static lv_obj_t *temperature_title_label;

  /**
   * A pressure display meter
   */
  static void lv_barometer_display(lv_obj_t *parent)
  {
    temperature_title_label = lv_label_create(parent);
    lv_obj_align(temperature_title_label, LV_ALIGN_CENTER, 0, -80);
#if LV_FONT_MONTSERRAT_20
    lv_obj_set_style_text_font(temperature_title_label, &lv_font_montserrat_20, 0);
#endif
    lv_label_set_text_static(temperature_title_label, "temperature");

    temperature_label = lv_label_create(parent);
    lv_obj_align(temperature_label, LV_ALIGN_CENTER, 0, -40);
#if LV_FONT_MONTSERRAT_48
    lv_obj_set_style_text_font(temperature_label, &lv_font_montserrat_48, 0);
#endif
    lv_label_set_text_static(temperature_label, " C");

    pressure__title_label = lv_label_create(parent);
    lv_obj_align(pressure__title_label, LV_ALIGN_CENTER, 0, 20);
#if LV_FONT_MONTSERRAT_20
    lv_obj_set_style_text_font(pressure__title_label, &lv_font_montserrat_20, 0);
#endif
    lv_label_set_text_static(pressure__title_label, "pressure");

    pressure_label = lv_label_create(parent);
    lv_obj_align(pressure_label, LV_ALIGN_CENTER, 0, 60);
#if LV_FONT_MONTSERRAT_48
    lv_obj_set_style_text_font(pressure_label, &lv_font_montserrat_48, 0);
#endif
    lv_label_set_text_static(pressure_label, " hPa");
  }

  static void pressure_update_cb()
  {
    lv_label_set_text(pressure_label,
                      ((fresh(shipDataModel.environment.air_outside.pressure.age) ? String(shipDataModel.environment.air_outside.pressure.hPa, 1) += " hPa" : String("--\n hPa")))
                          .c_str());

    lv_label_set_text(temperature_label,
                      ((fresh(shipDataModel.environment.air_outside.temp_deg_C.age) ? String(shipDataModel.environment.air_outside.temp_deg_C.deg_C, 1) += " C" : String("-- C")))
                          .c_str());
  }

  void init_barometerScreen()
  {
    barometerScreen.screen = lv_obj_create(NULL); // Creates a Screen object
    barometerScreen.init_cb = lv_barometer_display;
    barometerScreen.update_cb = pressure_update_cb;
  }

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
