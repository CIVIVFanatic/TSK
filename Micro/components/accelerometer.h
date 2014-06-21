//Accelerometer class written by:
//Robert Hayes
//2014 TechSmartKids LLC

//Micro and wpp framework provided by:
//Ed Baafi
//(c)2013 Modkit LLC

#include <micro_component.h>
//***************************************************************************************/                                                                                     */
//*     Modkit Micro Framework - Light Sensor                                                           */                                                                                     */
//***************************************************************************************/



class  Accelerometer: MICRO_Thread {
public: 
	MICRO_Event SHAKENX;
	MICRO_Event SHAKENY;
	MICRO_Event SHAKENZ;
	MICRO_Event JERKX;
	MICRO_Event JERKY;
	MICRO_Event JERKZ;

	Accelerometer(AdcPin px, AdcPin py);
	Accelerometer(AdcPin px, AdcPin py, AdcPin pz);
	float readX();
	float readY();
	float readZ();
	
	void micro_thread_run();
	void start();
	
private:        
	AdcPin pinX;
	AdcPin pinY;
	AdcPin pinZ;
	const uint8_t msDelay;
	const float noG;
	const float oneG;
	const float jerkThreshold;
	const uint8_t numVal;
	const boolean usingZ;
	int currentLoc;
	float xVal[6];
	float yVal[6];
	float zVal[6];

/*	Analog xVal[6]; //make sure that this matches numVal!
	Analog yVal[6];
	Analog zVal[6];*/
};

Accelerometer::Accelerometer(AdcPin px, AdcPin py):MICRO_Thread(MICRO_NEVER_EVENT),pinX(px),pinY(py),pinZ(PIN20),msDelay(33),noG(48),oneG(10),jerkThreshold(25),numVal(6),usingZ(false),currentLoc(0){
	start();
}

Accelerometer::Accelerometer(AdcPin px, AdcPin py, AdcPin pz):MICRO_Thread(MICRO_NEVER_EVENT),pinX(px),pinY(py),pinZ(pz),msDelay(33),noG(48),oneG(10),jerkThreshold(25),numVal(6),usingZ(true),currentLoc(0){
	start();
}

void Accelerometer::start(){
	triggerEvent();
}

void Accelerometer::micro_thread_run(){
	//this line is required when using "true" 
	// cooperative threading syntax. We're ok if
	// component makers have this small burden 
	COMPONENT_THREAD_SETUP;
	
	while(1){		
		currentLoc = (currentLoc+1)%numVal;
		Analog temp(pinX.analogRead().percent());
		xVal[currentLoc] = temp.percent(); //All values are currently floats, so we use .percent()
		temp = pinY.analogRead();
		yVal[currentLoc] = temp.percent();
		if(usingZ){
			temp = pinZ.analogRead();
			zVal[currentLoc] = temp.percent();
		}

		if(abs(xVal[currentLoc]-noG)>jerkThreshold){ //this condition could be much better
			broadcast(JERKX);
			uint8_t hi = 0;
			uint8_t lo = 0;
			for(uint8_t i = 0;i<numVal; i++){
				if((xVal[i]-noG)>jerkThreshold){
					hi++;
				}else if((noG-xVal[i])>jerkThreshold){
					lo++;
				}
			}
			if((hi>0)&&(lo>0)&&((hi+lo)>2)){
				broadcast(SHAKENX);
			}
		}

		if(abs(yVal[currentLoc]-noG)>jerkThreshold){ //this condition could be much better
			broadcast(JERKY);
			uint8_t hi = 0;
			uint8_t lo = 0;
			for(uint8_t i = 0;i<numVal; i++){
				if((yVal[i]-noG)>jerkThreshold){
					hi++;
				}else if((noG-yVal[i])>jerkThreshold){
					lo++;
				}
			}
			if((hi>0)&&(lo>0)&&((hi+lo)>2)){
				broadcast(SHAKENY);
			}
		}

		if(usingZ){
			if(abs(zVal[currentLoc]-noG)>jerkThreshold){ //this condition could be much better
				broadcast(JERKZ);
				uint8_t hi = 0;
				uint8_t lo = 0;
				for(uint8_t i = 0;i<numVal; i++){
					if((zVal[i]-noG)>jerkThreshold){
						hi++;
					}else if((noG-zVal[i])>jerkThreshold){
						lo++;
					}
				}
				if((hi>0)&&(lo>0)&&((hi+lo)>2)){
					broadcast(SHAKENZ);
				}
			}
		}

        delay(msDelay);
		 
	}
	
}

float Accelerometer::readX(){
	return xVal[currentLoc];
}

float Accelerometer::readY(){
	return yVal[currentLoc];
}

float Accelerometer::readZ(){
	return zVal[currentLoc];
}

/* 
 #define LinPot_Scope(instance) namespace MICRO_APPEND_ITEMS(instance,_NAMESPACE){\
 bool pressed(){return instance.pressed();}\
 }
 
 */