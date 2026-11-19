/************************************************************************
 * Génerateur PWM 4 canaux par BZO Concept, modulation de fréquence ou modulation de Duty.
 * Non dépendant des timers, broches PWM, interruptions. Compatible tout processeurs.
 * Fréquence 1 à 1000Hz sur les 4 canaux indépendants. Duty exprimée en %. valeur ref 8 ou 16bits.
 * 
 * Fonctions:
 * 
 * init_PWMG():
 * exemple: init_PWMG(1, PinOUT1, Frequence, 0, WorkingValueMIN, WorkingValueMAX, DutyMIN, DutyMAX);
 * 
 * Fonction qui initialise le canal et la broche OUT.
 * 1) numero de canal (1 - 4)
 * 2) broche utilisée pour la sortie (initialisation faite dans cette fonction)(uint8_t)
 * 3) Frequence en Hz pour modulation Duty. mettre 0 pour mode modulation de fréquence (uint16_t)
 * 4) Duty en % pour modulation fréquence. mettre 0 pour mode modulation de Duty (uint8_t)
 * 5) seuil minimum voulu pour la valeur d'entrée. en dessous de ce seuil, la valeur sera mise a ce seuil dans la fonction (uint16_t)
 * 6) seuil maximum voulu pour la valeur d'entrée. au dessus de ce seuil, la valeur sera mise a ce seuil dans la fonction (uint16_t)
 * 7) valeur de sortie minimum, Duty (1 - 99%) ou fréquence (Hz) (uint16_t)
 * 8) valeur de sortie maximum, Duty (1 - 99%) ou fréquence (Hz) (uint16_t)
 * * **********La fonction supporte les inversions***************
 * 
 * BZO_PWMG();
 * exemple: BZO_PWMG(1, PotValue);
 * 
 * 1) numero de canal (1 - 4)
 * 2) valeur utilisée pour la modulation, 8 ou 16bits (uint16_t)
 * 
 * Testé sur STM32F405, théoriquement OK pour Speeduino, 22/02/2026
 ************************************************************************/

 
#define DUTY_MODULATION 1
#define FREQ_MODULATION 2

uint8_t Pin_PWMG = 0;
uint8_t Mode_PWMG = 0;
uint8_t Duty_PWMG = 0;
uint16_t Frequence_PWMG = 0;
uint16_t ValueMIN_PWMG = 0;
uint16_t ValueMAX_PWMG = 0;
uint16_t Duty_FreqMIN_PWMG = 0;
uint16_t Duty_FreqMAX_PWMG = 0;
uint32_t Interval_Micros_PWMG = 0;
uint32_t Interval_Low_PWMG = 0;
bool PinisHigh_PWMG = false;
uint32_t High_Counter_PWMG = 0;

uint8_t Pin_PWMG1 = 0;
uint8_t Mode_PWMG1 = 0;
uint8_t Duty_PWMG1 = 0;
uint16_t ValueMIN_PWMG1 = 0;
uint16_t ValueMAX_PWMG1 = 0;
uint16_t Duty_FreqMIN_PWMG1 = 0;
uint16_t Duty_FreqMAX_PWMG1 = 0;
uint32_t Interval_Micros_PWMG1 = 0;
bool PinisHigh_PWMG1 = false;
uint32_t High_Counter_PWMG1 = 0;

uint8_t Pin_PWMG2 = 0;
uint8_t Mode_PWMG2 = 0;
uint8_t Duty_PWMG2 = 0;
uint16_t ValueMIN_PWMG2 = 0;
uint16_t ValueMAX_PWMG2 = 0;
uint16_t Duty_FreqMIN_PWMG2 = 0;
uint16_t Duty_FreqMAX_PWMG2 = 0;
uint32_t Interval_Micros_PWMG2 = 0;
bool PinisHigh_PWMG2 = false;
uint32_t High_Counter_PWMG2 = 0;

uint8_t Pin_PWMG3 = 0;
uint8_t Mode_PWMG3 = 0;
uint8_t Duty_PWMG3 = 0;
uint16_t ValueMIN_PWMG3 = 0;
uint16_t ValueMAX_PWMG3 = 0;
uint16_t Duty_FreqMIN_PWMG3 = 0;
uint16_t Duty_FreqMAX_PWMG3 = 0;
uint32_t Interval_Micros_PWMG3 = 0;
bool PinisHigh_PWMG3 = false;
uint32_t High_Counter_PWMG3 = 0;

uint8_t Pin_PWMG4 = 0;
uint8_t Mode_PWMG4 = 0;
uint8_t Duty_PWMG4 = 0;
uint16_t ValueMIN_PWMG4 = 0;
uint16_t ValueMAX_PWMG4 = 0;
uint16_t Duty_FreqMIN_PWMG4 = 0;
uint16_t Duty_FreqMAX_PWMG4 = 0;
uint32_t Interval_Micros_PWMG4 = 0;
bool PinisHigh_PWMG4 = false;
uint32_t High_Counter_PWMG4 = 0;


void CheckConstantsPWMG(uint8_t Channel){

  switch(Channel){
    case 1 :
      Pin_PWMG = Pin_PWMG1;
      Mode_PWMG = Mode_PWMG1;
      Duty_PWMG = Duty_PWMG1;
      ValueMIN_PWMG = ValueMIN_PWMG1;
      ValueMAX_PWMG = ValueMAX_PWMG1;
      Duty_FreqMIN_PWMG = Duty_FreqMIN_PWMG1;
      Duty_FreqMAX_PWMG = Duty_FreqMAX_PWMG1;
      Interval_Micros_PWMG = Interval_Micros_PWMG1;
      PinisHigh_PWMG = PinisHigh_PWMG1;
      High_Counter_PWMG = High_Counter_PWMG1;
    break;

    case 2 :
      Pin_PWMG = Pin_PWMG2;
      Mode_PWMG = Mode_PWMG2;
      Duty_PWMG = Duty_PWMG2;
      ValueMIN_PWMG = ValueMIN_PWMG2;
      ValueMAX_PWMG = ValueMAX_PWMG2;
      Duty_FreqMIN_PWMG = Duty_FreqMIN_PWMG2;
      Duty_FreqMAX_PWMG = Duty_FreqMAX_PWMG2;
      Interval_Micros_PWMG = Interval_Micros_PWMG2;
      PinisHigh_PWMG = PinisHigh_PWMG2;
      High_Counter_PWMG = High_Counter_PWMG2;
    break;

    case 3 :
      Pin_PWMG = Pin_PWMG3;
      Mode_PWMG = Mode_PWMG3;
      Duty_PWMG = Duty_PWMG3;
      ValueMIN_PWMG = ValueMIN_PWMG3;
      ValueMAX_PWMG = ValueMAX_PWMG3;
      Duty_FreqMIN_PWMG = Duty_FreqMIN_PWMG3;
      Duty_FreqMAX_PWMG = Duty_FreqMAX_PWMG3;
      Interval_Micros_PWMG = Interval_Micros_PWMG3;
      PinisHigh_PWMG = PinisHigh_PWMG3;
      High_Counter_PWMG = High_Counter_PWMG3;
    break;
    
    case 4 :
      Pin_PWMG = Pin_PWMG4;
      Mode_PWMG = Mode_PWMG4;
      Duty_PWMG = Duty_PWMG4;
      ValueMIN_PWMG = ValueMIN_PWMG4;
      ValueMAX_PWMG = ValueMAX_PWMG4;
      Duty_FreqMIN_PWMG = Duty_FreqMIN_PWMG4;
      Duty_FreqMAX_PWMG = Duty_FreqMAX_PWMG4;
      Interval_Micros_PWMG = Interval_Micros_PWMG4;
      PinisHigh_PWMG = PinisHigh_PWMG4;
      High_Counter_PWMG = High_Counter_PWMG4;
    break;
  }
}

void RefreshConstantsPWMG(uint8_t Channel){

  switch(Channel){
    case 1 :
      Pin_PWMG1 = Pin_PWMG;
      Mode_PWMG1 = Mode_PWMG;
      Duty_PWMG1 = Duty_PWMG;
      ValueMIN_PWMG1 = ValueMIN_PWMG;
      ValueMAX_PWMG1 = ValueMAX_PWMG;
      Duty_FreqMIN_PWMG1 = Duty_FreqMIN_PWMG;
      Duty_FreqMAX_PWMG1 = Duty_FreqMAX_PWMG;
      Interval_Micros_PWMG1 = Interval_Micros_PWMG;
      PinisHigh_PWMG1 = PinisHigh_PWMG;
      High_Counter_PWMG1 = High_Counter_PWMG;
    break;

    case 2 :
      Pin_PWMG2 = Pin_PWMG;
      Mode_PWMG2 = Mode_PWMG;
      Duty_PWMG2 = Duty_PWMG;
      ValueMIN_PWMG2 = ValueMIN_PWMG;
      ValueMAX_PWMG2 = ValueMAX_PWMG;
      Duty_FreqMIN_PWMG2 = Duty_FreqMIN_PWMG;
      Duty_FreqMAX_PWMG2 = Duty_FreqMAX_PWMG;
      Interval_Micros_PWMG2 = Interval_Micros_PWMG;
      PinisHigh_PWMG2 = PinisHigh_PWMG;
      High_Counter_PWMG2 = High_Counter_PWMG;
    break;

    case 3 :
      Pin_PWMG3 = Pin_PWMG;
      Mode_PWMG3 = Mode_PWMG;
      Duty_PWMG3 = Duty_PWMG;
      ValueMIN_PWMG3 = ValueMIN_PWMG;
      ValueMAX_PWMG3 = ValueMAX_PWMG;
      Duty_FreqMIN_PWMG3 = Duty_FreqMIN_PWMG;
      Duty_FreqMAX_PWMG3 = Duty_FreqMAX_PWMG;
      Interval_Micros_PWMG3 = Interval_Micros_PWMG;
      PinisHigh_PWMG3 = PinisHigh_PWMG;
      High_Counter_PWMG3 = High_Counter_PWMG;
    break;
    
    case 4 :
      Pin_PWMG4 = Pin_PWMG;
      Mode_PWMG4 = Mode_PWMG;
      Duty_PWMG4 = Duty_PWMG;
      ValueMIN_PWMG4 = ValueMIN_PWMG;
      ValueMAX_PWMG4 = ValueMAX_PWMG;
      Duty_FreqMIN_PWMG4 = Duty_FreqMIN_PWMG;
      Duty_FreqMAX_PWMG4 = Duty_FreqMAX_PWMG;
      Interval_Micros_PWMG4 = Interval_Micros_PWMG;
      PinisHigh_PWMG4 = PinisHigh_PWMG;
      High_Counter_PWMG4 = High_Counter_PWMG;
    break;
  }
}

void init_PWMG(uint8_t Channel_init, uint8_t Pin, uint16_t Frequence_init, uint8_t Duty_init, 
               uint16_t ValueMIN_init, uint16_t ValueMAX_init, uint16_t Duty_FreqMIN_init, uint16_t Duty_FreqMAX_init){

//( Channel, Pin, Frequence, Duty, Valeur MIN, Valeur MAX, Duty/Freq MIN, Duty/Freq MAX)
  switch(Channel_init){
    
    case 1 :
    
      Pin_PWMG1 = Pin;
      Duty_PWMG1 = Duty_init;
      ValueMIN_PWMG1 = ValueMIN_init;
      ValueMAX_PWMG1 = ValueMAX_init;
      Duty_FreqMIN_PWMG1 = Duty_FreqMIN_init;
      Duty_FreqMAX_PWMG1 = Duty_FreqMAX_init;

      pinMode(Pin_PWMG1, OUTPUT);
      
      if(Duty_PWMG1 == 0){      
        Interval_Micros_PWMG1 = 1000000 / Frequence_init;
        Mode_PWMG1 = DUTY_MODULATION;
      }
      if(Frequence_init == 0){
        Mode_PWMG1 = FREQ_MODULATION;
      }
    break;

    case 2 :
    
      Pin_PWMG2 = Pin;
      Duty_PWMG2 = Duty_init;
      ValueMIN_PWMG2 = ValueMIN_init;
      ValueMAX_PWMG2 = ValueMAX_init;
      Duty_FreqMIN_PWMG2 = Duty_FreqMIN_init;
      Duty_FreqMAX_PWMG2 = Duty_FreqMAX_init;

      pinMode(Pin_PWMG2, OUTPUT);
      
      if(Duty_PWMG2 == 0){      
        Interval_Micros_PWMG2 = 1000000 / Frequence_init;
        Mode_PWMG2 = DUTY_MODULATION;
      }
      if(Frequence_init == 0){
        Mode_PWMG2 = FREQ_MODULATION;
      }
    break; 

    case 3 :
    
      Pin_PWMG3 = Pin;
      Duty_PWMG3 = Duty_init;
      ValueMIN_PWMG3 = ValueMIN_init;
      ValueMAX_PWMG3 = ValueMAX_init;
      Duty_FreqMIN_PWMG3 = Duty_FreqMIN_init;
      Duty_FreqMAX_PWMG3 = Duty_FreqMAX_init;

      pinMode(Pin_PWMG3, OUTPUT);
      
      if(Duty_PWMG3 == 0){      
        Interval_Micros_PWMG3 = 1000000 / Frequence_init;
        Mode_PWMG3 = DUTY_MODULATION;
      }
      if(Frequence_init == 0){
        Mode_PWMG3 = FREQ_MODULATION;
      }
    break; 

    case 4 :
    
      Pin_PWMG4 = Pin;
      Duty_PWMG4 = Duty_init;
      ValueMIN_PWMG4 = ValueMIN_init;
      ValueMAX_PWMG4 = ValueMAX_init;
      Duty_FreqMIN_PWMG4 = Duty_FreqMIN_init;
      Duty_FreqMAX_PWMG4 = Duty_FreqMAX_init;

      pinMode(Pin_PWMG4, OUTPUT);
      
      if(Duty_PWMG4 == 0){      
        Interval_Micros_PWMG4 = 1000000 / Frequence_init;
        Mode_PWMG4 = DUTY_MODULATION;
      }
      if(Frequence_init == 0){
        Mode_PWMG4 = FREQ_MODULATION;
      }
    break; 
  }
}

void BZO_PWMG(uint8_t Channel_Session, uint16_t Value) {

  CheckConstantsPWMG(Channel_Session);

  if(Mode_PWMG == DUTY_MODULATION){
    
    //On calcule le Duty souhaité 
    if (ValueMIN_PWMG < ValueMAX_PWMG) {
      Value = constrain(Value, ValueMIN_PWMG, ValueMAX_PWMG);
      Duty_PWMG = map(Value, ValueMIN_PWMG, ValueMAX_PWMG, Duty_FreqMIN_PWMG, Duty_FreqMAX_PWMG);
    }
    if (ValueMIN_PWMG > ValueMAX_PWMG) {
      Value = constrain(Value, ValueMAX_PWMG, ValueMIN_PWMG);
      Duty_PWMG = map(Value, ValueMAX_PWMG, ValueMIN_PWMG, Duty_FreqMIN_PWMG, Duty_FreqMAX_PWMG);
    }

    //On calcule le temps a attendre pour mettre la broche basse en micros par rapport a la valeur duty
    Interval_Low_PWMG = (Interval_Micros_PWMG * Duty_PWMG) / 100;
  }
  
  if(Mode_PWMG == FREQ_MODULATION){
    
    //On calcule la fréquence souhaitée
    if (ValueMIN_PWMG < ValueMAX_PWMG) {
      Value = constrain(Value, ValueMIN_PWMG, ValueMAX_PWMG);
      Frequence_PWMG = map(Value, ValueMIN_PWMG, ValueMAX_PWMG, Duty_FreqMIN_PWMG, Duty_FreqMAX_PWMG);
    }
    if (ValueMIN_PWMG > ValueMAX_PWMG) {
      Value = constrain(Value, ValueMAX_PWMG, ValueMIN_PWMG);
      Frequence_PWMG = map(Value, ValueMAX_PWMG, ValueMIN_PWMG, Duty_FreqMIN_PWMG, Duty_FreqMAX_PWMG);
    }

    //On calcule l'intervale qu'il faut pour appliquer la fréquence
    Interval_Micros_PWMG = 1000000 / Frequence_PWMG;

    //On calcule le temps a attendre pour mettre la broche basse en micros par rapport a la valeur duty
    Interval_Low_PWMG = (Interval_Micros_PWMG * Duty_PWMG) / 100;
  }

  //On lis micros() une fois pour les deux if()
  uint32_t Now = micros();
  
  //On fait le tic de départ
  if(((int32_t)(Now - High_Counter_PWMG) >= (int32_t)Interval_Micros_PWMG) && PinisHigh_PWMG == false){  
    digitalWrite(Pin_PWMG, HIGH); 
    PinisHigh_PWMG = true;
    High_Counter_PWMG += Interval_Micros_PWMG;
  }

  if(((int32_t)(Now - High_Counter_PWMG) >= (int32_t)Interval_Low_PWMG) && PinisHigh_PWMG == true){  
    digitalWrite(Pin_PWMG, LOW); 
    PinisHigh_PWMG = false;
  }
      
  RefreshConstantsPWMG(Channel_Session);
}
