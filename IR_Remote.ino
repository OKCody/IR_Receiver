#include <digitalWriteFastTiny.h>

int address = 0x20;
int waitTime = 50;  //time between pulses
//int command = 0xC0;
int rightFor = 0x01;
int rightRev = 0x02;
int leftFor  = 0x03;
int leftRev  = 0x04;

int LEDs = 0;

int n, c, k;

void command(int);
void out(int);
void zero(void);
void one(void);
void lead(void);

void setup()
{
  pinMode(LEDs, OUTPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
}

void loop()
{
  if( digitalRead(2) ){
    command( rightFor );
  }
  if( digitalRead(1) ){
    command( rightRev );
  }
  if( digitalRead(3) ){
    command( leftFor );
  }
  if( digitalRead(4) ){
    command( leftRev );
  }
}

void command(int command){
  lead();
  out(address);
  out(~address);
  out(command);
  out(~command);
  one();                //terminating bit
  delay(waitTime);
}

void out( int n){
  for(c = 7; c >= 0; c--)
  {
    k = n >> c;
    if (k & 1)
    {
      one();
    }
    else
    {
      zero();
    }
  }
}

void zero(void){
  digitalWriteFast(LEDs, LOW);
  delayMicroseconds(562);
  digitalWriteFast(LEDs, HIGH);
  delayMicroseconds(562);
}

void one(void){
  digitalWriteFast(LEDs, LOW);
  delayMicroseconds(562);
  digitalWriteFast(LEDs, HIGH);
  delayMicroseconds(1688);
}

void lead(void){
  digitalWriteFast(LEDs, LOW);  //38KHz on
  delayMicroseconds(9000);
  digitalWriteFast(LEDs, HIGH); //38KHz off
  delayMicroseconds(4500);
}

