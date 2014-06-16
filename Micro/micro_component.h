//author: Ed Baafi
//(c)2013 Modkit LLC
//#include <Arduino.h>
//#include <micro_helper_macros.h>

// threadsafe definition currently commented because it would override threadsafe in threads below
//#define threadsafe Threadsafe_is_not_safe_in_Components___Use_Instance_Variables 
#define COMPONENT_THREAD_SETUP if (getNextLabel()!=MICRO_START_LABEL){\
         goto *(getNextLabel());\
       } 

