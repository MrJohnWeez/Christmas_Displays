
#include <TimerOne.h>

unsigned char channel_1 = 3;  // Output to Opto Triac pin, channel 1
unsigned char channel_2 = 4;  // Output to Opto Triac pin, channel 1
unsigned char channel_3 = 5;  // Output to Opto Triac pin, channel 1
unsigned char channel_4 = 6;  // Output to Opto Triac pin, channel 1
unsigned char channel_5 = 7;  // Output to Opto Triac pin, channel 1
unsigned char channel_6 = 8;  // Output to Opto Triac pin, channel 1
unsigned char channel_7 = 9;  // Output to Opto Triac pin, channel 1
unsigned char channel_8 = 10;  // Output to Opto Triac pin, channel 1
unsigned char channel_9 = 11; // Output to Opto Triac pin, channel 1
unsigned char CH1;
unsigned char CH2;
unsigned char CH3;
unsigned char CH4;
unsigned char CH5;
unsigned char CH6;
unsigned char CH7;
unsigned char CH8;
unsigned char CH9;
//unsigned char CHANNEL_SELECT;
//unsigned char i=0;
unsigned char clock_tick; // variable for Timer1
//unsigned int delay_time = 300;

//unsigned char low = 70;
//unsigned char high = 5;


unsigned char CH[]={CH1, CH2, CH3, CH4, CH5, CH6, CH7, CH8, CH9};

int incomingByte[2];
float convert = 255.0/90.0;

int foo = 4;

void setup() {

//for(int num_CH = 0; num_CH < CH.length; num_CH++){
//  CH[num_CH] = 90;
//}
CH1 = 90;
CH2 = 90;
CH3 = 90;
CH4 = 90;
CH5 = 90;
CH6 = 90;
CH7 = 90;
CH8 = 90;
CH9 = 90;

  
pinMode(channel_1, OUTPUT);// Set AC Load pin as output
pinMode(channel_2, OUTPUT);// Set AC Load pin as output
pinMode(channel_3, OUTPUT);// Set AC Load pin as output
pinMode(channel_4, OUTPUT);// Set AC Load pin as output
pinMode(channel_5, OUTPUT);// Set AC Load pin as output
pinMode(channel_6, OUTPUT);// Set AC Load pin as output
pinMode(channel_7, OUTPUT);// Set AC Load pin as output
pinMode(channel_8, OUTPUT);// Set AC Load pin as output
pinMode(channel_9, OUTPUT);// Set AC Load pin as output
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
  if (CH2==clock_tick)
  {
  digitalWrite(channel_2, HIGH); // triac firing
  delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(channel_2, LOW); // triac Off
  }
  if (CH3==clock_tick)
  {
  digitalWrite(channel_3, HIGH); // triac firing
  delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(channel_3, LOW); // triac Off
  }
  if (CH4==clock_tick)
  {
  digitalWrite(channel_4, HIGH); // triac firing
  delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(channel_4, LOW); // triac Off
  }
  if (CH5==clock_tick)
  {
  digitalWrite(channel_5, HIGH); // triac firing
  delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(channel_5, LOW); // triac Off
  }
  if (CH6==clock_tick)
  {
  digitalWrite(channel_6, HIGH); // triac firing
  delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(channel_6, LOW); // triac Off
  }
  if (CH7==clock_tick)
  {
  digitalWrite(channel_7, HIGH); // triac firing
  delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(channel_7, LOW); // triac Off
  }
  if (CH8==clock_tick)
  {
  digitalWrite(channel_8, HIGH); // triac firing
  delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(channel_8, LOW); // triac Off
  }
  if (CH9==clock_tick)
  {
  digitalWrite(channel_9, HIGH); // triac firing
  delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(channel_9, LOW); // triac Off
  }
}



void zero_crosss_int() // function to be fired at the zero crossing to dim the light
{
// Every zerocrossing interrupt: For 50Hz (1/2 Cycle) => 10ms ; For 60Hz (1/2 Cycle) => 8.33ms
// 10ms=10000us , 8.33ms=8330us
clock_tick=0;
}



void loop() {

//  if (Serial.available() >= 2)
//    {
//      for (int i=0; i<2;i++)
//      {
//        incomingByte[i] = Serial.read();
//      }                                       // Arduino pins
//
//      int r = -1*(incomingByte[0]-255);
//      int tempint = (int)(r/convert);
//      if(tempint <4){
//        tempint = 4;
//      }else if(tempint >90){
//        tempint = 90;
//      }
//      
//      CH1 = tempint;
//    }

CH1 = 4;
CH2 = 4;
CH3 = 4;
CH4 = 4;
CH5 = 4;
CH6 = 4;
CH7 = 22;
CH8 = 13;
CH9 = 22;

// Light Type       High  Off
//  Normal Lights   4     90
//  Bulb LED        22    85
//  Star LED        13    92




}
