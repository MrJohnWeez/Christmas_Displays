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
int dimmers[] = {11,11,11,11,11,11,11,11,11,11}; // 2 = Full on   ,    127 = Full off
int LightType[] = {0,0,0,0,1,0,1,0,0,0};  //0 = normal, 1 = LED
int normMin = 11;
int normMax = 128;
int ledMin = 30;
int ledMax = 115;

// Light control
const int numOfChannels = sizeof(channels)/sizeof(int);
volatile int counters[numOfChannels];
volatile boolean zero_cross[numOfChannels]; //has channel had a zero cross
int dir[numOfChannels]; // Dim direction
int freqStep = 60;              // Set to 60hz mains

// Test vars
char buffer[6];
int TestMode = 1; //0 = serial  1 = dim loop

// Convert a 11-128 value to a non norm light
int convertNumber(int inByte, int lightType)
{
  if(lightType == 1){
    return map(inByte, 11, 128, ledMin, ledMax);
  }else{
    return inByte;
  }
}

int findDimClamp(int inLightType, int isMin)
{
  if(inLightType == 1)
  {
    if(isMin)
    {
      return ledMin;
    }
    else
    {
      return ledMax;
    }
  }
  else
  {
    if(isMin)
    {
      return normMin;
    }
    else
    {
      return normMax;
    }
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
    dimmers[i] = constrain(dimmers[i], findDimClamp(LightType[i],1), findDimClamp(LightType[i],0));
  }
  attachInterrupt(0, zero_cross_detect, RISING);   // Attach an Interupt to digital pin 2 (interupt 0),
  Timer1.initialize(freqStep);
  Timer1.attachInterrupt(dim_check,freqStep);
  Serial.begin(9600);
}

void loop()                        // Main loop
{
  if(TestMode == 0)
  {
    // Change dimming manually over serial port
    int index;  
    while (Serial.available()) 
    {
      index = Serial.readBytesUntil('\n', buffer, 5);  //newline or max of 5 chars
      buffer[index] = '\0';
    
      int n = atoi(buffer);  //convert readString into a number
      Serial.println(n); //so you can see the integer
      for (int i = 0; i < numOfChannels; i++)
      {
        dimmers[i] = n;
      }
      buffer[0] = '\0';
    } 
    //Serial.println(dimmers[4]);
  }
  else
  {
    // Dimm channels overtime
    for (int i = 0; i < numOfChannels; i++)
    {
      // Change dim up and back down
      if(dimmers[i] > findDimClamp(LightType[i],0) || dimmers[i] < findDimClamp(LightType[i],1))
      {
        dir[i] *= -1;
      }
      dimmers[i] += dir[i];
    }
    delay(50);
  }
  //Serial.println(dimmers[4]);
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
        //delayMicroseconds(8.3333);
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
