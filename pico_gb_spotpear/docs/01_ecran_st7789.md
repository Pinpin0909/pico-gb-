# Ecran : ILI9225 -> ST7789

C'est le changement le plus lourd du portage. Deux voies possibles, choisir
UNE des deux (ne pas melanger) :

## Option A (recommandee) -- fork Staacks/Pico-GB avec TFT_eSPI

Ce fork utilise deja la lib TFT_eSPI, qui supporte nativement le ST7789.
Il suffit de renseigner le bon fichier de config, pas besoin d'ecrire un
driver bas niveau.

Dans `tft-espi-config/tft_setup.h` (ou equivalent selon la version du
fork), definir :

```c
#define ST7789_DRIVER
#define TFT_WIDTH  240
#define TFT_HEIGHT 240

#define TFT_MOSI  11
#define TFT_SCLK  10
#define TFT_CS     9
#define TFT_DC     8
#define TFT_RST   12
#define TFT_BL     7
#define TFT_BACKLIGHT_ON HIGH

#define SPI_FREQUENCY 62500000
```

Puis dans le CMakeLists.txt du fork, verifier que la variable pointe bien
vers ce fichier de config (souvent `PICO_TFT_ESPI_SETUP` ou equivalent --
regarder le CMakeLists.txt fourni par Staacks pour le nom exact).

## Option B -- driver C fourni par SpotPear

SpotPear fournit dans son wiki/exemple C un fichier d'init ST7789 complet
(sequence d'init + reglages gamma propres a leur dalle). Recuperer ce
fichier depuis leur exemple "LCD_1inch54_test" (C, pas MicroPython) et
l'integrer a la place de `lcd.c` dans le projet Pico-GB d'origine
(deltabeard/RP2040-GB), en remplacant les appels ILI9225 par les
fonctions ST7789 correspondantes (init, set_window, write_pixels).

Cette option demande plus de travail (pas de lib d'abstraction) mais
garde un controle plus fin sur les timings.

## Mise a l'echelle 160x144 -> 240x240

La Game Boy affiche du 160x144 (ratio ~1.11:1), l'ecran est carre
240x240. Deux choix, a fixer via un #define GB_SCALE_MODE :

- **Pillarbox / letterbox centre** : facteur d'echelle 1.5x -> image
  240x216, centree verticalement avec 12px de bande noire en haut et en
  bas. Le plus simple, pas de deformation.
- **Etirement plein ecran** : facteur different en X et Y (240/160=1.5,
  240/144=1.667) -> l'image est legerement etiree verticalement mais
  remplit tout l'ecran. Necessite d'adapter la boucle de blit du
  framebuffer (le sous-echantillonnage n'est plus un simple facteur
  entier).

Recommandation : commencer par le pillarbox 1.5x (plus simple a debugger),
puis passer a l'etirement une fois l'affichage valide.
