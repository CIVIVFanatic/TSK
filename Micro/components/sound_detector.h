//authors: Robert Hayes
//2014 TechSmartKids LLC
//micro framework: Ed Baafi, (c) 2013 ModKit
//Sound Detector Class

#ifndef SOUND_DETECTOR_H
#define SOUND_DETECTOR_H

#include <micro_component.h>

 class SoundDetector:MICRO_Thread{
	public:
	MICRO_Event LOUD;
	MICRO_Event QUIET;
	MICRO_Event NOISY;
	SoundDetector(GpioPin p):MICRO_Thread(MICRO_NEVER_EVENT),pin(p),msDelay(20),isOn(false),wasOn(false),heldCount(0){pin.setMode(INPUT); start();};
	bool listen();
	
	void micro_thread_run();
	void start();
	
	private:        
	GpioPin pin;
	const uint8_t msDelay;
	bool isOn;
	bool wasOn;
	uint8_t heldCount;

 };

void SoundDetector::start(){
	triggerEvent();
}

void SoundDetector::micro_thread_run(){
	//this line is required when using "true" 
	// cooperative threading syntax. We're ok if
	// component makers have this small burden 
	COMPONENT_THREAD_SETUP;
	
	while(1){
		isOn = pin.digitalRead();
        if(isOn){
            if(!wasOn){                
                broadcast(LOUD);
                wasOn = true;
            }else{
				heldCount++;
			}
        }else{
			heldCount = 0;
			if(wasOn){
				broadcast(QUIET);
			}
			wasOn = false;
        }
		if(heldCount == 25){
			broadcast(NOISY);
		}
		delay(msDelay);
	}
	
}

bool SoundDetector::listen(){
	return isOn;
}

#endif