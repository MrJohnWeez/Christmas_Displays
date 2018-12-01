
#include <TimerOne.h>

unsigned char channel_1 = 3;    // Output to Opto Triac pin, channel 1
unsigned char channel_2 = 4;    // Output to Opto Triac pin, channel 2
unsigned char channel_3 = 5;    // Output to Opto Triac pin, channel 3
unsigned char channel_4 = 6;    // Output to Opto Triac pin, channel 4
unsigned char channel_5 = 7;    // Output to Opto Triac pin, channel 5
unsigned char channel_6 = 8;    // Output to Opto Triac pin, channel 6
unsigned char channel_7 = 9;    // Output to Opto Triac pin, channel 7
unsigned char channel_8 = 10;   // Output to Opto Triac pin, channel 8
unsigned char channel_9 = 11;   // Output to Opto Triac pin, channel 9
unsigned char channel_10 = 12;  // Output to Opto Triac pin, channel 10

unsigned char CH1, CH2, CH3, CH4, CH5, CH6, CH7, CH8, CH9, CH10;
unsigned char CHANNEL_SELECT;
unsigned char clock_tick; // variable for Timer1
unsigned char low = 70;
unsigned char high = 5;


unsigned char CH[]={CH1, CH2, CH3, CH4, CH5, CH6, CH7, CH8, CH9, CH10};
unsigned char CHPins[]={channel_1, channel_2, channel_3, channel_4, channel_5, channel_6, channel_7, channel_8, channel_9, channel_10};

int incomingByte[10];
float convert = 255.0/90.0;

void setup() {

for(int r = 0; r < 10; r++){
  pinMode(CHPins[r], OUTPUT);// Set AC Load pin as output
}

Serial.begin(9600);
attachInterrupt(0, zero_crosss_int, RISING);
Timer1.initialize(83); // set a timer of length 100 microseconds for 50Hz or 83 microseconds for 60Hz;
Timer1.attachInterrupt( timerIsr ); // attach the service routine here
}

void timerIsr()
{
  clock_tick++;

  
  if (CH[1]==clock_tick)
  {
  digitalWrite(CHPins[1], HIGH); // triac firing
  delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(CHPins[1], LOW); // triac Off
  }
  if (CH[2]==clock_tick)
  {
  digitalWrite(CHPins[2], HIGH); // triac firing
  delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(CHPins[2], LOW); // triac Off
  }
  if (CH[3]==clock_tick)
  {
  digitalWrite(CHPins[3], HIGH); // triac firing
  delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(CHPins[3], LOW); // triac Off
  }
  if (CH[4]==clock_tick)
  {
  digitalWrite(CHPins[4], HIGH); // triac firing
  delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(CHPins[4], LOW); // triac Off
  }
  if (CH[5]==clock_tick)
  {
  digitalWrite(CHPins[5], HIGH); // triac firing
  delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(CHPins[5], LOW); // triac Off
  }
  if (CH[6]==clock_tick)
  {
  digitalWrite(CHPins[6], HIGH); // triac firing
  delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(CHPins[6], LOW); // triac Off
  }
  if (CH[7]==clock_tick)
  {
  digitalWrite(CHPins[7], HIGH); // triac firing
  delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(CHPins[7], LOW); // triac Off
  }
  if (CH[8]==clock_tick)
  {
  digitalWrite(CHPins[8], HIGH); // triac firing
  delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(CHPins[8], LOW); // triac Off
  }
  if (CH[9]==clock_tick)
  {
  digitalWrite(CHPins[9], HIGH); // triac firing
  delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(CHPins[9], LOW); // triac Off
  }
  if (CH[10]==clock_tick)
  {
  digitalWrite(CHPins[10], HIGH); // triac firing
  delayMicroseconds(8.33); // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(CHPins[10], LOW); // triac Off
  }
}


// function to be fired at the zero crossing to dim the light
void zero_crosss_int() 
{
clock_tick=0;     // Every zerocrossing interrupt: For 50Hz (1/2 Cycle) => 10ms ; For 60Hz (1/2 Cycle) => 8.33ms
}

void loop() {
//4 brightest full
//90 brightest off

//  if (Serial.available() >= 10)
//    {
//      for (int i=0; i<10;i++)
//      {
//        incomingByte[i] = Serial.read();
//      }                                       // Arduino pins
//
//      for(int ii = 0; ii < 10; ii++){
//        int invertedByte = -1*(incomingByte[0]-255);
//        int convertedByte = (int)(invertedByte/convert);      // Convert byte to about 0-90
//
//        // Prevent overflow values
//        if(convertedByte <4){
//          convertedByte = 4;
//        }else if(convertedByte >90){
//          convertedByte = 90;
//        }
//
//        CH[ii] = convertedByte;   // set value
//      }
//    }


//CH1 = 90;
//CH2 = 90;
//CH3 = 90;
//CH4 = 90;
//CH5 = 90;
//CH6 = 90;
//CH7 = 90;
//CH8 = 90;
//CH9 = 90;
//CH10 = 90;

CH1 = 90;
CH2 = 90;
CH3 = 90;
CH4 = 90;
CH5 = 90;
CH6 = 90;
CH7 = 90;
CH8 = 4;
CH9 = 4;
CH10 = 90;
}
