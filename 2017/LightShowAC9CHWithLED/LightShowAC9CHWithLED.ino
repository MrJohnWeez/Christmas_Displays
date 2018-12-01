
#include <TimerOne.h>

// Output to Triac pin channels
unsigned char channel_1 = 3;  // Layer1Tree
unsigned char channel_2 = 4;  // Layer2Tree
unsigned char channel_3 = 5;  // Layer3Tree
unsigned char channel_4 = 6;  // Layer4Tree
unsigned char channel_5 = 7;  // SideTree
unsigned char channel_6 = 8;  // CiramicTree
unsigned char channel_7 = 9;  // LEDTree
unsigned char channel_8 = 10; // TopStar
unsigned char channel_9 = 11; // FireLED

// 0 = Normal, 1 = LED Strand, 2 = LED Star
unsigned char LightType[] = {0,0,0,0,0,0,1,2,1};
unsigned char CH1,CH2,CH3,CH4,CH5,CH6,CH7,CH8, CH9;
unsigned char ChannelNumbers[] = {channel_1, channel_2, channel_3, channel_4, channel_5, channel_6, channel_7, channel_8, channel_9};
unsigned char CH[]={CH1, CH2, CH3, CH4, CH5, CH6, CH7, CH8, CH9};

unsigned char clock_tick; // variable for Timer1

int incomingByte[sizeof(ChannelNumbers)];

int NormalHigh = 4;
int BulbLEDHigh = 22;
int StarLEDHigh = 13;

int NormalLow = 90;
int BulbLEDLow = 95;
int StarLEDLow = 99;

float convertNormal = 255.0/(float)NormalLow;
float convertLED = 255.0/(float)BulbLEDLow;
float convertStar = 255.0/(float)StarLEDLow;





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

int convertNumber(int inByte, int lightType){
  int invertedValue = 0;
  int convertedValue = 0;
  if(lightType == 0){
    invertedValue = -1*(inByte-255);
    convertedValue = (int)(invertedValue/convertNormal);
    if(convertedValue < NormalHigh){
      convertedValue = NormalHigh;
    }else if(convertedValue > NormalLow){
      convertedValue = NormalLow;
    }
    return convertedValue;
  }else if(lightType == 1){
    invertedValue = -1*(inByte-255);
    convertedValue = (int)(invertedValue/convertLED);
    if(convertedValue < BulbLEDHigh){
      convertedValue = BulbLEDHigh;
    }else if(convertedValue >BulbLEDLow){
      convertedValue = BulbLEDLow;
    }
    return convertedValue;
  }else{
    invertedValue = -1*(inByte-255);
    convertedValue = (int)(invertedValue/convertStar);
    if(convertedValue <StarLEDHigh){
      convertedValue = StarLEDHigh;
    }else if(convertedValue >StarLEDLow){
      convertedValue = StarLEDLow;
    }
    return convertedValue;
  }
}

void loop() {

//  if (Serial.available() >= sizeof(ChannelNumbers))
//    {
//      for (int i=0; i<sizeof(ChannelNumbers);i++)
//      {
//        incomingByte[i] = Serial.read();
//      }
//
//      for(int c = 0; c < sizeof(CH); c++){
//        int tempInt = convertNumber(incomingByte[c],LightType[c]);
//        CH[c] = tempInt;
//      }
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


}
