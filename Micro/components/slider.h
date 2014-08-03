//author:Robert Hayes
//2014 Tech Smart Kids LLC
//Micro framework provided by Ed Baafi
//(c) 2013 ModKit LLC
//Slider component code

#ifndef SLIDER_H
#define SLIDER_H

#include <micro_component.h>

class  Slider: MICRO_Thread {
public: 
	MICRO_Event MOVED;
	Slider(AdcPin p);
	float readSlider();
	float readStep(int steps);
	float readStep(int steps, int min, int max);
	
	void micro_thread_run();
	void start();
	
private:        
	AdcPin pin;
	const uint8_t msDelay;
	const uint8_t changeThreshold;
	Analog currslideVal;  
};

Slider::Slider(AdcPin p):MICRO_Thread(MICRO_NEVER_EVENT),pin(p),msDelay(200),changeThreshold(5),currslideVal(0){
	start();
}

void Slider::start(){
	triggerEvent();
}

void Slider::micro_thread_run(){
	//this line is required when using "true" 
	// cooperative threading syntax. We're ok if
	// component makers have this small burden 
	COMPONENT_THREAD_SETUP;
	
	while(1){
		
		Analog prevslideVal = currslideVal;
		Analog tempVal(100 - pin.analogRead().percent());
		currslideVal = tempVal;

		if(abs(currslideVal.percent() - prevslideVal.percent())>changeThreshold){
			broadcast(MOVED);
		}

        delay(msDelay);
		 
	}
	
}

float Slider::readSlider(){
	return currslideVal.percent();
}

float Slider::readStep(int steps){
	return constrain(map(currslideVal.percent(),0,100,1,steps+1),1,steps);
}

float Slider::readStep(int steps, int min, int max){
	return constrain(map(currslideVal.percent(),min,max,1,steps+1),1,steps);
}

#endif