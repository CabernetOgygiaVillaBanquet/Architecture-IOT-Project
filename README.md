# Architecture-IOT-Project

# 🛡️ Tracker GPS pour Opérateur sur le Terrain (Arduino)

Ce projet permet de suivre en temps réel la position d'un opérateur (idéalement pensé pour un cas d'usage comme le suivi d'un démineur dans une zone à risque) à l'aide d'une carte microcontrôleur et d'un module GPS. 

Il inclut un code de lecture classique pour un vrai module GPS, ainsi qu'un **mode de simulation** très pratique pour tester la logique du code sans avoir besoin d'un signal satellite.

## 📋 Fonctionnalités

* **Acquisition de données GPS en temps réel** : Latitude, Longitude, Altitude, Vitesse.
* **Synchronisation temporelle** : Récupération de la date et de l'heure précises via les satellites.
* **Mode Simulation** : Génération de trames NMEA factices valides (avec Checksum) pour tester le code en intérieur.
* **Compatibilité nRF52840** : Code optimisé pour les cartes à démarrage rapide comme l'Arduino Nano 33 BLE Sense.

# Membres

* **Nicolas Cholin
* **Badis Dridi
* **Thomas Jouvenceau
