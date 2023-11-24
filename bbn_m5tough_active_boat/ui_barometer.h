
#ifndef UI_BAROMETER_H
#define UI_BAROMETER_H

#ifdef __cplusplus
extern "C" {
#endif

  lv_updatable_screen_t barometerScreen;

  static lv_obj_t *barometer_display;
  static lv_meter_indicator_t *indic_barometer;
  static lv_obj_t *pressure_label;

  static void set_pressure_value(void *indic, int32_t v) {
    lv_meter_set_indicator_value(barometer_display, (lv_meter_indicator_t *)indic, v);
  }

  /**
 * A pressure display meter
 */
  static void lv_barometer_display(lv_obj_t *parent) {
    barometer_display = lv_meter_create(parent);
    lv_obj_align(barometer_display, LV_ALIGN_CENTER, 0, 6);
    lv_obj_set_size(barometer_display, 210, 210);

    /*Add a scale first*/
    lv_meter_scale_t *scale = lv_meter_add_scale(barometer_display);
    lv_meter_set_scale_ticks(barometer_display, scale, 37, 2, 9, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_range(barometer_display, scale, -180, 180, 360, 90);

    lv_meter_scale_t *scale2 = lv_meter_add_scale(barometer_display);
    lv_meter_set_scale_ticks(barometer_display, scale2, 12, 0, 0, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(barometer_display, scale2, 1, 3, 14, lv_palette_main(LV_PALETTE_GREY), 14); /*Every tick is major*/
    lv_meter_set_scale_range(barometer_display, scale2, -150, 180, 330, 120);

    /*Add a needle line indicator*/
    indic_pressure = lv_meter_add_needle_line(barometer_display, scale, 6, lv_palette_main(LV_PALETTE_GREY), -10);

    pressure_label = lv_label_create(parent);
    lv_obj_align(pressure_label, LV_ALIGN_TOP_LEFT, 5, 2);
#if LV_FONT_MONTSERRAT_20
    lv_obj_set_style_text_font(pressure_label, &lv_font_montserrat_20, 0);
#endif
    lv_label_set_text_static(pressure_label, "Pressure:  --\nhPa");

  static void pressure_update_cb() {
    lv_label_set_text(pressure_label,
                      (String("Pressure:   ") += (fresh(shipDataModel.environment.air_outside.pressure.age) ? String(shipDataModel.environment.air_outside.pressure.hPa, 1) += "\nhPa" : String("--\nhPa")))
                        .c_str());

    set_wind_value(indic_wind, fresh(shipDataModel.environment.air_outside.pressure.age) ? shipDataModel.environment.air_outside.pressure.hPa : 0);
  }

  void init_barometerScreen() {
    barometerScreen.screen = lv_obj_create(NULL);  // Creates a Screen object
    barometerScreen.init_cb = lv_barometer_display;
    barometerScreen.update_cb = pressure_update_cb;
  }

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
