/********************************************************************************************
 * globals.h - tout ce qui est partagé par le croquis : réglages, temps réel, et liste de ce
 * qu'on envoie à TS. A inclure juste après BZO_TS.h et AVANT tous les autres fichiers.
 *******************************************************************************************/

//************************************************************************************************************
// configPage1 = page 1 du .ini : réglages généraux (32 octets) - à droite : offset dans le .ini
// Les pages de réglages restent "packed" : TS lit et écrit leurs octets directement.

struct __attribute__((packed)) config1
{
  uint8_t  sortieActive : 1;    // 0 [0:0]
  uint8_t  modeSortie   : 2;    // 0 [1:2]  0 normal, 1 inversé, 2 clignotant
  uint8_t               : 5;
  uint8_t  rapportCyclique;     // 1   %
  uint8_t  delaiExtinction;     // 2   x0.1 s
  uint8_t  canalCapteur : 3;    // 3 [0:2]  A0..A7
  uint8_t               : 5;
  uint16_t seuilRegime;         // 4   tr/min
  int16_t  offsetTemperature;   // 6   x0.1 °C
  uint16_t tempsAllumage;       // 8   ms
  uint16_t frequencePWM;        // 10  Hz
  uint16_t tensionMin;          // 12  x0.01 V
  uint16_t tensionMax;          // 14  x0.01 V
  uint8_t  libre[16];           // 16  réserve
};

// configPage2 = page 2 du .ini : courbe + table (104 octets)

struct __attribute__((packed)) config2
{
  uint8_t  courbeX[8];          // 0   température +40
  uint8_t  courbeY[8];          // 8   %
  uint16_t tableRegime[8];      // 16  tr/min
  uint8_t  tableCharge[8];      // 32  %
  uint8_t  table[8][8];         // 40  [charge][régime]
};

//************************************************************************************************************
// currentStatus : les valeurs temps réel du programme, comme dans Speeduino.
// Structure libre : types et ordre au choix, ce n'est PAS elle qui part telle quelle vers TS.
// Ce qui part vers TS est décidé plus bas, dans getTSLogEntry().

struct statuses
{
  uint8_t  secl;                // secondes depuis le démarrage (rempli par la librairie)
  uint8_t  statutTS;            // statut com/mémoire (rempli par la librairie)
  uint8_t  erreursTS;           // erreurs de com (rempli par la librairie)
  uint8_t  libre;               // libre (envoyé à 0)
  uint16_t boucles;             // tours de loop par seconde (rempli par la librairie)
  bool     sortieOn;
  bool     alarme;
  uint16_t RPM;                 // tr/min
  int16_t  temperature;         // x0.1 °C
  uint16_t tension;             // x0.01 V
  uint8_t  rapportCyclique;     // %
  uint8_t  charge;              // %
  uint8_t  sortieTable;
};

struct config1  configPage1;
struct config2  configPage2;
struct statuses currentStatus;

//************************************************************************************************************
// Log TS : liste de ce qu'on envoie à TS, octet par octet ([OutputChannels] du .ini)
// Comme getTSLogEntry() de Speeduino : TS demande un offset, on renvoie l'octet correspondant.
// Offsets 0 à 5 : bloc standard BZO_TS du .ini (secl, statut, erreurs, libre, boucles/s).
// Pour ajouter une valeur : un "case" ici + la ligne dans [OutputChannels] du .ini
// + mettre TS_LOG_TAILLE et ochBlockSize à la nouvelle taille.

#define TS_LOG_TAILLE 16        // = ochBlockSize du .ini

uint8_t getTSLogEntry(uint16_t offset)
{
  uint8_t valeur = 0;

  switch (offset)
  {
    case 0:  valeur = currentStatus.secl;                          break; // secondes
    case 1:  valeur = currentStatus.statutTS;                      break; // statut
    case 2:  valeur = currentStatus.erreursTS;                     break; // erreurs de com
    case 3:  valeur = currentStatus.libre;                         break; // libre
    case 4:  valeur = lowByte(currentStatus.boucles);              break; // boucles/s (U16)
    case 5:  valeur = highByte(currentStatus.boucles);             break;
    case 6:  valeur = (currentStatus.sortieOn ? 0x01 : 0) | (currentStatus.alarme ? 0x02 : 0); break; // bits
    case 7:  valeur = lowByte(currentStatus.RPM);                  break; // RPM (U16)
    case 8:  valeur = highByte(currentStatus.RPM);                 break;
    case 9:  valeur = lowByte((uint16_t)currentStatus.temperature);  break; // temperature (S16)
    case 10: valeur = highByte((uint16_t)currentStatus.temperature); break;
    case 11: valeur = lowByte(currentStatus.tension);              break; // tension (U16)
    case 12: valeur = highByte(currentStatus.tension);             break;
    case 13: valeur = currentStatus.rapportCyclique;               break;
    case 14: valeur = currentStatus.charge;                        break;
    case 15: valeur = currentStatus.sortieTable;                   break;
  }

  return valeur;
}
