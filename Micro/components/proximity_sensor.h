//Robert Hayes
//2014 Tech Smart Kids LLC
//Micro framework by Ed Baafi
//2013 ModKit LLC
//Light Sensor Code

#ifndef PROXIMITY_SENSOR_H
#define PROXIMITY_SENSOR_H

#include <micro_component.h>

class  ProximitySensor: MICRO_Thread {
public: 
	MICRO_Event NEAR;
	MICRO_Event FAR;
	MICRO_Event VERYNEAR;

	ProximitySensor(AdcPin p);
	float readDistance();
	float readIn();
	float readCm();
	
	void micro_thread_run();
	void start();
	
private:        
	AdcPin pin;
	Analog currDistVal;
	const uint8_t msDelay;
	float maxVal;
};

ProximitySensor::ProximitySensor(AdcPin p):MICRO_Thread(MICRO_NEVER_EVENT),pin(p),msDelay(200),currDistVal(0),maxVal(650.0){
	start();
}

void ProximitySensor::start(){
	triggerEvent();
}

void ProximitySensor::micro_thread_run(){
	//this line is required when using "true" 
	// cooperative threading syntax. We're ok if
	// component makers have this small burden 
	COMPONENT_THREAD_SETUP;
	
	while(1){
		
		
		Analog prevDistVal = currDistVal;
		Analog temp(map(pin.analogRead().percent(),0,maxVal/1023.0*100.0,0,100));
		currDistVal = temp;

		if((currDistVal.percent()>85)&&(prevDistVal.percent()<85)){
			broadcast(VERYNEAR);
		}else if((currDistVal.percent()>40)&&(prevDistVal.percent()<40)){
			broadcast(NEAR);
		}else if((currDistVal.percent()<15)&&(prevDistVal.percent()>15)){
			broadcast(NEAR);
		}

        delay(msDelay);
		 
	}
	
}

float ProximitySensor::readDistance(){
	return currDistVal.percent();
}

float ProximitySensor::readIn(){
	if(currDistVal.percent()<0.01)
	{
		return 1001.0; //large number is effectively infinity when values are on scale of < 12"
	}

	return 151.01/currDistVal.percent() - 0.0409; //This equation calculated from lsqreg in MATLAB using data collected in Arduino
}

float ProximitySensor::readCm(){
	return readIn()*2.54;
}

#endif