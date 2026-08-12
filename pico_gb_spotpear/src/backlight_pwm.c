// backlight_pwm.c
// Sur le module d'origine (ILI9225), le retroeclairage etait souvent
// cable direct sur 3V3. Sur le module SpotPear, GP7 pilote le
// retroeclairage en PWM : sans cette init, l'ecran reste noir meme
// si le driver ST7789 fonctionne correctement.

#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "spotpear_pins.h"

static uint bl_slice;
static uint bl_channel;

void spotpear_backlight_init(void)
{
    gpio_set_function(TFT_BL_PIN, GPIO_FUNC_PWM);
    bl_slice = pwm_gpio_to_slice_num(TFT_BL_PIN);
    bl_channel = pwm_gpio_to_channel(TFT_BL_PIN);

    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_clkdiv(&cfg, 4.f);
    pwm_config_set_wrap(&cfg, 255);
    pwm_init(bl_slice, &cfg, true);

    pwm_set_chan_level(bl_slice, bl_channel, 200); // luminosite par defaut ~78%
}

// level : 0 (eteint) a 255 (maximum)
void spotpear_backlight_set(uint8_t level)
{
    pwm_set_chan_level(bl_slice, bl_channel, level);
}
