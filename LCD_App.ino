#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"
#include "ADC.h" // adding ADC, LCD, and delay libraries 

#define buzz 3 //buzzer variable set as pin 3

void init();

int main(void){

  init();     
  int tempmax = 30; // temperature max set 
  int tempmin = 20; // temperature min set 

//while loop start
  while (1)
  {
    int  a = ADC_Read(0); // reads analogue input at channel 0 (button pressed on LCD keypad)

    float temp = ADC_Read(1); // reads analogue input at channel 1 (temperature sensor)
    float tempC = temp/3.8; // divides temperature to become more realistic as sensor is not accurate

    LCD_Clear(); //clears LCD

    // if statement for button configuration
      if (a < 60){ 
        tempmin ++;  //right button adds one to temperature min
        LCD_String_xy (0, 1, tempmin); //print new min value (+1)
      }
      else if (a < 200) {
        tempmax ++;  //up  button adds one to temperature max
         LCD_String_xy (0, 1, tempmax); //print new max value (+1)
      }
      else if (a < 400){
        tempmax --;  //down button decreases one from temperature max
         LCD_String_xy (0, 1, tempmax); //print new max value (-1)
      }  
        else if (a < 600){
        tempmin --;  //left button decreases one from temperature min
         LCD_String_xy (0, 1, tempmin); //print new min value (-1)
        }

    if (tempC > tempmax || tempC < tempmin){ //if statement for temperature values if max or min values are exceeded
      PORTD = PORTD | (1 << buzz); // buzzer on
    }
    else { //temrature value stays between limits
        PORTD = PORTD & ~ (1 << buzz); // buzzer off 

    }

     char temp_string[5];
    itoa(tempC, temp_string, 10);
    //converts int data to string data
    LCD_String_xy (0, 0, "Temperature:"); // prints "Temperature:" at row 0 and column 0
    LCD_String_xy (0, 12, temp_string); // prints temperature at row 0 and column 12

     char temp_max[5];
    itoa(tempmax, temp_max, 10);

    LCD_String_xy (1, 0, "Max:"); // prints "Max:" at row 1 and column 0
    LCD_String_xy (1, 4, temp_max); // prints temperature max at row 1 and column 4

     char temp_min[5];
    itoa(tempmin, temp_min, 10);

    LCD_String_xy (1, 8, "Min:"); // prints "Min:" at row 1 and column 8
    LCD_String_xy (1, 12, temp_min); // prints temperature min at row 1 and column 12
    
    _delay_ms(500);
  }

  return 0; 
}
//while loop end

void init(){

   LCD_Init (); // initilize LCD

   ADC_Init(); // initilize ADC

   DDRD = DDRD | (1 << buzz); // buzzer pin set as output 

}