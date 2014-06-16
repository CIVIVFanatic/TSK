//authors: Ed Baafi, Robert Hayes
//(c)2013 Modkit LLC
//#include <wpp.h>
#include <micro_component.h>
//#include "wpp_pins.h"
//#include "micro_threads.h"
//***************************************************************************************/                                                                                     */
//*     Modkit Micro Framework - Light Sensor                                                           */                                                                                     */
//***************************************************************************************/



class  LinPot: MICRO_Thread {
public: 
	MICRO_Event MOVED;
	LinPot(AdcPin p);
	float readSlider();
	
	void micro_thread_run();
	void start();
	
private:        
	AdcPin pin;
	const uint8_t msDelay;
	const uint8_t changeThreshold;
	Analog currslideVal;  
};

LinPot::LinPot(AdcPin p):MICRO_Thread(MICRO_NEVER_EVENT),pin(p),msDelay(200),changeThreshold(5),currslideVal(0){
	start();
}

void LinPot::start(){
	triggerEvent();
}

void LinPot::micro_thread_run(){
	//this line is required when using "true" 
	// cooperative threading syntax. We're ok if
	// component makers have this small burden 
	COMPONENT_THREAD_SETUP;
	
	while(1){
		
		Analog prevslideVal = currslideVal;
		currslideVal = pin.analogRead();

		if(abs(currslideVal.percent() - prevslideVal.percent())>changeThreshold){
			broadcast(MOVED);
		}

        delay(msDelay);
		 
	}
	
}

float LinPot::readSlider(){
	return currslideVal.percent();
}


/* 
 #define LinPot_Scope(instance) namespace MICRO_APPEND_ITEMS(instance,_NAMESPACE){\
 bool pressed(){return instance.pressed();}\
 }
 
 */


//**********************************************************************/
//*  END COMPONENT EXAMPLES                                            */
//**********************************************************************/
