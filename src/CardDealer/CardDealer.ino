#include "ServoMotor.h"
#include "_7seg.h"
#include "joyStick.h"
#include "btn.h"
#include "signals.h"


ServoMotor servoRotor(9);
ServoMotor servoDealer(10);
_7seg playerNo(13, 7, 6, 5, 11, 12, 8);
joyStick js(A0, A1, 2);
btn button_OK(3), button_Next(4);

bool settings = false, playerNoS = false, cardsNoS = false;
bool initial_cardDeal = false;
int playersNo = 0, cardsNo = 0, joyStickValue, servoPos = 1000;
unsigned long lastJSCheck = 0;
//500 - Default position for every player
int ServoPositions[5] = { 500, 500, 500, 500, 500 }; 

void setup() {
  servoRotor.init();
  servoDealer.init();
  playerNo.init();
  js.init();
  button_OK.init();
  button_Next.init();
  Serial.begin(9600);
}

// 5000 - 180 | 1000 - 0

void loop() {
  if (!settings) {
    if (!playerNoS) {
      handlePlayerNumberSetting();
    } else if (!cardsNoS) {
      handleCardsNumberSetting();
    } else {
      for (int player = 1; player <= playersNo; player++) {
        playerNo.write_number(player);
        while (!button_OK.isButtonPressed()) {
          changeServoPos(js, servoPos);
          servoRotor.setPos(servoPos);
          _delay_ms(150);
        }
        // Here we save the positions for each player
        sendPlayerSignal(player);
        ServoPositions[player - 1] = servoPos;
        // If we have set positions for all players, the settings configuration mode ends
        if (player == playersNo) {
          settings = true;
        }
      }
    }
    // Here gameplay mode starts
  } else {
    // We make the first card deal based on configuration info
    if (!initial_cardDeal) {
      for (int player = 1; player <= playersNo; player++) {
        servoRotor.setPos(ServoPositions[player - 1]);
        _delay_ms(500);

        for (int card = 1; card <= cardsNo; card++) {
          servoDealer.servoTurn();
          _delay_ms(500);
        }
      }
      initial_cardDeal = true;
    }
    int curr_player = 1;
    while (curr_player <= playersNo) {
      playerNo.write_number(curr_player);
      if (button_OK.isButtonPressed()) {
        // We deal a card
        servoDealer.servoTurn();
        curr_player++;
      } else if (button_Next.isButtonPressed()) {
        curr_player++;
      }
      servoRotor.setPos(ServoPositions[curr_player - 1]);
    }
    curr_player = 1;
  }
}

// Function to check if the specified time has passed
int hasTimePassed(unsigned long currentMillis, unsigned long &lastCheck, int time) {
  if (currentMillis - lastCheck >= time) {
    lastCheck = currentMillis;
    return 1;
  }
  return 0;
}


/* handlePlayerNumberSetting and handleCardsNumberSetting check every 500ms if the joystick is moved left or right for increase or decrease, and if the button is pushed, the selection is done for current branch */

void handlePlayerNumberSetting() {
  if (hasTimePassed(millis(), lastJSCheck, 250)) {
    if (button_OK.isButtonPressed()) {
      playerNoS = true;
      sendOkSignal();
    } else {
      checkJSValue(js, playersNo);
    }
  }
}

void handleCardsNumberSetting() {
  if (hasTimePassed(millis(), lastJSCheck, 250)) {
    if (button_OK.isButtonPressed()) {
      cardsNoS = true;
      servoRotor.setPos(1000);
      sendOkSignal();
    } else {
      checkJSValue(js, cardsNo);
    }
  }
}
