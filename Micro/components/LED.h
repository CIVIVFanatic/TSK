//authors: Ed Baafi, Robert Hayes
//(c)2013 Modkit LLC
//#include <wpp.h>
#include <micro_component.h>
//#include "wpp_pins.h"
//#include "micro_threads.h"
//***************************************************************************************/                                                                                     */
//*     Modkit Micro Framework - LED                                                           */                                                                                     */
//***************************************************************************************/



    class LED{
        public: 
			LED(GpioPwmPin p):pin(p),brightness(100),isOn(false){pin.setMode(OUTPUT).pwmWrite(0);};
            void on();
			void off();
			void setBrightness(float value);
			float getBrightness();
			bool state();
        private:        
			GpioPwmPin pin;
            float brightness;
            bool isOn;
};
    

    void LED::on(){
		isOn = true;
		pin.pwmWrite(brightness);
	}
    
	void LED::off(){
		isOn = false;
		pin.pwmWrite(0);
	}

	void LED::setBrightness(float value){
		brightness = value;
		if(isOn){pin.pwmWrite(brightness);}
	}

	float LED::getBrightness(){
		return brightness;
	}

	bool LED::state(){
		return isOn;
	}
 

 
//**********************************************************************/
//*  END COMPONENT EXAMPLES                                            */
//**********************************************************************/
