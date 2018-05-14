///////////////////////////////////
// SETTINGS //////////////////////
/////////////////////////////////
// TODO: Werte müssen angepasst werden
int pollution_80 = 80;
int pollution_70 = 70;
int pollution_60 = 60;
int pollution_50 = 50;
int pollution_40 = 40;
int pollution_30 = 30;
int pollution_20 = 20;
int pollution_10 = 10;

int servoRotation = 80;


///////////////////////////////////
// GENERAL ///////////////////////
/////////////////////////////////
#include"AirQuality.h"
#include"Arduino.h"
#include <Servo.h>
int currentQuality;
unsigned long time_since_startup;
int loop_count;

///////////////////////////////////
// LED ///////////////////////////
/////////////////////////////////
unsigned char bytes[]={B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000};
unsigned char eight      = B11111111;
unsigned char seven      = B11111110;
unsigned char six        = B11111100;
unsigned char five       = B11111000;
unsigned char four       = B11110000;
unsigned char three      = B11100000;
unsigned char two        = B11000000;
unsigned char one        = B10000000;
unsigned char zero       = B00000000;
uint8_t rowPins[8]={ A3, 12, 2, A0, 9, 3, 8, 5 };
uint8_t colPins[8]={ 13, 7, 6, A2, 4, A1, 11, 10 };

void setupLEDMatrix() {
  for(int i = 0; i < 8; i++) {
    pinMode(colPins[i],OUTPUT);
    pinMode(rowPins[i],OUTPUT);
  }
}

void setLEDMatrix(uint8_t img[]) {
  for(int row = 0; row < 8; row++) {
    for(int k = 0; k < 8; k++) digitalWrite(colPins[k], HIGH); // Cleanup cols
    digitalWrite(rowPins[row], HIGH); // prepare to write the row
    for(int col = 0; col < 8; col++) {
      digitalWrite(colPins[7 - col], img[row] & 1 << col ? LOW : HIGH);
    }
    delay(1);
    digitalWrite(rowPins[row],LOW);
  }
}

void LED_setValueToRow(int row, unsigned char byte_array){
  bytes[row] = byte_array;
}

void showMeasureAnimation() {
}

void displayResult(int input) {
  time_since_startup = millis();
  if(time_since_startup % 1000 == 0){
    //Logging time in Miliseconds
    //Serial.print(time_since_startup);
    loop_count = loop_count % 8;
    if (input < pollution_10) {
      LED_setValueToRow(loop_count, zero);

      Serial.print(input);
      Serial.print(" NO POLLUTION \n");
    }
    else if (input < pollution_20) {
      LED_setValueToRow(loop_count, one);
      Serial.print(input);
      Serial.print(" LOW \n");
    }
    else if (input < pollution_30) {
      LED_setValueToRow(loop_count, two);
      Serial.print(input);
      Serial.print(" LOW \n");
    }
    else if (input < pollution_40) {
      LED_setValueToRow(loop_count, three);
      Serial.print(input);
      Serial.print(" MED \n");
    }
    else if (input < pollution_50) {
      LED_setValueToRow(loop_count, four);
      Serial.print(input);
      Serial.print(" MED \n");
    }
    else if (input < pollution_60) {
      LED_setValueToRow(loop_count, five);
      Serial.print(input);
      Serial.print(" HIGH \n");
    }
    else if (input < pollution_70) {
      LED_setValueToRow(loop_count, six);
      Serial.print(input);
      Serial.print(" HIGH \n");
    }
    else if (input < pollution_80) {
      LED_setValueToRow(loop_count, seven);
      Serial.print(input);
      Serial.print(" SUPER HIGH \n");
    }
    else if (input > pollution_80) {
      LED_setValueToRow(loop_count, eight);
      Serial.print(input);
      Serial.print(" SUPER HIGH \n");
    }


    loop_count++;
  }
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

void setup() {
  Serial.begin(9600);
  setupLEDMatrix();
  setupAirQualitySensor();
  //setupServo(servoPin);
}

void loop() {
  setLEDMatrix(bytes);
  currentQuality = getAirQuality();
  displayResult(currentQuality); // has no delay included
  //rotateServo(servoRotation);
}


ISR(TIMER1_OVF_vect)
{
  if(airqualitysensor.counter == 61)//set 2 seconds as a detected duty
  {
      airqualitysensor.last_vol    = airqualitysensor.first_vol;
      airqualitysensor.first_vol   = analogRead(A5);
      airqualitysensor.counter     = 0;
      airqualitysensor.timer_index = 1;
      PORTB=PORTB^0x20;
  }
  else
  {
    airqualitysensor.counter++;
  }
}
