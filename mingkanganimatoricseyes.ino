#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  275
#define SERVOMAX  425
#define XSERVOMIN  225
#define XSERVOMAX  425
const int trigPin = 9;  
const int echoPin = 10; 
float duration, distance;
uint8_t servonum = 1;
int previousMotionState = 0;
void setup() {
  pwm.begin();
  // pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);
  delay(10);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
  // put your main code here, to run repeatedly:
  int motionState = digitalRead(2);
  Serial.println(motionState);
  // if (motionState == 1 & previousMotionState==0)  {
  //   kelip();
  //   previousMotionState = 1;
  // }
  if (distance <= 100)
  {
    kelip();
    previousMotionState = 1;
  }
  if (motionState == 1 & previousMotionState==1)  {
    previousMotionState = 1;
  }
  if (motionState == 0 & previousMotionState == 1 )
  {
    previousMotionState = 0;
  }
    if (motionState == 0 & previousMotionState == 0 )
  {
    previousMotionState = 0;
  }
}

void kelip(){
    for (uint16_t pulsediff = 0; pulsediff < XSERVOMAX - XSERVOMIN; pulsediff++) {
    pwm.setPWM(4, 0, XSERVOMIN+pulsediff);
    delay(2);
  }

  delay(10);
  for (uint16_t pulsediff = 0; pulsediff < XSERVOMAX - XSERVOMIN; pulsediff++) {
    pwm.setPWM(4, 0, XSERVOMAX-pulsediff);

    delay(2);
  }
    for (uint16_t pulsediff = 0; pulsediff < (XSERVOMAX - XSERVOMIN)/2; pulsediff++) {
    pwm.setPWM(4, 0, XSERVOMIN+pulsediff);
    delay(2);
  }
  for (uint16_t pulsediff = 0; pulsediff < SERVOMAX - SERVOMIN; pulsediff++) {
    pwm.setPWM(0, 0, SERVOMIN+pulsediff);
    pwm.setPWM(1, 0, SERVOMAX-pulsediff);
    pwm.setPWM(3, 0, SERVOMIN+pulsediff);
    pwm.setPWM(2, 0, SERVOMAX-pulsediff);
  }
    for (uint16_t pulsediff = 0; pulsediff < SERVOMAX - SERVOMIN; pulsediff++) {
    pwm.setPWM(0, 0, SERVOMAX-pulsediff);
    pwm.setPWM(1, 0, SERVOMIN+pulsediff);
    pwm.setPWM(3, 0, SERVOMAX-pulsediff);
    pwm.setPWM(2, 0, SERVOMIN+pulsediff);

    delayMicroseconds(100);
  }
  delay(500);
}