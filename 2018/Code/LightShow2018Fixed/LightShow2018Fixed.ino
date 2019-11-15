/*
 Using the ZeroCross Tail(ZCT)to generate a sync pulse to drive a 
 triac for dimming ac lights.
 
 Connections to an Arduino:
 1. Connect the C terminal of the ZeroCross Tail to digital pin 2 with a 10K ohm 
    pull up resistor to Arduino 5V.
 2. Connect the E terminal of the ZeroCross Tail to Arduino Gnd.
*/

// BottomTree
// MiddleTree
// TopTree
// Star
// InsideTree
// Icicles
// TopFirePlace
// BottomFirePlace
// LeftSideTree
// RightSideTree

#include <TimerOne.h>                    

// User data
int channels[] = {3,4,5,6,7,8,9,10,11,12}; // Triac out pins
int LightType[] = {0,1,0,0,1,0,1,0,0,0};  //0 = normal, 1 = LED
int normMin = 11;
int normMax = 128;
int ledMin = 30;
int ledMax = 117;
int vixenMin = 0;
int vixenMax = 255;

// Light control
const int numOfChannels = sizeof(channels)/sizeof(int);
volatile int counters[numOfChannels];
volatile boolean zero_cross[numOfChannels]; //has channel had a zero cross
int dir[numOfChannels]; // Dim direction
int dimmers[numOfChannels]; // 2 = Full on   ,    128 = Full off
int incomingByte[numOfChannels];
int freqStep = 60;              // Set to 60hz mains

int state;
int ch;
enum states
{
  IDLE,
  DELIM,
  READ,
  DISP
};

// Convert vixen values to triac dimm levels
int convertNumber(int inByte, int lightType)
{
  if(lightType == 0) {
    return map(inByte, vixenMin, vixenMax, normMax, normMin);
  }else if(lightType == 1) {
    return map(inByte, vixenMin, vixenMax, ledMax, ledMin);
  }else {
    return inByte;
  }
}

void setup()
{
  // Set triac fire pins as output
  for (int i = 0; i < numOfChannels; i++) {
    pinMode(channels[i], OUTPUT);
    counters[i] = 0;
    zero_cross[i] = 0;
    dir[i] = 1;
    dimmers[i] = convertNumber(0,LightType[i]);
  }
  attachInterrupt(0, zero_cross_detect, RISING);   // Attach an Interupt to digital pin 2 (interupt 0),
  Timer1.initialize(freqStep);
  Timer1.attachInterrupt(dim_check,freqStep);
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available())
  {
    switch (state)
    {
      case IDLE:  
        ch = 0;
        if (Serial.read() == '+')
        {
          state = DELIM;          
        }
        else
        {
          state = IDLE;
        }
      break;
        
      case DELIM:
        ch = 0;
        if (Serial.read() == '>')
        {
          state = READ;
        }
        else
        {
          state = IDLE;
        }
      break;
      
      case READ:
        incomingByte[ch++] = Serial.read();
        if (ch >= numOfChannels)
        {
          ch = 0;
          state = DISP;
        }
      break; 
      
      case DISP:
        state = IDLE;
        for(int i = 0; i < numOfChannels; i++)
        {
          dimmers[i] = convertNumber(incomingByte[i],LightType[i]);
        }
      break;
    }
  }

  
//  if (Serial.available() >= numOfChannels)
//  {
//    int i = 0;
//    for (i = 0; i < numOfChannels; i++)
//    {
//      incomingByte[i] = Serial.read();
//    }
//
//    for(i = 0; i < numOfChannels; i++)
//    {
//      dimmers[i] = convertNumber(incomingByte[i],LightType[i]);
//    }
//  }
}

// This function will fire the triac at the proper time
void dim_check()
{
  for (int i = 0; i < numOfChannels; i++)
  {
    // First check to make sure the zero-cross has happened else do nothing
    if(zero_cross[i] == 1)
    {
      if(counters[i]>=dimmers[i])
      {
        digitalWrite(channels[i], HIGH);
        delayMicroseconds(8.3333);
        digitalWrite(channels[i], LOW); 
        counters[i] = 0;  // Reset the accumulator
        zero_cross[i] = 0;  // Reset the zero_cross so it may be turned on again at the next zero_cross_detect    
      }
      else
      {
        counters[i]++;  // If the dimming value has not been reached, increment the counter
      }
    }
  }
}

// Set the boolean to true to tell our dimming function that a zero cross has occured
void zero_cross_detect()
{
  for (int i = 0; i < numOfChannels; i++)
  {
    zero_cross[i] = 1;
  }
} 