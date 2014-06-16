//author: Ed Baafi
//(c)2013 Modkit LLC
//#include <wpp.h>
#include <micro_component.h>
//#include "wpp_pins.h"
//#include "micro_threads.h"
//***************************************************************************************/                                                                                     */
//*     Wiring++ Threaded Component Example                                             */                                                                                     */
//***************************************************************************************/


//TODO Clean this up (main question is should inheritance from MICRO_Thread require 
// redeclaration of start and run? )
//
// but this is a working example of how an event based component will work.


 
//EXAMPLE THREAD ENABLED LIBRARY

    class  Button: MICRO_Thread {
        public: 
          MICRO_Event PRESSED;
		  Button(GpioPin p);
          Button(GpioPin p, int pUp);
          bool pressed();
          void micro_thread_run();
          void start();
          
         private:
		   bool pullUp;
           bool eventPressed;
		   bool pollPressed;
           GpioPin pin;
    };
    
	Button::Button(GpioPin p):MICRO_Thread(MICRO_NEVER_EVENT),pin(p){
         pin.setMode(INPUT);
		 pullUp = true;
		 pin.setPullup(HIGH);
         start();
    }

    Button::Button(GpioPin p, int pUp):MICRO_Thread(MICRO_NEVER_EVENT),pin(p){
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
    
    bool Button::pressed(){
      if(eventPressed && ! pollPressed){
		  pollPressed = true;
         return true;
      }
     else{
         return false; 
     }
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
      bool isDown;

      while(1){
		isDown = pullUp? (!pin.digitalRead()) : pin.digitalRead();
        if(isDown){
            if(!eventPressed){                
                broadcast(PRESSED);
                eventPressed = true;
            }
        }else{
          eventPressed = false;
		  pollPressed = false;
        }
       
       delay(100);
      }
    }
 
 
#define Button_Scope(instance) namespace MICRO_APPEND_ITEMS(instance,_NAMESPACE){\
 bool pressed(){return instance.pressed();}\
}

 
//**********************************************************************/
//*  END COMPONENT EXAMPLES                                            */
//**********************************************************************/
 
