//authors: Robert Hayes
//2014 TechSmartKids LLC
//micro framework: Ed Baafi, (c) 2013 ModKit
//IR Detector Class

#ifndef IR_DETECTOR_H
#define IR_DETECTOR_H

#include <micro_component.h>

 class IRDetector:MICRO_Thread{
	public:
	MICRO_Event TURN_ON;
	IRDetector(AdcPin p):MICRO_Thread(MICRO_NEVER_EVENT),pin(p),msDelay(200),onThreshold(85),currIRVal(0){start();};
	float readIR();
	bool on();
	
	void micro_thread_run();
	void start();
	
	private:        
	AdcPin pin;
	const uint8_t msDelay;
	const uint8_t onThreshold;
	Analog currIRVal;
 };

void IRDetector::start(){
	triggerEvent();
}

void IRDetector::micro_thread_run(){
	//this line is required when using "true" 
	// cooperative threading syntax. We're ok if
	// component makers have this small burden 
	COMPONENT_THREAD_SETUP;
	
	while(1){
		
		Analog prevIRVal = currIRVal;
		currIRVal = pin.analogRead();

		if(on()&&(prevIRVal.percent()<onThreshold)){
			broadcast(TURN_ON);
		}

        delay(msDelay);
		 
	}
	
}

float IRDetector::readIR(){
	return currIRVal.percent();
}

bool IRDetector::on(){
	if(readIR()>onThreshold){
		return true;
	}else{
		return false;
	}
}

#endif