//authors: Ed Baafi, Robert Hayes
//(c)2013 Modkit LLC
//#include <wpp.h>
#include <micro_component.h>
//#include "wpp_pins.h"
//#include "micro_threads.h"
//***************************************************************************************/                                                                                     */
//*     Modkit Micro Framework - Light Sensor                                                           */                                                                                     */
//***************************************************************************************/



class  Knob: MICRO_Thread {
public: 
	MICRO_Event TURNED;
	MICRO_Event TURNED_CLOCKWISE;
	MICRO_Event TURNED_COUNTERCLOCKWISE;
	Knob(AdcPin p);
	float readKnob();
	float readStep(int step);
	float readStep(int step, int min, int max);
	
	void micro_thread_run();
	void start();
	
private:        
	AdcPin pin;
	const uint8_t msDelay;
	const uint8_t changeThreshold;
	const boolean clockwiseUp;
	Analog currknobVal;  
};

Knob::Knob(AdcPin p):MICRO_Thread(MICRO_NEVER_EVENT),pin(p),msDelay(200),changeThreshold(5),currknobVal(0),clockwiseUp(false){
	start();
}

void Knob::start(){
	triggerEvent();
}

void Knob::micro_thread_run(){
	//this line is required when using "true" 
	// cooperative threading syntax. We're ok if
	// component makers have this small burden 
	COMPONENT_THREAD_SETUP;
	
	while(1){
		
		Analog switchVal(100 - pin.analogRead().percent()); //needed for type-matching the ternary statement
		Analog prevknobVal = currknobVal;
		currknobVal = clockwiseUp? pin.analogRead() : switchVal;

		if(abs(currknobVal.percent() - prevknobVal.percent())>changeThreshold){
			broadcast(TURNED);
			if(currknobVal.percent()>prevknobVal.percent()){
				broadcast(TURNED_CLOCKWISE);
			}else{
				broadcast(TURNED_COUNTERCLOCKWISE);
			}
		}

        delay(msDelay);
		 
	}
	
}

float Knob::readKnob(){
	return currknobVal.percent();
}

float Knob::readStep(int steps){
	return map(currknobVal.percent(),0,100,1,steps+1);
}

float Knob::readStep(int steps, int min, int max){
	return map(currknobVal.percent(),min,max,1,steps+1);
}

/* 
 #define Knob_Scope(instance) namespace MICRO_APPEND_ITEMS(instance,_NAMESPACE){\
 bool pressed(){return instance.pressed();}\
 }
 
 */


//**********************************************************************/
//*  END COMPONENT EXAMPLES                                            */
//**********************************************************************/