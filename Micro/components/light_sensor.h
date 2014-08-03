//Robert Hayes
//2014 Tech Smart Kids LLC
//Micro framework by Ed Baafi
//2013 ModKit LLC
//Light Sensor Code

#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include <micro_component.h>

class  LightSensor: MICRO_Thread {
public: 
	MICRO_Event LIGHT;
	MICRO_Event DARK;
	MICRO_Event LIGHTER;
	MICRO_Event DARKER;
	MICRO_Event CHANGED;

	LightSensor(AdcPin p);
	float readLight();
	
	void micro_thread_run();
	void start();
	
private:        
	AdcPin pin;
	Analog currlightVal;
	const uint8_t msDelay;
	const uint8_t changeThreshold;
	const boolean brightUp;
};

LightSensor::LightSensor(AdcPin p):MICRO_Thread(MICRO_NEVER_EVENT),pin(p),msDelay(200),changeThreshold(5),brightUp(true),currlightVal(0){
	start();
}

void LightSensor::start(){
	triggerEvent();
}

void LightSensor::micro_thread_run(){
	//this line is required when using "true" 
	// cooperative threading syntax. We're ok if
	// component makers have this small burden 
	COMPONENT_THREAD_SETUP;
	
	while(1){
		
		Analog switchVal(100 - pin.analogRead().percent()); //needed for type-matching the ternary statement

		Analog prevlightVal = currlightVal;
		currlightVal = brightUp? pin.analogRead() : switchVal; //Always read brigthness as high and darkness as low

		if((currlightVal.percent()>75)&&(prevlightVal.percent()<75)){
			broadcast(LIGHT);
		}
		if((currlightVal.percent()<50)&&(prevlightVal.percent()>50)){
			broadcast(DARK);
		}		
		if(abs(currlightVal.percent() - prevlightVal.percent())>changeThreshold){
			broadcast(CHANGED);
			if(currlightVal.percent() > prevlightVal.percent()){
				broadcast(LIGHTER);
			}else{
				broadcast(DARKER);
			}
		}

        delay(msDelay);
		 
	}
	
}

float LightSensor::readLight(){
	return currlightVal.percent();
}

#endif