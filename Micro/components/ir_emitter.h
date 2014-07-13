//authors: Robert Hayes
//2014 TechSmartKids LLC
//micro framework: Ed Baafi, (c) 2013 ModKit
//IR Emitter Class

#ifndef IR_EMITTER_H
#define IR_EMITTER_H

#include <micro_component.h>

    class IREmitter{
        public: 
			IREmitter(GpioPwmPin p):pin(p),brightness(100),isOn(false){pin.setMode(OUTPUT).pwmWrite(0);};
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
    

    void IREmitter::on(){
		isOn = true;
		pin.pwmWrite(brightness);
	}
    
	void IREmitter::off(){
		isOn = false;
		pin.pwmWrite(0);
	}

	void IREmitter::setBrightness(float value){
		brightness = value;
		if(isOn){pin.pwmWrite(brightness);}
	}

	float IREmitter::getBrightness(){
		return brightness;
	}

	bool IREmitter::state(){
		return isOn;
	}
 
#endif