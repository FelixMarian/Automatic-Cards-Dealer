#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#include <avr/io.h>
class ServoMotor{
private:
  int myPin;
public:
  ServoMotor(int myPin_c){
    myPin = myPin_c;
    if(myPin == 10) DDRB |= (1<<PB2);
    else if(myPin == 9) DDRB |= (1<<PB1);
  }
  void setPos(int value){
    // We set the position depending on the pin because we will have 2 servos with different duty cycles
    if(myPin == 10) OCR1B = value;
    else if(myPin == 9) OCR1A = value;
  }
  void init(){
    // Non-inverted, fastPWM with a prescaler of 8 and TOP of 39999 to achieve a frequency of 50 Hz
    TCCR1A = (1<<WGM11) | (1<<COM1A1) | (1<<COM1B1);
    TCCR1B = (1<<WGM12) | (1<<WGM13) | (1<<CS11);
    ICR1 = 39999; 
  }
  // Used for the dealer servo, a continuous servo motor
  // It goes 60 degrees in 0.11 seconds, so 360 degrees in 0.66 seconds
  // We use OCR1B because it is on pin 10
  void servoTurn(){
    OCR1B = 5100;
    _delay_ms(680);
    OCR1B = 3000;
  }
};


#endif
