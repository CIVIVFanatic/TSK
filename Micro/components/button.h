//authors: Ed Baafi, Robert Hayes
//(c)2013 Modkit LLC, 2014 TechSmartKids LLC
//Button Class Code

#ifndef BUTTON_H
#define BUTTON_H

#include <micro_component.h>

    class  Button: MICRO_Thread {
        public: 
          MICRO_Event PRESSED;
	      MICRO_Event RELEASED;
	      MICRO_Event HELD;
	      Button(GpioPin p);
          Button(GpioPin p, int pUp);
	      bool down();
          void micro_thread_run();
          void start();
          
        private:
		  bool pullUp;
		  bool eventPressed;
		  bool isDown;
          GpioPin pin;
	      uint8_t heldCount; 
    };
    
	Button::Button(GpioPin p):MICRO_Thread(MICRO_NEVER_EVENT),pin(p),pullUp(false),eventPressed(false),heldCount(0){
         pin.setMode(INPUT);
         start();
    }

    Button::Button(GpioPin p, int pUp):MICRO_Thread(MICRO_NEVER_EVENT),pin(p),eventPressed(false),heldCount(0){
         pin.setMode(INPUT);
		 switch (pUp){
		 case 0:
			 pullUp = false;
		     pin.setPullup(LOW);
			 break;
		 case 1:
			 pullUp = true;
		     pin.setPullup(LOW);
			 break;
		 case 2:
			 pullUp = true;
			 pin.setPullup(HIGH);
			 break;
		 }
         start();
    }
    
    bool Button::down(){
       return isDown;
    }
    void Button::start(){
       triggerEvent();
    }
    void Button::micro_thread_run(){
      //this line is required when using "true" 
      // cooperative threading syntax. We're ok if
      // component makers have this small burden 
      COMPONENT_THREAD_SETUP;
      eventPressed = false;

      while(1){
		isDown = pullUp? (!pin.digitalRead()) : pin.digitalRead();
        if(isDown){
            if(!eventPressed){                
                broadcast(PRESSED);
                eventPressed = true;
            }else{
				heldCount++;
			}
        }else{
			heldCount = 0;
			if(eventPressed){
				broadcast(RELEASED);
			}
			eventPressed = false;
        }
		if(heldCount == 15){
			broadcast(HELD);
		}
		delay(30);
	  }
	}
 
#endif