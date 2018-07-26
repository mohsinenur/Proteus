#include <avr/io.h>
#include <util/delay.h>

int row=4,col=4;

void move(){
  PORTD = 0b01111111;
  PORTB = 0b00000000;

  switch (row){
    case 1:
      PORTD = PORTD & 0b11111110; break;
    case 2:
      PORTD = PORTD & 0b11111101; break;
    case 3:
      PORTD = PORTD & 0b11111011; break;
    case 4:
      PORTD = PORTD & 0b11110111; break;
    case 5:
      PORTD = PORTD & 0b11101111; break;
    case 6:
      PORTD = PORTD & 0b11011111; break;
    case 7:
      PORTD = PORTD & 0b10111111; break;
    default:
      PORTD = PORTD | 0b01111111;
  }

  switch (col){
    case 1:
      PORTD = PORTD | 0b10000000; break;
    case 2:
      PORTB = PORTB | 0b00000001; break;
    case 3:
      PORTB = PORTB | 0b00000010; break;
    case 4:
      PORTB = PORTB | 0b00000100; break;
    case 5:
      PORTB = PORTB | 0b00001000; break;
    case 6:
      PORTB = PORTB | 0b00010000; break;
    case 7:
      PORTB = PORTB | 0b00100000; break;
    default:
      PORTD = PORTD & 0b01111111;
      PORTB = PORTB & 0b11000000;
  }
  _delay_ms(400);
}

int main(void){
  DDRD = 0xFF;
  DDRB = 0xFF;
  DDRC = 0;

  int count=0;
  while(1){
        //row 2 col 4
    PORTD = 0b01111101;
    PORTB = 0b00000100;
    _delay_ms(1);

        //row 3 col 3,5
    PORTD = 0b01111011;
    PORTB = 0b00001010;
    _delay_ms(1);

        //row 4 col 2,3,4,5
    PORTD = 0b01110111;
    PORTB = 0b00011111;
    _delay_ms(1);

        //row 5 col 1,7
    PORTD = 0b11101111;
    PORTB = 0b00100000;
    _delay_ms(1);

        //stop after 3 second and on row 4 col 4
    if(++count>=600){
      break;
    }
  }
  
  count=0;
  while(1){
    //row 1 col 1-7
    PORTD = 0b11111110;
    PORTB = 0b00111111;
    _delay_ms(1);

    //row 1-7 col 7
    PORTD = 0b01000001;
    PORTB = 0b00100000;
    _delay_ms(1);

    //row 1-7 col 7
    PORTD = 0b10111111;
    PORTB = 0b00111111;
    _delay_ms(1);

    //row 1-7 col 7
    PORTD = 0b11000001;
    PORTB = 0b00000000;
    _delay_ms(1);
    
    if(++count>=200){
      break;
    }
  }

  count=0;
  while(1){
    //row 2 col 1-7
    PORTD = 0b01111101;
    PORTB = 0b00011111;
    _delay_ms(1);

    //row 1-7 col 7
    PORTD = 0b01100011;
    PORTB = 0b00010000;
    _delay_ms(1);

    //row 6  col 7
    PORTD = 0b01011111;
    PORTB = 0b00011111;
    _delay_ms(1);

    //row 1-7 col 7
    PORTD = 0b01100011;
    PORTB = 0b00000001;
    _delay_ms(1);
    
    if(++count>=200){
      break;
    }
  }

  count=0;
  while(1){
    //row 3 col 1-7
    PORTD = 0b01111011;
    PORTB = 0b00001110;
    _delay_ms(1);

    //row 1-7 col 7
    PORTD = 0b01110111;
    PORTB = 0b00001000;
    _delay_ms(1);

    //row 6  col 7
    PORTD = 0b01101111;
    PORTB = 0b00001110;
    _delay_ms(1);

    //row 1-7 col 7
    PORTD = 0b01110111;
    PORTB = 0b00000010;
    _delay_ms(1);
    
    if(++count>=200){
      PORTD = 0b01110111;
      PORTB = 0b00000100;
      _delay_ms(700);
      PORTD = 0b01111111;
      PORTB = 0b00000000;
      _delay_ms(700);
      PORTD = 0b01110111;
      PORTB = 0b00000100;
      count=0;
      break;
    }
  }
  
  unsigned char inX,inY;
  ADCSRA |= (1<<ADEN);
  ADCSRA = ADCSRA | 0b00000100;
  ADMUX = ADMUX | 0b01100000;

  while(1){
    //X-Axis
    ADMUX = ADMUX & 0b11110000;
    ADMUX = ADMUX | 0b00000000;
    ADCSRA |= (1<<ADSC);
    while(!(ADCSRA & 0b00010000));

    inX = ADCH;

    if(inX >= 0 && inX <= 25){
      if(col > 1) col--;
      else col = 7;
      move();
    }
    else if(inX > 200 && inX <255){
      if(col<7) col++;
      else col=1;
      move();
    }

    //Y-Axis
    ADMUX = ADMUX & 0b11110000;
    ADMUX = ADMUX | 0b00000001;
    ADCSRA |= (1<<ADSC);
    while(!(ADCSRA & 0b00010000));

    inY = ADCH;

    if(inY >= 0 && inY <= 25){
      if(row<7) row++;
      else row=1;
      move();
    }
    else if(inY > 200 && inY <255){
      if(row > 1) row--;
      else row = 7;
      move();
    }
  }

  return 0;
}
