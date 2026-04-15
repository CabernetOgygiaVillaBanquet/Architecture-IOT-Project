/*
 * Simulation d'un capteur GPS avec données NMEA factices.
 * Basé sur la bibliothèque TinyGPS++
 */

#include <TinyGPS++.h>

// Création de l'objet TinyGPS++
TinyGPSPlus gps; 

// Voici des trames NMEA factices valides (Coordonnées d'exemple, vitesse de 0.67 nœuds, etc.)
// Ces trames contiennent les informations de localisation, d'altitude, de vitesse et de temps.
const char *tramesNMEAFactices = 
  "$GPRMC,045103.000,A,3014.1984,N,09749.2872,W,0.67,161.46,030913,,,A*7C\r\n"
  "$GPGGA,045104.000,3014.1984,N,09749.2872,W,1,09,1.2,211.6,M,-22.5,M,,0000*62\r\n";

void setup() {
  Serial.begin(9600);
  
  // --- AJOUT INDISPENSABLE POUR LES CARTES nRF52840 ---
  // Met le programme en pause tant que le Moniteur Série n'est pas ouvert
  while (!Serial) {
    delay(10);
  }
  // ----------------------------------------------------
  
  Serial.println(F("======================================="));
  Serial.println(F("   Simulation du Module GPS (Arduino)  "));
  Serial.println(F("======================================="));
  Serial.println();
}

void loop() {
  // On simule l'arrivée des données sur le port série en lisant notre chaîne de caractères
  // caractère par caractère, comme le ferait gpsSerial.read()
  for (const char *p = tramesNMEAFactices; *p != '\0'; p++) {
    
    // gps.encode() renvoie "true" chaque fois qu'une phrase NMEA complète et valide a été lue
    if (gps.encode(*p)) {
      afficherInfosGPS();
    }
  }

  // On attend 2 secondes avant de renvoyer la trame factice 
  // pour simuler la mise à jour périodique du GPS sans inonder le moniteur série.
  delay(2000);
}

// Fonction qui regroupe votre logique d'affichage
void afficherInfosGPS() {
  Serial.println(F("----- NOUVELLES DONNÉES REÇUES -----"));

  // 1. LATITUDE ET LONGITUDE
  if (gps.location.isValid()) {
    Serial.print(F("- latitude: "));
    Serial.println(gps.location.lat(), 6); // , 6 pour afficher 6 décimales

    Serial.print(F("- longitude: "));
    Serial.println(gps.location.lng(), 6);
  } else {
    Serial.println(F("- location: INVALID"));
  }

  // 2. ALTITUDE
  Serial.print(F("- altitude: "));
  if (gps.altitude.isValid()) {
    Serial.print(gps.altitude.meters());
    Serial.println(F(" m"));
  } else {
    Serial.println(F("INVALID"));
  }

  // 3. VITESSE
  Serial.print(F("- speed: "));
  if (gps.speed.isValid()) {
    Serial.print(gps.speed.kmph());
    Serial.println(F(" km/h"));
  } else {
    Serial.println(F("INVALID"));
  }

  // 4. DATE ET HEURE
  Serial.print(F("- GPS date&time: "));
  if (gps.date.isValid() && gps.time.isValid()) {
    Serial.print(gps.date.year());
    Serial.print(F("-"));
    
    // Ajout d'un 0 si le mois ou le jour est < 10 pour un bel affichage
    if (gps.date.month() < 10) Serial.print(F("0"));
    Serial.print(gps.date.month());
    Serial.print(F("-"));
    
    if (gps.date.day() < 10) Serial.print(F("0"));
    Serial.print(gps.date.day());
    Serial.print(F(" "));
    
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.println(gps.time.second());
  } else {
    Serial.println(F("INVALID"));
  }

  Serial.println();
}
