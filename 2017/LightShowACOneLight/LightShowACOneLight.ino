
#include <TimerOne.h>

unsigned char channel_1 = 3;  // Output to Opto Triac pin, channel 1
unsigned char CH1;
unsigned char clock_tick; // variable for Timer1

void setup() {

CH1 = 90;

  
pinMode(channel_1, OUTPUT);// Set AC Load pin as output
Serial.begin(9600);
attachInterrupt(0, zero_crosss_int, RISING);
Timer1.initialize(83); // set a timer of length 100 microseconds for 50Hz or 83 microseconds for 60Hz;
Timer1.attachInterrupt( timerIsr ); // attach the service routine here

}

void timerIsr()
{
  clock_tick++;
  
  if (CH1==clock_tick)
  {
  digitalWrite(channel_1, HIGH); // triac firing
  delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(channel_1, LOW); // triac Off
  }
}

void zero_crosss_int() // function to be fired at the zero crossing to dim the light
{
// Every zerocrossing interrupt: For 50Hz (1/2 Cycle) => 10ms ; For 60Hz (1/2 Cycle) => 8.33ms
// 10ms=10000us , 8.33ms=8330us
clock_tick=0;
}

void loop() {
//4 brightest full
//90 brightest off
CH1 = 4;
}
