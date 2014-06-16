//authors: Ed Baafi, Robert Hayes
//(c)2013 Modkit LLC
//#include <wpp.h>
#include <micro_component.h>
//#include "wpp_pins.h"
//#include "micro_threads.h"
//***************************************************************************************/                                                                                     */
//*     Modkit Micro Framework - Light Sensor                                                           */                                                                                     */
//***************************************************************************************/



class  LightSensor: MICRO_Thread {
public: 
	MICRO_Event LIGHT;
	MICRO_Event DARK;
	MICRO_Event BRIGHTER;
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
	const uint8_t brightThreshold;
	const boolean brightUp;
};

LightSensor::LightSensor(AdcPin p):MICRO_Thread(MICRO_NEVER_EVENT),pin(p),msDelay(200),changeThreshold(5),brightUp(false),currlightVal(0),brightThreshold(50.0){
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

		if((currlightVal.percent()>brightThreshold)&&(prevlightVal.percent()<brightThreshold)){
			broadcast(LIGHT);
		}
		if((currlightVal.percent()<brightThreshold)&&(prevlightVal.percent()>brightThreshold)){
			broadcast(DARK);
		}		
		if(abs(currlightVal.percent() - prevlightVal.percent())>changeThreshold){
			broadcast(CHANGED);
			if(currlightVal.percent() > prevlightVal.percent()){
				broadcast(BRIGHTER);
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


/* 
 #define LightSensor_Scope(instance) namespace MICRO_APPEND_ITEMS(instance,_NAMESPACE){\
 bool pressed(){return instance.pressed();}\
 }
 
 */


//**********************************************************************/
//*  END COMPONENT EXAMPLES                                            */
//**********************************************************************/



