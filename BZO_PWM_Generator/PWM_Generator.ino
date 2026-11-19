
#include "BZO_PWM_Generator.h"

#define PinOUT1 PB0
#define PinOUT2 PB1
#define PinOUT3 PB10
#define PinOUT4 PB11

#define PinPOTvalue PA0
#define Frequence   150      //Hz
#define Duty        10       //%
#define WorkingValueMIN 50   //seuil min de traitement de la valeur
#define WorkingValueMAX 900  //seuil max de traitement de la valeur
#define DutyMIN   10         //valeur de Duty au seuil min %
#define DutyMAX   90         //valeur de Duty au seuil max %

uint16_t PotValue = 0;

void setup() {

  pinMode(PinPOTvalue, INPUT_ANALOG);
  //( Channel, Pin, Frequence, Duty, Valeur MIN, Valeur MAX, Duty/Freq MIN, Duty/Freq MAX)
  init_PWMG(1, PinOUT1, Frequence, 0, WorkingValueMIN, WorkingValueMAX, DutyMIN, DutyMAX);
  init_PWMG(2, PinOUT2, Frequence, 0, WorkingValueMIN, WorkingValueMAX, 90, 10);
  init_PWMG(3, PinOUT3, 0, Duty, WorkingValueMIN, WorkingValueMAX, 1, 100);
  init_PWMG(4, PinOUT4, 0, Duty, WorkingValueMIN, WorkingValueMAX, 100, 1);
}

void loop() {

//On calcule le Duty souhaité
  PotValue = analogRead(PinPOTvalue); 
  BZO_PWMG(1, PotValue);
  BZO_PWMG(2, PotValue);
  BZO_PWMG(3, PotValue);
  BZO_PWMG(4, PotValue);
}
