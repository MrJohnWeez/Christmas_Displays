
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
unsigned char channel_10 = 12;

//Power
int NormalHigh = 125;
int LedHigh = 45;
int RopeHigh = 125;

int NormalLow = 169;
int LedLow = 110;
int RopeLow = 200;

//Normal = 0
//-Small lights

//Led = 1
//-Big lights
//-Star

//Rope = 2
//-Rope Lighting

unsigned char LightType[] = {0,0,0,0,0,0,1,2,1,0};
unsigned char CH1,CH2,CH3,CH4,CH5,CH6,CH7,CH8,CH9,CH10;

//ChannelNumbers and ChannelValues must have the same number of values
unsigned char ChannelNumbers[] = {channel_1, channel_2, channel_3, channel_4, channel_5, channel_6, channel_7, channel_8, channel_9, channel_10};
unsigned char ChannelValues[]={CH1, CH2, CH3, CH4, CH5, CH6, CH7, CH8, CH9, CH10};

unsigned char clock_tick; // variable for Timer1

int incomingByte[sizeof(ChannelValues)];
int channelCount = sizeof(ChannelValues);


int foo = 100;
char buffer[6];

void setup()
{
  for(int CH_I = 0; CH_I < channelCount; CH_I++)
  {
    ChannelValues[CH_I] = 0; // Turn off all channels
    pinMode(ChannelNumbers[CH_I], OUTPUT); // Set triac firing pin mode
  }
  
  Serial.begin(9600);
  attachInterrupt(0, zero_crosss_int, RISING);
  Timer1.initialize(83); // set a timer of length 100 microseconds for 50Hz or 83 microseconds for 60Hz;
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here
}

//Triac firing function
void timerIsr()
{
  clock_tick++;
  for(int r = 0; r < channelCount; r++)
  {
    if (ChannelValues[r] == clock_tick)
    {
      digitalWrite(ChannelNumbers[r], HIGH); // triac firing
      delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
      digitalWrite(ChannelNumbers[r], LOW); // triac Off
    }
  }
}

// Resets counter when a zero cross was detected
void zero_crosss_int() 
{
// Every zerocrossing interrupt: For 50Hz (1/2 Cycle) => 10ms ; For 60Hz (1/2 Cycle) => 8.33ms
// 10ms=10000us , 8.33ms=8330us
clock_tick=0;
}

// Convert a 0-255 value to a type of light value
int convertNumber(int inByte, int lightType)
{
  if(lightType == 0){
    if(inByte == 0) { return 0; }
    return map(inByte, 0, 255, NormalLow, NormalHigh);
  }else if(lightType == 1){
    return map(inByte, 0, 255, LedLow, LedHigh);
  }else if(lightType == 2){
    return map(inByte, 0, 255, RopeLow, RopeHigh);
  }else{
    return inByte;
  }
}

void loop()
{
  if (Serial.available() >= channelCount)
    {
      for (int i = 0; i < channelCount; i++)
      {
        incomingByte[i] = Serial.read();
      }

      for(int c = 0; c < channelCount; c++)
      {
        int tempInt = convertNumber(incomingByte[c],LightType[c]);
        ChannelValues[c] = tempInt;
      }
    }




//  int index;  
//  while (Serial.available()) 
//  {
//    index = Serial.readBytesUntil('\n', buffer, 5);  //newline or max of 5 chars
//    buffer[index] = '\0';
//  
//    int n = atoi(buffer);  //convert readString into a number
//    Serial.println(n); //so you can see the integer
//    CH[0] = n;
//    buffer[0] = '\0';
//  } 
//  Serial.println(CH[0]);






//foo += 2;
//if(foo > 255)
//{
//  foo = 0;
//}
//
//CH[0] = foo;
//Serial.println(CH[0]);
//
//delay(100);
}
