int con = 1;
int wert =11;
int pos = 0;

#include <Servo.h>

Servo myservo;  

void setup() {
  myservo.attach(1);
//  setupServo(con);
}

void loop() {
  if (pos == 0) {
    pos=90;
  } else {
    pos = 0;
  }
  //rotateServo(pos);
  myservo.write(pos);
  delay(1000);
}

//void setupServo(int connector) {
//  myservo.attach(connector);
//}
//
//void rotateServo(int degree) {
//  myservo.write(degree);
//  delay(1000);
//}

