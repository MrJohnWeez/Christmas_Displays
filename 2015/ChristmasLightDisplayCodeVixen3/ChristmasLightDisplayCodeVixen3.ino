/* 
This sketch allows the Arduino to read 16 bytes of data from Vixen and turn on
its pins accordingly, which in turn controls a solid state relay hooked up to Xmas lights.
*/

// Define pins on Arduino that will control the relay.
#define CHANNEL_01 2
#define CHANNEL_02 3
#define CHANNEL_03 4
#define CHANNEL_04 5 
#define CHANNEL_05 6 
#define CHANNEL_06 7
#define CHANNEL_07 8


// Define size of array to hold channels
#define CHANNEL_COUNT 7

// Define array to hold channels
int channels[] =
{
  CHANNEL_01, CHANNEL_02, CHANNEL_03, CHANNEL_04, CHANNEL_05, CHANNEL_06, CHANNEL_07
};

// Define array to hold incoming data stream from Vixen
int incomingByte[7];

// Define baud rate. This figure must match that of your profile configuration in Vixen!
#define BAUD_RATE 9600

void setup()
{
  // Begin serial communication
  Serial.begin(BAUD_RATE);

  // Set up each channel as an output
  for(int i = 0; i < CHANNEL_COUNT; i++)
  {
    pinMode(channels[i], OUTPUT);
  }
}

void loop()
{
  if (Serial.available() >= CHANNEL_COUNT)
  {
    // Read data from Vixen, store in array
    for (int i = 0; i < CHANNEL_COUNT; i++)
    {
      incomingByte[i] = Serial.read();
    }
    // Write data from array to a pin on Arduino
    for (int i = 0; i < CHANNEL_COUNT; i++)
    {
      analogWrite(channels[i], incomingByte[i]);
    }
  }
}