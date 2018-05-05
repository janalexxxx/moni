#include"Arduino.h"
#include"AirQuality.h"

//Get the avg voltage in 5 minutes.

void AirQuality::avgVoltage()
{
	if(i==150)//sum 5 minutes
	{
		vol_standard=temp/150; 
		temp=0;
		Serial.print("Vol_standard in 5 minutes:");			
		Serial.println(vol_standard);		
		i=0;		
	}
    else 
	{
		temp+=first_vol;
		i++;
	}
}
void AirQuality::init(int pin)
{
    _pin=pin;
    pinMode(_pin,INPUT);
    unsigned char i=0;
    delay(3000);
    Serial.println("sys_starting...");
    delay(20000);//200000
    init_voltage=analogRead(_pin);

    Serial.println("The init voltage is ...");
    Serial.println(init_voltage);
    while(init_voltage)
    {
        if(init_voltage<798 && init_voltage>10)// the init voltage is ok
        {
            first_vol=analogRead(A5);//initialize first value
            last_vol=first_vol;
            vol_standard=last_vol;
            Serial.println("Sensor ready.");
            error=false;;
            break;
        }
        else if(init_voltage>798||init_voltage<=10)
        {	
            i++;
            Serial.println("waitting sensor init..(it takes 20 seconds to init)");
            delay(2000);//60000
            init_voltage=analogRead(A5);
            if(i==5)
            {
                i=0;
                error=true;
                Serial.println("Sensor Error!");
            }
          }
        else 
        break;
    }
    //init the timer 
    TCCR1A=0;//normal model
    TCCR1B=0x02;//set clock as 8*(1/16M)
    TIMSK1=0x01;//enable overflow interrupt
    Serial.println("Test begin...");
    sei();
}
int AirQuality::slope(void)
{
  while(timer_index)
	{
    	if(first_vol-last_vol>400||first_vol>60)
        {
            Serial.println("High pollution! Force signal active.");		
            timer_index=0;	
            avgVoltage();	
            return 0;	
        }
    	else if((first_vol-last_vol>400&&first_vol<60)||first_vol-vol_standard>150)
        {	
            Serial.print("sensor_value:");		
            Serial.print(first_vol);      		
            Serial.println("\t High pollution!");		
            timer_index=0;	
            avgVoltage();
            return 1;
            
        }
    	else if((first_vol-last_vol>200&&first_vol<60)||first_vol-vol_standard>50)
        {
            //Serial.println(first_vol-last_vol);
            Serial.print("sensor_value:");
            Serial.print(first_vol);      		
            Serial.println("\t Low pollution!");		
            timer_index=0;
            avgVoltage();
            return 2;	
        }
    	else
        {
            avgVoltage();	
            Serial.print("sensor_value:");
            Serial.print(first_vol);
            Serial.println("\t Air fresh");
            timer_index=0;
            return 3;
        }
	}
    return -1;
}

