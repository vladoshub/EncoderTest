#include <wiringPi.h>
#include <stdio.h>
#include <stdbool.h>


bool State_A,State_B;
short Coordinate = 0;//координата





void ISR_A(){
if (digitalRead(24))
Coordinate++;
else
Coordinate--;
}   
   

void ISR_B(){
if (digitalRead(23))
Coordinate--;
else
Coordinate++;
}   
   




int main()
{
wiringPiSetupGpio (); //BCM mode
pinMode (23, INPUT);
pinMode(24, INPUT);
wiringPiISR(23,INT_EDGE_RISING,ISR_A);
wiringPiISR(24,INT_EDGE_RISING,ISR_B);
while(1){
   
   printf("The integer is: %d\n",Coordinate);
}
}
