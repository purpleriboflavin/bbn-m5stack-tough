#ifndef UI_WEATHER_H
#define UI_WEATHER_H

#ifdef __cplusplus
extern "C"
{
#endif

        /*

         Look at:

         https://github.com/fandonov/weatherstation
         http://www.beteljuice.co.uk/zambretti/forecast.html

        */

        lv_updatable_screen_t weatherScreen;

        static lv_obj_t *weather_time_label;
        static lv_obj_t *weather_localtime_label;
        static lv_obj_t *weather_sunrise_label;
        static lv_obj_t *weather_sunset_label;
        static lv_obj_t *weather_moonrise_label;
        static lv_obj_t *weather_moonset_label;

        /**
         * A weather display
         */
        static void lv_weather_display(lv_obj_t *parent)
        {

                lv_obj_t *main_label = lv_label_create(parent);
                lv_obj_align(main_label, LV_ALIGN_CENTER, 0, -105);
                lv_label_set_recolor(main_label, true);
                lv_label_set_text_static(main_label, "SUN  #0080ff " LV_SYMBOL_IMAGE " #");

                weather_time_label = lv_label_create(parent);
                lv_obj_align(weather_time_label, LV_ALIGN_TOP_LEFT, 10, 35);
#if LV_FONT_MONTSERRAT_20
                lv_obj_set_style_text_font(weather_time_label, &lv_font_montserrat_20, 0);
#endif
                lv_label_set_text_static(weather_time_label, "UTC Time:");

                weather_localtime_label = lv_label_create(parent);
                lv_obj_align(weather_localtime_label, LV_ALIGN_TOP_LEFT, 10, 70);
#if LV_FONT_MONTSERRAT_20
                lv_obj_set_style_text_font(weather_localtime_label, &lv_font_montserrat_20, 0);
#endif
                lv_label_set_text_static(weather_localtime_label, "Local Time:");

                weather_sunrise_label = lv_label_create(parent);
                lv_obj_align(weather_sunrise_label, LV_ALIGN_TOP_LEFT, 10, 105);
#if LV_FONT_MONTSERRAT_20
                lv_obj_set_style_text_font(weather_sunrise_label, &lv_font_montserrat_20, 0);
#endif
                lv_label_set_text_static(weather_sunrise_label, "Sunrise:");

                weather_sunset_label = lv_label_create(parent);
                lv_obj_align(weather_sunset_label, LV_ALIGN_TOP_LEFT, 10, 140);
#if LV_FONT_MONTSERRAT_20
                lv_obj_set_style_text_font(weather_sunset_label, &lv_font_montserrat_20, 0);
#endif
                lv_label_set_text_static(weather_sunset_label, "Sunset:");

                weather_moonrise_label = lv_label_create(parent);
                lv_obj_align(weather_moonrise_label, LV_ALIGN_TOP_LEFT, 10, 175);
#if LV_FONT_MONTSERRAT_20
                lv_obj_set_style_text_font(weather_moonrise_label, &lv_font_montserrat_20, 0);
#endif
                lv_label_set_text_static(weather_moonrise_label, "Moonrise:");

                weather_moonset_label = lv_label_create(parent);
                lv_obj_align(weather_moonset_label, LV_ALIGN_TOP_LEFT, 10, 210);
#if LV_FONT_MONTSERRAT_20
                lv_obj_set_style_text_font(weather_moonset_label, &lv_font_montserrat_20, 0);
#endif
                lv_label_set_text_static(weather_moonset_label, "Moonset:");
        }

        static String hour_format(float hr)
        {
                static char bufferTime[16];
                if (hr < 0)
                {
                        hr = 24 + hr;
                }
                int h = hr;
                int m = (hr - h) * 60;
                int s = ((hr - h) * 60 - m) * 60;
                sprintf(bufferTime, "%02d:%02d:%02d", h, m, s);
                return String(bufferTime);
        }

        static void weather_update_cb()
        {
                M5.Rtc.GetDate(&RTCdate);
                M5.Rtc.GetTime(&RTCtime);

                tm utcTime = {};
                utcTime.tm_sec = RTCtime.Seconds;
                utcTime.tm_min = RTCtime.Minutes;
                utcTime.tm_hour = RTCtime.Hours;
                utcTime.tm_mday = RTCdate.Date;
                utcTime.tm_mon = RTCdate.Month;
                utcTime.tm_year = RTCdate.Year;

                tm localTime = utcToTimeWithOffset(utcTime);

                lv_label_set_text(weather_time_label,
                                  (String(F("UTC Time:                   ")) + tmToTimeString(utcTime))
                                      .c_str());
                lv_label_set_text(weather_localtime_label,
                                  (String(F("Local Time:                 ")) + tmToTimeString(localTime))
                                      .c_str());
                lv_label_set_text(weather_sunrise_label,
                                  (String(F("Sunrise:                        ")) + tmToTimeString(utcToTimeWithOffset(shipDataModel.environment.sunrise.t)))
                                      .c_str());
                lv_label_set_text(weather_sunset_label,
                                  (String(F("Sunset:                         ")) + tmToTimeString(utcToTimeWithOffset(shipDataModel.environment.sunset.t)))
                                      .c_str());
                lv_label_set_text(weather_moonrise_label,
                                  (String(F("Moonrise:                    ")) + tmToTimeString(utcToTimeWithOffset(shipDataModel.environment.moonrise.t)))
                                      .c_str());
                lv_label_set_text(weather_moonset_label,
                                  (String(F("Moonset:                     ")) + tmToTimeString(utcToTimeWithOffset(shipDataModel.environment.moonset.t)))
                                      .c_str());
        }

        void init_weatherScreen()
        {
                weatherScreen.screen = lv_obj_create(NULL); // Creates a Screen object
                weatherScreen.init_cb = lv_weather_display;
                weatherScreen.update_cb = weather_update_cb;
        }

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
