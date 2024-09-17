#ifndef SIGNALS_H
#define SIGNALS_H

#include "ServoMotor.h"

void sendIncreaseSignal() {
  Serial.println("I");
}

void sendDecreaseSignal() {
  Serial.println("D");
}

void sendOkSignal() {
  Serial.println("K");
}

void sendPlayerSignal(int player) {
  switch (player) {
    case 1:
      Serial.println("P1");
      break;
    case 2:
      Serial.println("P2");
      break;
    case 3:
      Serial.println("P3");
      break;
    case 4:
      Serial.println("P4");
      break;
    case 5:
      Serial.println("P5");
      break;
  }
}

void checkJSValue(joyStick js, int &number) {
  int joyStickValue = js.readADC(3);
  if (joyStickValue <= 150 && number < 5) {
    sendIncreaseSignal();
    number++;
  } else if (joyStickValue >= 800 && number > 0) {
    sendDecreaseSignal();
    number--;
  } else return 0;
}

//In our case, 5000 corresponds to 180 degrees and 1000 corresponds to 0 degrees
void changeServoPos(joyStick js, int &pos) {
  int joyStickValue = js.readADC(3);
  if (joyStickValue <= 150 && pos <= 4950) {
    pos += 50;
    Serial.println("UP");
  } else if (joyStickValue >= 800 && pos >= 1050) {
    pos -= 50;
    Serial.println("DOWN");
  }
}

#endif
