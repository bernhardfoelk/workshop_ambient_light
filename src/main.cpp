#include <Arduino.h>
#include <app_config.h>
#include <variables.h>
#include <Ton.h>
#include <EdgePosNeg.h>

// Function to increase led value
void increaseLedValue(sLedState &isLedState);

void setup() {
  // Define button pins as input
  pinMode(POWER_BUTTON, INPUT);
  pinMode(BUTTON_RED, INPUT);
  pinMode(BUTTON_GREEN, INPUT);
  pinMode(BUTTON_BLUE, INPUT);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
   
  // Start serial interface
  Serial.begin(9600);
  delay(500);
  debugln("Debugging started..");  
}

void loop() {

  // Edge detection for buttons
  Edge_PowerButton.run(digitalRead(POWER_BUTTON));
  Edge_ButtonRed.run(digitalRead(BUTTON_RED));
  Edge_ButtonGreen.run(digitalRead(BUTTON_GREEN));
  Edge_ButtonBlue.run(digitalRead(BUTTON_BLUE));

  // Power button pressed? --> toggle power
  if (Edge_PowerButton.EdgePos()){
    lxPower = !lxPower;
    debug("Powerstatus: ");
    debugln(lxPower);

    if (!lxPower){
      debugln("Alles ausschalten..");
      liStep = 0;
    }
  }

  // State machine
  switch (liStep){

    //***************************************
    // Reset step
    //***************************************
    case 0:
      lsLedRed.iValue = 0;
      lsLedGreen.iValue = 0;
      lsLedBlue.iValue = 0;

      lxPower = false;

      liStep = 10;
      break;

    //***************************************
    // Wait for power on 
    case 10:
      if (lxPower){
        lsLedRed.iValue = 100;
        lsLedGreen.iValue = 145;
        lsLedBlue.iValue = 250;

        liStep = 20;
      }
      break;


    //***************************************
    // Main step
    //***************************************
    case 20:

      if (Edge_ButtonRed.EdgePos()){
        debugln("Positive Flanke von Button Rot!");
      }
      if (Edge_ButtonGreen.EdgePos()){
        debugln("Positive Flanke von Button Grün!");
      }
      if (Edge_ButtonBlue.EdgePos()){
        debugln("Positive Flanke von Button Blau!");
      }

      TonStep.IN((digitalRead(BUTTON_RED) || digitalRead(BUTTON_GREEN) || digitalRead(BUTTON_BLUE)));
      TonStep.PT(500);

      if (TonStep.Q()){

        if (digitalRead(BUTTON_RED)){
          liStep = 100;
        }

        if (digitalRead(BUTTON_GREEN)){
          liStep = 200;
        }

        if (digitalRead(BUTTON_BLUE)){
          liStep = 300;
        }
      }
      break;

    //***************************************
    // Increase brightness of red led
    case 100:

      TonStep.IN(true);
      TonStep.PT(25);
      if (TonStep.Q()){
        debugln(lsLedRed.iValue);
        TonStep.IN(false);
        increaseLedValue(lsLedRed);
      }

      if (!digitalRead(BUTTON_RED) && !digitalRead(BUTTON_GREEN) && !digitalRead(BUTTON_BLUE)){
        liStep = 20;
      }
      break;

    //***************************************
    // Increase brightness of green led
    case 200:

      TonStep.IN(true);
      TonStep.PT(25);
      if (TonStep.Q()){
        debugln(lsLedGreen.iValue);
        TonStep.IN(false);
        increaseLedValue(lsLedGreen);
      }

      if (!digitalRead(BUTTON_RED) && !digitalRead(BUTTON_GREEN) && !digitalRead(BUTTON_BLUE)){
        liStep = 20;
      }
      break;

    //***************************************
    // Increase brightness of blue led
    case 300:

      TonStep.IN(true);
      TonStep.PT(25);
      if (TonStep.Q()){
        debugln(lsLedBlue.iValue);
        TonStep.IN(false);
        increaseLedValue(lsLedBlue);
      }

      if (!digitalRead(BUTTON_RED) && !digitalRead(BUTTON_GREEN) && !digitalRead(BUTTON_BLUE)){
        liStep = 20;
      }    
  }

  //analogWrite(LED_RED, lsLedRed.iValue);
  //analogWrite(LED_GREEN, lsLedGreen.iValue);
  //analogWrite(LED_BLUE, lsLedBlue.iValue);

  // Timer call
  TonStep.run();
  TonStep.IN(false);

  // Debug: log change of step variable
  if (liStep != liStepOld){
    liStepOld = liStep;
    debug("Aktueller Schritt: ");
    debugln(liStep);
  }
}

// Function to increase brightness of led
void increaseLedValue(sLedState &isLedState){  
    isLedState.iValue += 1;
    if (isLedState.iValue >= 256){
      isLedState.iValue = 0;
    }
}


