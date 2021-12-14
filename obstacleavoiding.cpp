#include<Servo.h>
Servo myservo;


#define LA 6
#define LB 9
#define RA 11
#define RB 5
#define ENA 7
#define ENB 8


int trig = 2 ;
int echo = 3;
int cm;
int distance = 100;
void setup() {


  //sensor part
  pinMode(13, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  //servo
  myservo.attach(8);
  myservo.write(90);
  delay(1000);
  //motor part
  pinMode(LA, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(RA, OUTPUT);
  pinMode(RB, OUTPUT);
  //pinMode(ENA, OUTPUT);
  //pinMode(ENB, OUTPUT);


  //digitalWrite(ENA,HIGH);
  //digitalWrite(ENB,HIGH);

  distance = getdistance();


}

void loop() {

  int distanceR = 0;
  int distanceL =  0;
  delay(40);
  if (distance <= 40) {

    mstop();
    delay(300);
    distanceR = lookRight();
    delay(500);
    distanceL = lookLeft();
    delay(500);
    if (distanceR > 40 || distanceL > 40 ) {
      if (distanceR >= distanceL)
      {
        rightward();
        delay(350);
        mstop();
        

      } 
      else
      {
        leftward();
        delay(350);
        mstop();
      }

    } else {
      backward();
    }
  } else {
    analogWrite(RA, 100);
    analogWrite(RB, 0);
    analogWrite(LA, 100);
    analogWrite(LB, 0);
  }

  distance = getdistance();



}
// turn servo
int lookRight()
{
  myservo.write(30);
  delay(500);
  int distance = getdistance();
  delay(100);
  myservo.write(90);
  return distance;
}

int lookLeft()
{
  myservo.write(165);
  delay(500);
  distance = getdistance();
  delay(100);
  myservo.write(90);
  delay(100);
  return distance;

}
//get distance

int getdistance() {
  long duration;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  cm = (duration / 2) / 29.1;
  return cm;
}

void backward() {
  digitalWrite(LA, LOW);
  digitalWrite(LB, HIGH);
  digitalWrite(RA, LOW);
  digitalWrite(RB, HIGH);
  delay(200);
}

void forward() {
  analogWrite(RA, 100);
  analogWrite(RB, 0);
  analogWrite(LA, 100);
  analogWrite(LB, 0);
}


void mstop() {
  digitalWrite(LA, LOW);
  digitalWrite(LB, LOW);
  digitalWrite(RA, LOW);
  digitalWrite(RB, LOW);
}

void  leftward() {
  digitalWrite(LA, LOW);
  digitalWrite(LB, LOW);
  analogWrite(RA, 120);
  analogWrite(RB, 0);
}

void  rightward() {
  analogWrite(LA, 120);
  analogWrite(LB, 0);
  digitalWrite(RA, LOW);
  digitalWrite(RB, LOW);
}
