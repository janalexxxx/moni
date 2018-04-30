
int wert =11;

#include <Servo.h>

Servo myservo;  
int pos = 0;   

void setup() {
  myservo.attach(1);  

void loop() {
  if(wert<10 && pos <= 180){
     pos++;
     myservo.write(pos); 
    } 
  if(wert>10 && pos >= 0){
     pos--;
     myservo.write(pos);            
   }    
}

