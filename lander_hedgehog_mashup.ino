//Europa Lander code for Loss of Signal
//Written by Colin Thomas Nichols

#include <Servo.h>

//Define Motor pins

#define AIN1 5
#define AIN2 4
#define PWMA 3
#define BIN1 7
#define BIN2 8
#define PWMB 9
#define STBY 6

//Define LED pins
int power_led = 10; //Power LED
int tx_led = 11; //Transmission LED
int flash = A3; //Clear LEDs tied to Analog Pin 3

//Define RF pins
int pin1 = A0; //RF Chan1 Y axis to Analog pin 0
int pin2 = A1; //RF Chan1 X axis to Analog pin 1
int pin3 = A2; //RF Chan2 X axis to Analog pin 3

//RF Control limits for servos:
//Wheel A
int neutralHa = 1450;
int neutralLa = 1400;
int maxVala = 1720;
int minVala = 1300;

//Wheel B
int neutralHb = 1600;
int neutralLb = 1570;
int maxValb = 1920;
int minValb = 1390;

const int offsetA = 1;
const int offsetB = 1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

int pos = 0;
Servo servo1;
Servo servo2;

#define flash A3

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); //Begin Serial Connection
  //Declare the function of all the pins!
  pinMode (power_led, OUTPUT);
  pinMode (tx_led, OUTPUT);
  pinMode (pin1, INPUT);
  pinMode (pin2, INPUT);
  pinMode (pin3, INPUT);
  pinMode (flash,OUTPUT);
  servo1.attach(1);
  servo2.attach(2);

}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(power_led, HIGH);
  digitalWrite(tx_led, LOW);

  int sV1; //speed values to be mapped
  int sV2;
  int sV3;
  int sV4;

 int AValue = pulseIn(pin1, HIGH);
 int BValue = pulseIn(pin2, HIGH);
 int CValue = pulseIn(pin3, HIGH);

 Serial.println(AValue);
// Serial.println(BValue);
// Serial.println(CValue);

//tx NOT ON
if (CValue <= 1600) {
  digitalWrite(tx_led, LOW);
  delay(50);
}

//tx ON
if (CValue >= 1610) {
  digitalWrite(tx_led, HIGH);
  delay(50);
}

//DONT SPIN WHEEL A
if (AValue >= neutralLa && AValue <= neutralHa) { //wheel A is neutral
  servo1.write(90);
  motor1.brake();
  delay(50);
}

//SPIN WHEEL A FORWARD
if (AValue > neturalHa) { //if speed is high
  sV1 = map(AValue, neutralHa, maxVala, 140, 255); //map the speed value to analog output
  if (sV1 > 255) { //if speed happens to be over 255, change it to 255
    sV1 = 255;
  }
  motor1.drive(sV1);
  delay(50);
}

  }
}

}
