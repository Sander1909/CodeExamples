#include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>

TMRpcm tmrpcm;

const int SEQ_MAX = 200;

int sequence[SEQ_MAX];
int seqIndex = 1;
bool awaitingInput = false;
bool inputResolved = false;

void setup() {
  // put your setup code here, to run once:

  seqIndex = 1;
  awaitingInput = false;
  tmrpcm.speakerPin = 9;

  pinMode(8, INPUT); //Button for 4
  pinMode(7, INPUT); //Button for 3
  pinMode(6, INPUT); //Button for 2
  pinMode(5, INPUT); //Button for A0

  pinMode(4, OUTPUT); 
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(A0, OUTPUT);

  Serial.begin(9600);

  if (!SD.begin(10)) 
  {
    Serial.println("SD fail");
  }

  tmrpcm.setVolume(6);
  tmrpcm.play("GAMEST~1.WAV");

  delay(3000);


  randomSeed(analogRead(A3));

  for(int i = 0; i < SEQ_MAX; i++)
  {
    sequence[i] = -1; 
  }

  sequence[0] = random(1,5);

}

void beep(int beepNumber)
{

switch(beepNumber)
{
  case 4:
    tmrpcm.setVolume(6);
    tmrpcm.play("BEEP1_~1.WAV");
  break;

  case 3:
  tmrpcm.setVolume(6);
    tmrpcm.play("BEEP2_~1.WAV");

  break;

  case 2:
  tmrpcm.setVolume(6);
    tmrpcm.play("BEEP3_~1.WAV");

  break;

  case 1:
  tmrpcm.setVolume(6);
    tmrpcm.play("BEEP4_~1.WAV");

  break;
}
  return;
}

void displaySequence()
{

for(int i = 0; i < seqIndex; i++)
{
  Serial.println(sequence[i]);
}
  
  for(int i = 0; i < seqIndex; i++)
  {

    beep(sequence[i]);
    
    if(sequence[i] == 1)
    {
      digitalWrite(A0, HIGH);
    }
    else
    {
     digitalWrite(sequence[i], HIGH); 
    }
    delay(1000);

    if(sequence[i] == 1)
    {
     digitalWrite(A0, LOW); 
    }

    else
    {
      digitalWrite(sequence[i], LOW);
    }
    delay(100);
  }

  awaitingInput = true;
}

bool anyInput()
{
  return (digitalRead(8) == HIGH || digitalRead(7) == HIGH || digitalRead(6) == HIGH || digitalRead(5));
}

int buttonPressed()
{
  if(digitalRead(8) == HIGH)
  {
    return 4;
  }
    if(digitalRead(7) == HIGH)
  {
    return 3;
  }
    if(digitalRead(6) == HIGH)
  {
    return 2;
  }
    if(digitalRead(5) == HIGH)
  {
    return 1;
  }

  return -1;
  
}

void fail()
{
  
  tmrpcm.setVolume(6);
    tmrpcm.play("GAMEOVER.WAV");
  Serial.println("Failed");
  delay(100000);
}

void inputHandler()
{

  int button = -1;
  
  for(int i = 0; i < seqIndex; i++)
  {
    inputResolved = false;
    
     while(!inputResolved)
     {
      //Wait for player to press a button
      Serial.println("Awaiting input");
      Serial.println(i);
      Serial.println(seqIndex);
      if(anyInput())
      {
        button = buttonPressed();

        if(button == sequence[i])
        {

          beep(sequence[i]);
          
          //Wait for player to release all buttons
          while(anyInput())
          {
            Serial.println("Waiting for all buttons to be released");
          }
          inputResolved = true;
        }
        else
        {
          fail();
        }
      }
     } 
  }

  Serial.println("Finished handling inputs");
  delay(2500);

  randomSeed(analogRead(A3));
  
  sequence[seqIndex] = random(1,5);
  seqIndex++;



  awaitingInput = false;
}

void loop() {
  // put your main code here, to run repeatedly:

 if(!awaitingInput)
  {
   displaySequence(); 
  } 

  if(awaitingInput)
  {
    inputHandler();
    }
  
}
