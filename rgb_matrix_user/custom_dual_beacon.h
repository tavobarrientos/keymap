#ifdef ENABLE_CUSTOM_DUAL_BEACON
    RGB_MATRIX_EFFECT(CUSTOM_DUAL_BEACON)
    #ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
        bool CUSTOM_DUAL_BEACON(effect_params_t  *params) {
            
            RGB_MATRIX_USE_LIMITS(led_min, led_max);

            HSV hsv = rgb_matrix_config.hsv;
            uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
            hsv.h = 129 - time - atan2_8(1, 3);
            hsv.v = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
            
            uint8_t scale = scale8(64, rgb_matrix_config.speed);

            for (uint8_t i = led_min; i < led_max; i++) {
                RGB_MATRIX_TEST_LED_FLAGS();
                hsv.h = rgb_matrix_config.hsv.h + scale * (g_led_config.point[i].y >> 5);
            RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
                
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
            return led_max < DRIVER_LED_TOTAL;
        }

        

    #endif
#endif