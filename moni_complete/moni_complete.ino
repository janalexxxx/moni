///////////////////////////////////
// SETTINGS //////////////////////
/////////////////////////////////
int loopTimer = 5000;

int barrierHighPollution = 80;
int barrierMediumPollution = 70;
int barrierLowPollution = 60;
int barrierNoPollution = 50;

int servoRotation = 80;



///////////////////////////////////
// GENERAL ///////////////////////
/////////////////////////////////
#include"AirQuality.h"
#include"Arduino.h"
#include <Servo.h>
int currentQuality;


///////////////////////////////////
// LED ///////////////////////////
/////////////////////////////////
byte character[8]={0x6c, 0xfe, 0xfe, 0x7c, 0x38, 0x10, 0x0, 0x0};
uint8_t rowPins[8]={ A3, 12, 2, A0, 9, 3, 8, 5 };
uint8_t colPins[8]={ 13, 7, 6, A2, 4, A1, 11, 10 };

void setupLEDMatrix() {
  for(int i=0; i<8; i++) {
    pinMode(colPins[i],OUTPUT);
    pinMode(rowPins[i],OUTPUT); 
  }
}

void setLEDMatrix(uint8_t img[]) {
  for(int row=0; row<8; row++) {
    for(int k=0; k<8; k++) digitalWrite(colPins[k],HIGH); // Cleanup cols
    digitalWrite(rowPins[row], HIGH); // prepare to write the row
    for(int col=0; col<8; col++) {
      digitalWrite(colPins[7-col], img[row] & 1 << col ? LOW : HIGH);
    }
    delay(1);
    digitalWrite(rowPins[row],LOW);
  } 
}

void showMeasureAnimation() {
}

void displayResult(int input) {
  if (input > barrierHighPollution) {
    displayHighPollution();
  } else if (input > barrierMediumPollution) {
    displayMediumPollution();
  } else if (input > barrierLowPollution) {
    displayLowPollution();
  } else if (input > barrierNoPollution) {
    displayNoPollution();
  }
}

void displayHighPollution() {
}

void displayMediumPollution() {
}

void displayLowPollution() {
}

void displayNoPollution() {
}

///////////////////////////////////
// SERVO /////////////////////////
/////////////////////////////////
Servo myServo;
int servoPin = 1;
boolean servoDown = true;


void setupServo(int connector) {
  myServo.attach(connector);
}

void rotateServo(int degree) {
  if (servoDown) {
    myServo.write(degree);
    servoDown = false;
  } else {
    myServo.write(0);
    servoDown = true;
  }
  delay(1000);
}

///////////////////////////////////
// AIR QUALITY SENSOR ////////////
/////////////////////////////////

AirQuality airqualitysensor;
int airQualityPin = 1;

void setupAirQualitySensor() {
  airqualitysensor.init(airQualityPin);
}

int getAirQuality() {
  return airqualitysensor.first_vol;
}

ISR(TIMER1_OVF_vect)
{
  if(airqualitysensor.counter==61)//set 2 seconds as a detected duty
  {

      airqualitysensor.last_vol=airqualitysensor.first_vol;
      airqualitysensor.first_vol=analogRead(A5);
      airqualitysensor.counter=0;
      airqualitysensor.timer_index=1;
      PORTB=PORTB^0x20;
  }
  else
  {
    airqualitysensor.counter++;
  }
}







void setup() {
  //Serial.begin(9600);
  setupLEDMatrix();
  setupAirQualitySensor();
  setupServo(servoPin);
}

void loop() {
  showMeasureAnimation(); // has delays included. takes some time.
  currentQuality = getAirQuality();
  displayResult(currentQuality); // has no delay included
  rotateServo(servoRotation); 
  delay(loopTimer); // time that result is displayed before new measurement starts
}
