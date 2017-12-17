
#include <TimerOne.h>

// Output to Triac pin channels
unsigned char channel_1 = 3;  
unsigned char channel_2 = 4;
unsigned char channel_3 = 5;
unsigned char channel_4 = 6;
unsigned char channel_5 = 7;
unsigned char channel_6 = 8;
unsigned char channel_7 = 9;
unsigned char channel_8 = 10;
unsigned char channel_9 = 11;

unsigned char CH1,CH2,CH3,CH4,CH5,CH6,CH7,CH8, CH9;
unsigned char ChannelNumbers[] = {channel_1, channel_2, channel_3, channel_4, channel_5, channel_6, channel_7, channel_8, channel_9};
unsigned char CH[]={CH1, CH2, CH3, CH4, CH5, CH6, CH7, CH8, CH9};

unsigned char clock_tick; // variable for Timer1

int incomingByte[2];
float convert = 255.0/90.0;


void setup() {
CH1=CH2=CH3=CH4=CH5=CH6=CH7=CH8=CH9=90;   // Turn off all channels

// Set pinmodes
for(int CH_I = 0; CH_I < sizeof(ChannelNumbers); CH_I++){
  pinMode(ChannelNumbers[CH_I], OUTPUT); // Set triac firing pin
}

Serial.begin(9600);
attachInterrupt(0, zero_crosss_int, RISING);
Timer1.initialize(83); // set a timer of length 100 microseconds for 50Hz or 83 microseconds for 60Hz;
Timer1.attachInterrupt( timerIsr ); // attach the service routine here
}


void timerIsr()
{
  clock_tick++;

  // Loops through all channels
  for(int r = 0; r < sizeof(CH); r++){
    if (CH[r] == clock_tick){
      digitalWrite(ChannelNumbers[r], HIGH); // triac firing
      delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
      digitalWrite(ChannelNumbers[r], LOW); // triac Off
    }
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

CH[0] = 4;
CH[1] = 4;
CH[2] = 4;
CH[3] = 4;
CH[4] = 4;
CH[5] = 4;
CH[6] = 22;
CH[7] = 13;
CH[8] = 22;

// Light Type       High  Off
//  Normal Lights   4     90
//  Bulb LED        22    85
//  Star LED        13    92




}
