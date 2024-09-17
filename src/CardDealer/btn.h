#ifndef BTN_H
#define BTN_H

class btn {
private:
  int btn_pin;
public:
  btn(int btn_pinC) {
    btn_pin = btn_pinC;
  }
  void init() {
    //Set the registers as INPUTS
    if(btn_pin == 3) DDRD |= (1 << PD3);
    else if(btn_pin == 4) DDRD |= (1 << PD4);
  }
  int isButtonPressed() {
    if ((PIND & (1 << PD4)) && btn_pin == 4){
      _delay_ms(300);
      return 1;
    }
    else if ((PIND & (1 << PD3)) && btn_pin == 3){
      _delay_ms(300);
      return 1;
    }
    return 0;
  }
};

#endif