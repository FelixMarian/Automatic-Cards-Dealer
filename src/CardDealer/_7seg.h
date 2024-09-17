#ifndef _7SEG_H
#define _7SEG_H

/*This project uses the following pin values:
A - 13 (PB5)
B - 7 (PD7)
C - 6 (PD6)
D - 5 (PD5)
E - 11 (PB3)
F - 12 (PB4)
G - 8 (PB0)
We are using these preset values because we will set them for this project using registers*/
class _7seg {
private:
  int A, B, C, D, E, F, G;
public:
  _7seg(int A_c, int B_c, int C_c, int D_c, int E_c, int F_c, int G_c) {
    A = A_c;
    B = B_c;
    C = C_c;
    D = D_c;
    E = E_c;
    F = F_c;
    G = G_c;
  }
  void ResetPins() {
    //Set pins to HIGH to maintain a HIGH voltage and allow them to act as GND when needed
    PORTD |= (1 << PD5) | (1 << PD6) | (1 << PD7);
    PORTB |= (1 << PB0) | (1 << PB3) | (1 << PB4) | (1 << PB5);
  }
  void init() {
    //Set these pins as OUTPUT because we have a common anode
    DDRD |= (1 << PD5) | (1 << PD6) | (1 << PD7);
    DDRB |= (1 << PB0) | (1 << PB3) | (1 << PB4) | (1 << PB5);

    ResetPins();
  }
  void write_number(int number) {
    switch (number) {
      case 1:
        ResetPins();
        PORTD &= ~((1 << PD6) | (1 << PD7)); 
        break;
      case 2:
        ResetPins();
        PORTD &= ~((1 << PD7) | (1 << PD5));
        PORTB &= ~((1 << PB5) | (1 << PB3) | (1 << PB0));
        break;
      case 3:
        ResetPins();
        PORTD &= ~((1 << PD7) | (1 << PD6) | (1 << PD5));
        PORTB &= ~((1 << PB5) | (1 << PB0));
        break;
      case 4:
        ResetPins();
        PORTD &= ~((1 << PD7) | (1 << PD6));
        PORTB &= ~((1 << PB4) | (1 << PB0));
        break;
      case 5:
        ResetPins();
        PORTD &= ~((1 << PD6) | (1 << PD5));
        PORTB &= ~((1 << PB5) | (1 << PB4) | (1 << PB0));
        break;
    }
  }
  void debug() {
    write_number(1);
    _delay_ms(500);
    write_number(2);
    _delay_ms(500);
    write_number(3);
    _delay_ms(500);
    write_number(4);
    _delay_ms(500);
    write_number(5);
    _delay_ms(500);
  }
};

#endif
