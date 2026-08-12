# Portage Pico-GB -> module SpotPear ST7789 -- avec Bubble Ghost embarque

## Important -- ce que contient ce paquet, et ce qu'il ne contient PAS

Je n'ai pas pu compiler de firmware `.uf2` fonctionnel depuis cet
environnement : je n'ai ni acces reseau (impossible de recuperer le SDK
Raspberry Pi Pico ni le depot source RP2040-GB/Pico-GB depuis GitHub), ni
la chaine de compilation ARM (`arm-none-eabi-gcc`, `cmake`) installee ici.
Un firmware `.uf2` "compile" que je vous donnerais sans ces outils serait
forcement invente -- je ne fais pas ca.

Ce que je vous donne a la place, c'est tout le travail de portage
reellement fait :

- toutes les modifications de code discutees precedemment, ecrites et
  pretes a coller dans le projet ;
- votre ROM Bubble Ghost deja convertie en tableau C pret a l'emploi
  (`rom/bubble_ghost_rom.h`, genere directement depuis le fichier que vous
  avez fourni) ;
- les commandes exactes a lancer chez vous pour obtenir le `.uf2` en
  quelques minutes une fois le SDK Pico installe (etapes ci-dessous).

## Contenu du paquet

```
include/spotpear_pins.h     -> brochage complet du module (ecran + boutons)
src/input_spotpear.c        -> lecture des boutons, pret a brancher sur Peanut-GB
src/backlight_pwm.c         -> init PWM du retroeclairage (obligatoire, GP7)
rom/bubble_ghost_rom.h      -> Bubble Ghost converti en tableau C (32768 octets)
tools/rom2h.py              -> le script utilise pour la conversion (reutilisable)
docs/01_ecran_st7789.md     -> les deux options pour le driver ecran + scaling
docs/02_audio.md            -> desactivation ou sortie PWM du son
```

## Etapes pour obtenir le .uf2, chez vous

Sur une machine avec `git`, `cmake` et le toolchain `arm-none-eabi-gcc`
installes (ou via le script d'install officiel Raspberry Pi) :

```bash
# 1. SDK Pico
git clone -b master https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk && git submodule update --init && cd ..
export PICO_SDK_PATH=$(pwd)/pico-sdk

# 2. Le fork recommande (TFT_eSPI deja integre, cf docs/01_ecran_st7789.md)
git clone https://github.com/Staacks/pico-gb.git
cd pico-gb

# 3. Copier les fichiers de ce paquet dans le projet
cp ../include/spotpear_pins.h  include/
cp ../src/input_spotpear.c     src/
cp ../src/backlight_pwm.c      src/
cp ../rom/bubble_ghost_rom.h   src/rom.h

# 4. Editer tft-espi-config/tft_setup.h avec les valeurs de
#    docs/01_ecran_st7789.md (Option A)

# 5. Dans src/main.c (ou equivalent) :
#    - #include "spotpear_pins.h" et "rom.h"
#    - appeler spotpear_input_init() et spotpear_backlight_init() au demarrage
#    - brancher spotpear_input_read() sur le joypad Peanut-GB (voir le
#      commentaire en bas de input_spotpear.c)
#    - pointer gb_init() sur le tableau bubble_ghost_rom au lieu de lire
#      une carte SD

# 6. Build
mkdir build && cd build
cmake -DPICO_BOARD=pico ..
make -j4

# -> genere build/pico-gb.uf2
```

## Flashage

Maintenir le bouton BOOTSEL du Pico, le brancher en USB, relacher le
bouton : il apparait comme un disque `RPI-RP2`. Glisser le fichier
`pico-gb.uf2` dessus, le Pico redemarre automatiquement dessus.

## Si vous voulez que j'aille plus loin depuis ici

Je peux :
- detailler encore le glue code de `main.c` (boucle principale, ou
  brancher exactement chaque fonction) ;
- ecrire la variante "etirement plein ecran" du scaling au lieu du
  pillarbox ;
- ecrire la sortie audio PWM complete (Option B du fichier audio).

Dites-moi lequel vous interesse le plus et je le fais tout de suite.
