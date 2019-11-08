/*
 This sketch is a sample sketch using the ZeroCross Tail(ZCT)to generate a sync
 pulse to drive a PowerSSR Tail(PSSRT) for dimming ac lights.
 
 Connections to an Arduino Duemilanove:
 1. Connect the C terminal of the ZeroCross Tail to digital pin 2 with a 10K ohm pull up to Arduino 5V.
 2. Connect the E terminal of the ZeroCross Tail to Arduino Gnd.
*/

#include <TimerOne.h>                    

volatile int i=0;               // Variable to use as a counter
volatile boolean zero_cross=0;  // Boolean to store a "switch" to tell us if we have crossed zero
int CH1 = 3;                  // PowerSSR Tail connected to digital pin 4
int dim = 1;                   // Default dimming level (0-128)  0 = on, 128 = off
int freqStep = 60;              // Set to 60hz mains


char buffer[6];

void setup()
{
 pinMode(CH1, OUTPUT);                // Set SSR1 pin as output
 attachInterrupt(0, zero_cross_detect, RISING);   // Attach an Interupt to digital pin 2 (interupt 0),
 Timer1.initialize(freqStep);
 Timer1.attachInterrupt(dim_check,freqStep);
 Serial.begin(9600);
}

void loop()                        // Main loop
{
  int index;  
  while (Serial.available()) 
  {
    index = Serial.readBytesUntil('\n', buffer, 5);  //newline or max of 5 chars
    buffer[index] = '\0';
  
    int n = atoi(buffer);  //convert readString into a number
    Serial.println(n); //so you can see the integer
    dim = n;
    buffer[0] = '\0';
  } 
  Serial.println(dim);
}

// Functions

void dim_check() {                  // This function will fire the triac at the proper time
 if(zero_cross == 1) {              // First check to make sure the zero-cross has happened else do nothing
   if(i>=dim) {
    delayMicroseconds(100);        //These values will fire the PSSR Tail.
    digitalWrite(CH1, HIGH);
    delayMicroseconds(50);
    digitalWrite(CH1, LOW); 
     i = 0;                         // Reset the accumulator
     zero_cross = 0;                // Reset the zero_cross so it may be turned on again at the next zero_cross_detect    
   } else {
     i++;                           // If the dimming value has not been reached, increment the counter
   }                                // End dim check
 }                                  // End zero_cross check
}

// set the boolean to true to tell our dimming function that a zero cross has occured
void zero_cross_detect() { zero_cross = 1; } 
