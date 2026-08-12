// spotpear_pins.h
// Brochage du module SpotPear "Raspberry Pi Pico RP2040 1.54inch LCD
// Display Screen Game ST7789" -- a coller dans le projet Pico-GB /
// RP2040-GB a la place des defines d'origine (souvent dans lcd.h / config.h).

#ifndef SPOTPEAR_PINS_H
#define SPOTPEAR_PINS_H

// ---------- Ecran ST7789, SPI1 materiel ----------
#define TFT_SCK_PIN     10
#define TFT_MOSI_PIN    11
#define TFT_DC_PIN      8
#define TFT_RST_PIN     12
#define TFT_CS_PIN      9
#define TFT_BL_PIN      7      // retroeclairage pilote en PWM, PAS en simple GPIO on/off
#define TFT_SPI_PORT    spi1
#define TFT_SPI_BAUD    (62500 * 1000)  // a ajuster selon marge de timing constatee

#define TFT_WIDTH       240
#define TFT_HEIGHT      240

// ---------- Boutons, actifs a l'etat bas, pull-up interne ----------
#define BTN_UP_PIN      16
#define BTN_DOWN_PIN    14
#define BTN_LEFT_PIN    13
#define BTN_RIGHT_PIN   17
#define BTN_A_PIN       3
#define BTN_B_PIN       6
#define BTN_X_PIN       2   // pas d'equivalent Game Boy -> libre pour menu/fast-forward
#define BTN_Y_PIN       4   // pas d'equivalent Game Boy -> libre pour save-state
#define BTN_SELECT_PIN  26
#define BTN_START_PIN   27
#define BTN_L_PIN       18  // pas d'equivalent Game Boy -> libre
#define BTN_R_PIN       1   // pas d'equivalent Game Boy -> libre

#endif // SPOTPEAR_PINS_H
