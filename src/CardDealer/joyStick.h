#ifndef JOYSTICK_H
#define JOYSTICK_H

class joyStick {
private:
  int axisX_pin, axisY_pin, btn_pin;
public:
  joyStick(int axisX_pinC, int axisY_pinC, int btn_pinC) {
    axisX_pin = axisX_pinC;
    axisY_pin = axisY_pinC;
    btn_pin = btn_pinC;
  }
  void init() {
    // Set the reference voltage to Arduino's (5V)
    ADMUX |= (1 << REFS0);

    // Enable the ADC and start conversion with a 128 prescaler to achieve a 125KHz clock.
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  }
  uint16_t readADC(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0X0F);

    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC))
      ;  // Wait for the conversion to complete

    return ADC;
  }
};

#endif
