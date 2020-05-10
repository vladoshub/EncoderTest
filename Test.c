#include <wiringPi.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <malloc.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>


bool State_A,State_B;
bool Start=true;
short Coordinate = 0;//координата
double Time;
struct timeval start;	
struct timeval stop;	

void
timevalToDouble ()
{			
    Time = (double) (stop.tv_usec - start.tv_usec) / 1000000 + (double) (stop.tv_sec - start.tv_sec);	
}


void ISR_A(){
if(Coordinate!=0 && start){
   Start=false;
   gettimeofday (&stop, NULL);
}
if (digitalRead(24)){
Coordinate++;
}
else{
Coordinate--;
gettimeofday (&stop, NULL);
}
}   
   

void ISR_B(){
if (digitalRead(23)){
Coordinate--;
gettimeofday (&stop, NULL);
}
else{
Coordinate++;
gettimeofday (&stop, NULL);
}
}   
   




int main()
{
wiringPiSetupGpio (); //BCM mode
pinMode (17, INPUT);
pinMode(27, INPUT);
wiringPiISR(17,INT_EDGE_RISING,ISR_A);
wiringPiISR(27,INT_EDGE_RISING,ISR_B);
while(1){
   fgets (readbuffer, countBuf, stdin);

      if (readbuffer[0] == 'E')
	exit (0);
   
   if (readbuffer[0] == 'N'){
	timevalToDouble();
  sprintf (out, "%d\n", Coordinate);
  fputs (out, stdout);
  fflush(stdout);
  sprintf (out, "%f\n", Time);
  fputs (out, stdout);
  fflush(stdout);
   }

   if (readbuffer[0] == 'C'){
	Coordinate=0;
   Time=0;
   Start=true;
   }
   usleep (100000);
}
}
