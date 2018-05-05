#include"AirQuality.h"
#include"Arduino.h"
AirQuality airqualitysensor;
int current_quality =-1;

#include <Servo.h>

Servo myservo;
int pos = 0;

void setup(){

  myservo.attach(1);
    Serial.begin(9600);
    airqualitysensor.init(14);
}
void loop()
{
    current_quality=airqualitysensor.slope();
    if (current_quality >= 0)// if a valid data returned.
    {
        if (current_quality==0) {
          delay(2000);
            Serial.println("High pollution! Force signal active");
           pos=180;
              
              }
        else if (current_quality==1){
            Serial.println("High pollution!");
             pos=180;
              
            }
        else if (current_quality==2 ){
            Serial.println("Low pollution!");
            pos=0;                      
  }
            
            }
        else if (current_quality ==3){
            Serial.println("Fresh air");
            pos=0;                    
  }

myservo.write(pos);
delay(5000);
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


