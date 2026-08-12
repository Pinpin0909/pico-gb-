// input_spotpear.c
// Remplace le polling de boutons d'origine (breadboard libre) par celui
// du module SpotPear. A appeler a la place de gb_input_init()/lit_boutons()
// dans le fichier principal du projet Pico-GB (souvent main.c ou input.c).
//
// Peanut-GB attend une structure gb_s->direct.joypad_bits ou un callback
// gb_input(). Ci-dessous une version generique independante de la version
// exacte du fork utilise -- adapter les noms de champs si besoin.

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "spotpear_pins.h"

typedef struct {
    bool up, down, left, right;
    bool a, b, start, select;
    // boutons additionnels du module, sans equivalent Game Boy
    bool x, y, l, r;
} spotpear_buttons_t;

static void spotpear_input_pin_init(uint pin)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);   // actifs a l'etat bas
}

void spotpear_input_init(void)
{
    spotpear_input_pin_init(BTN_UP_PIN);
    spotpear_input_pin_init(BTN_DOWN_PIN);
    spotpear_input_pin_init(BTN_LEFT_PIN);
    spotpear_input_pin_init(BTN_RIGHT_PIN);
    spotpear_input_pin_init(BTN_A_PIN);
    spotpear_input_pin_init(BTN_B_PIN);
    spotpear_input_pin_init(BTN_SELECT_PIN);
    spotpear_input_pin_init(BTN_START_PIN);
    spotpear_input_pin_init(BTN_X_PIN);
    spotpear_input_pin_init(BTN_Y_PIN);
    spotpear_input_pin_init(BTN_L_PIN);
    spotpear_input_pin_init(BTN_R_PIN);
}

void spotpear_input_read(spotpear_buttons_t *out)
{
    // gpio_get() renvoie 1 au repos (pull-up), 0 quand presse -> on inverse
    out->up     = !gpio_get(BTN_UP_PIN);
    out->down   = !gpio_get(BTN_DOWN_PIN);
    out->left   = !gpio_get(BTN_LEFT_PIN);
    out->right  = !gpio_get(BTN_RIGHT_PIN);
    out->a      = !gpio_get(BTN_A_PIN);
    out->b      = !gpio_get(BTN_B_PIN);
    out->select = !gpio_get(BTN_SELECT_PIN);
    out->start  = !gpio_get(BTN_START_PIN);
    out->x      = !gpio_get(BTN_X_PIN);
    out->y      = !gpio_get(BTN_Y_PIN);
    out->l      = !gpio_get(BTN_L_PIN);
    out->r      = !gpio_get(BTN_R_PIN);
}

// Exemple de branchement vers Peanut-GB (a adapter au nom exact du champ
// bitfield joypad_bits dans le fork utilise -- verifier peanut_gb.h) :
//
// void gb_update_joypad(struct gb_s *gb)
// {
//     spotpear_buttons_t btn;
//     spotpear_input_read(&btn);
//     gb->direct.joypad_bits.up     = !btn.up;
//     gb->direct.joypad_bits.down   = !btn.down;
//     gb->direct.joypad_bits.left   = !btn.left;
//     gb->direct.joypad_bits.right  = !btn.right;
//     gb->direct.joypad_bits.a      = !btn.a;
//     gb->direct.joypad_bits.b      = !btn.b;
//     gb->direct.joypad_bits.select = !btn.select;
//     gb->direct.joypad_bits.start  = !btn.start;
//     // btn.x / btn.y / btn.l / btn.r restent libres : menu, save-state,
//     // fast-forward, reglage retroeclairage, etc.
// }
