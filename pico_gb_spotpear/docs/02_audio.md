# Audio : pas d'ampli MAX98357A sur le module SpotPear

Deux options :

## Option A -- desactiver le son (le plus simple, recommande pour un premier build)

Dans `peanut_gb.h` (ou le fichier de config du fork), mettre :

```c
#define ENABLE_SOUND 0
```

ou le flag equivalent selon le fork (`AUDIO_ENABLED`, `PEANUT_GB_HEADER_ONLY`
selon les versions -- verifier le nom exact dans le fichier de config du
fork utilise). L'emulation video/inputs n'est pas affectee.

## Option B -- sortie audio en PWM sur une broche libre

Les GPIO 19, 20, 21, 22, 28 restent libres sur ce module. Cabler un petit
haut-parleur ou piezo sur l'un d'eux (avec un filtre RC passe-bas simple,
ex. resistance 1k + condensateur 10nF vers la masse, pour lisser le PWM),
puis :

1. Initialiser une slice PWM sur la broche choisie a une frequence
   d'echantillonnage fixe (ex. 32768 Hz, frequence native de l'APU Game
   Boy geree par Peanut-GB).
2. Dans le callback audio de Peanut-GB (`gb_get_audio` ou equivalent selon
   le fork), ecrire l'echantillon 16 bits recu dans `pwm_set_chan_level()`
   apres l'avoir ramene sur l'echelle du wrap PWM configure.

C'est plus de travail et sort du cadre d'un premier portage fonctionnel --
a faire une fois l'affichage et les boutons valides.
