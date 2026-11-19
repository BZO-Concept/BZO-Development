/********************************************************************************************
 *
 * Exemple d'utilisation de BZO_TS.h (base de communication TunerStudio)
 * A utiliser avec le fichier Exemple_TS.ini - mode d'emploi complet en tête de BZO_TS.h
 *
 * Mêmes noms que Speeduino : configPageX pour les réglages, currentStatus pour le temps réel.
 * (ici configPage1 = page 1 du .ini, configPage2 = page 2 : le numéro suit celui du .ini)
 *
 * Contact: www.bzo-concept.fr
 * v1.3 03/11/26
 *
 *******************************************************************************************/

#define TS_SIGNATURE      "BZO GPIO Base TS v1.0"   // = "signature" du .ini (TS : commence par "Speeduino")
//#define TS_PROTOCOLE_CRC                     // gros MCU (F103, F405...)
#define TS_EEPROM_VERSION 1                    // +1 à chaque changement de config1 / config2
#include "BZO_TS.h"            // 1. la lib
#include "globals.h"           // 2. réglages, currentStatus et liste du log TS : AVANT le reste

//************************************************************************************************************
// Boutons du .ini

bool SortieForcee = false;

void SortieON()  { SortieForcee = true;  }   // "E\x01\x01"
void SortieOFF() { SortieForcee = false; }   // "E\x01\x02"

//************************************************************************************************************

void setup()
{
  TS.addPage(1, configPage1);
  TS.addPage(2, configPage2);
  TS.setOutputs(getTSLogEntry, TS_LOG_TAILLE, currentStatus);   // temps réel façon Speeduino (liste dans globals.h)
  TS.addCommand(0x0101, SortieON);   // bouton "E\x01\x01" du .ini : on recopie les 2 octets après le E
  TS.addCommand(0x0102, SortieOFF);  // bouton "E\x01\x02"
  //Chaque fois que TS envoie la commande "E\x01\x01" (0x0101), la librairie appelle SortieON() une fois, pendant le TS.update()
  TS.begin(Serial, 115200);          // carte neuve : réglages à 0, charger la base tune (.msq) dans TS
  // ATTENTION STM32 : selon la carte choisie dans l'IDE, "Serial" n'est pas forcément l'UART câblée vers le PC
  // (F103 générique : Serial = USART2 sur PA3/PA2). Vérifier les broches, sinon déclarer l'UART à la main,
  // par exemple HardwareSerial SerialTS(PA10, PA9); puis TS.begin(SerialTS, 115200);
  // Tout ce qui lit les réglages (configPageX) au démarrage se fait APRÈS TS.begin() : c'est lui qui les relit en mémoire.
}

void loop()
{
  TS.update();

  bool sortieActive = configPage1.sortieActive || SortieForcee;

  // Valeurs simulées : à remplacer par les vraies mesures
  currentStatus.RPM             = (millis() / 10) % 7000;
  currentStatus.temperature     = 853 + configPage1.offsetTemperature;
  currentStatus.tension         = 1380;
  currentStatus.charge          = (millis() / 100) % 101;
  if (sortieActive == true) {currentStatus.rapportCyclique = configPage1.rapportCyclique;}
  else                      {currentStatus.rapportCyclique = 0;}
  currentStatus.sortieTable     = TS.table(configPage2.tableRegime, configPage2.tableCharge,
                                           configPage2.table, currentStatus.RPM, currentStatus.charge);
  currentStatus.sortieOn        = sortieActive;
  currentStatus.alarme          = (currentStatus.tension < configPage1.tensionMin);
}
