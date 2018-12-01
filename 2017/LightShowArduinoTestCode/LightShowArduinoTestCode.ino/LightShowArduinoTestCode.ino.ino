int A = 2;
int B = 3;
int i = 0;
int incomingByte[2];

void setup()
{
  Serial.begin(9600);

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  //pinMode(5, OUTPUT);
}

void loop()
{
  if (Serial.available() >= 2)
  {
    for (int i=0; i<2;i++)
    {
      incomingByte[i] = Serial.read();
    }                                       // Arduino pins
    analogWrite(A, incomingByte[0]);  // Pin 2
    analogWrite(B, incomingByte[1]);  // Pin 3
   
  }
//  digitalWrite(5, HIGH);
//  delay(1000);
//  digitalWrite(5, LOW);
//  delay(1000);
}
