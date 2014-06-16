//author:Robert Hayes
//(c)2014 Tech Smart Kids
//#include <wpp.h>
#include <micro_component.h>
//#include "wpp_pins.h"
//#include "micro_threads.h"
//***************************************************************************************/                                                                                     */
//*     Modkit Micro Framework - Light Sensor                                                           */                                                                                     */
//***************************************************************************************/



class  Joystick: MICRO_Thread {
public: 
	MICRO_Event UP;
	MICRO_Event DOWN;
	MICRO_Event LEFT;
	MICRO_Event RIGHT;
	Joystick(AdcPin x, AdcPin y);
	float readX();
	float readY();
	
	void micro_thread_run();
	void start();
	
private:        
	AdcPin xPin;
	AdcPin yPin;
	const uint8_t msDelay;
	Analog xVal;
	Analog yVal;
};

Joystick::Joystick(AdcPin x, AdcPin y):MICRO_Thread(MICRO_NEVER_EVENT),xPin(x),yPin(y),msDelay(300),xVal(0),yVal(0){
	start();
}

void Joystick::start(){
	triggerEvent();
}

void Joystick::micro_thread_run(){
	//this line is required when using "true" 
	// cooperative threading syntax. We're ok if
	// component makers have this small burden 
	COMPONENT_THREAD_SETUP;
	
	while(1){
		xVal = xPin.analogRead();
		yVal = yPin.analogRead();
		if(xVal.percent()>80){
			broadcast(RIGHT);
		}
		if(xVal.percent()<20){
			broadcast(LEFT);
		}
		if(yVal.percent()>80){
			broadcast(UP);
		}
		if(yVal.percent()>80){
			broadcast(DOWN);
		}
        delay(msDelay);
		 
	}
	
}

float Joystick::readX(){
	return xVal.percent();
}

float Joystick::readY(){
	return yVal.percent();
}

/* 
 #define Joystick_Scope(instance) namespace MICRO_APPEND_ITEMS(instance,_NAMESPACE){\
 bool pressed(){return instance.pressed();}\
 }
 
 */


//**********************************************************************/
//*  END COMPONENT EXAMPLES                                            */
//**********************************************************************/
