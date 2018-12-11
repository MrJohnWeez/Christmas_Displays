
#include <TimerOne.h>
 
// Output to Triac pin channels
unsigned char channel_1 = 3;   // BottomTree
unsigned char channel_2 = 4;   // MiddleTree
unsigned char channel_3 = 5;   // TopTree
unsigned char channel_4 = 6;   // Star
unsigned char channel_5 = 7;   // InsideTree
unsigned char channel_6 = 8;   // Icicles
unsigned char channel_7 = 9;   // TopFirePlace
unsigned char channel_8 = 10;  // BottomFirePlace
unsigned char channel_9 = 11;  // LeftSideTree
unsigned char channel_10 = 12; // RightSideTree

// Power
int NormalHigh = 125;
int LedHigh = 45;
int RopeHigh = 25;
int StarHigh = 20;

int NormalLow = 169;
int LedLow = 110;
int RopeLow = 100;
int StarLow = 105;

//Normal = 0
//-Small lights

//Led = 1
//-Big lights

//Rope = 2
//-Rope Lighting

//Star = 3
// Star

unsigned char LightType[] = {0,0,0,3,1,0,1,2,0,0};
unsigned char CH1,CH2,CH3,CH4,CH5,CH6,CH7,CH8,CH9,CH10;

//ChannelNumbers and ChannelValues must have the same number of values
unsigned char ChannelNumbers[] = {channel_1, channel_2, channel_3, channel_4, channel_5, channel_6, channel_7, channel_8, channel_9, channel_10};
unsigned char ChannelValues[]={CH1, CH2, CH3, CH4, CH5, CH6, CH7, CH8, CH9, CH10};

unsigned char clock_tick; // variable for Timer1

int incomingByte[sizeof(ChannelValues)];
int channelCount = sizeof(ChannelValues);

int counter2 = 0;
int selectCh = 0;
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
  }else if(lightType == 3){
    return map(inByte, 0, 255, StarLow, StarHigh);
  }else{
    return inByte;
  }
}

void setup()
{
  for(int CH_I = 0; CH_I < channelCount; CH_I++)
  {
    ChannelValues[CH_I] = convertNumber(0,LightType[CH_I]); // Turn off all channels
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



void loop()
{
  ChannelValues[selectCh] = convertNumber(counter2,LightType[selectCh]);
  counter2++;
  if(counter2 >= 255)
  {
    counter2 = 0;
    ChannelValues[selectCh] = convertNumber(counter2,LightType[selectCh]);
    //selectCh++;
    if(selectCh >= 10)
    {
      selectCh = 0;
    }
  }
  delay(30);
  Serial.print(ChannelValues[0]);
  Serial.print("  ");
  Serial.print(ChannelValues[3]);
  Serial.print("  ");
  Serial.println(ChannelValues[7]);
}
