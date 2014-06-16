//author: Ed Baafi
//(c)2013 Modkit LLC
#ifndef MICRO_THREADS
#define MICRO_THREADS
#include "micro_helper_macros.h"

/**********************************************************************/
/*                                                                    */
/*  THREADING DEFINES                                                 */
/*                                                                    */
/**********************************************************************/

 

//Event defs - currently hard coded to allow only 1024 user defined events 
enum MICRO_EVENT_ID {MICRO_NEVER_EVENT=1024, START, MICRO_BEGIN_AUTO_EVENTID};

//State defs
#define YIELD_STATE 0


#define MAX_EVENTS 10
#define MAX_THREADS 10

//thread states
#define MICRO_TRIGGERED 0
#define MICRO_DELAY_MICROS 1
#define MICRO_DELAY_MILLIS 2
#define MICRO_NOT_TRIGGERED 3


//start label - set to start label whenever done yielding
#define MICRO_START_LABEL 0


//**********************************************************************/
//*  END THREADING DEFINES                                             */
//**********************************************************************/
 
 
 
/**********************************************************************/
/*                                                                    */
/*  THREADING CLASSES                                                 */
/*                                                                    */
/**********************************************************************/

 
class MICRO_Event{
  public:
    MICRO_Event();
    int getEventID();
    void setEventID(int id);
    
  private:
    int eventID;
   
};  

//base class for threads
class MICRO_Thread{
  public:
    static MICRO_Thread *threadList[10];
    static int arrayTest[10];
    static int threadCount;
   
    //can't use default constructor or it will get called for every item in thread array and screw up our count
    MICRO_Thread(){}
    //using int is a hack to avoid this
    MICRO_Thread(int event){
          threadList[threadCount] = this;
          threadId=threadCount++;
          state = MICRO_NOT_TRIGGERED;
          eventId = event;
          delayLeft = 0;
          lastTime = 0;
          
        }
    MICRO_Thread(MICRO_Event event){
          threadList[threadCount] = this;
          threadId=threadCount++;
          state = MICRO_NOT_TRIGGERED;
          eventId = event.getEventID();
          delayLeft = 0;
          lastTime = 0;
          
        }

    void debug(){
      Serial.print("DEBUG from thread:");
      Serial.println(threadId);
    }
    
    void init(){
      Serial.print("Init for threadId: ");
      Serial.print(threadId);
      Serial.print(" and eventId: ");
      Serial.println(eventId);
      setNextLabel(MICRO_START_LABEL);
      if (eventId == START){
        triggerEvent(); 
      }
    }
     void setNextLabel(void *address){
      nextAddress = address;
    }
    
    void* getNextLabel(){
      return nextAddress;
    }
    //todo is there a max size?
    void doYield(void *address){
      nextAddress=address;
      state=YIELD_STATE;
    }
    void setEventId(int event){
       eventId=event; 
    }
    int getEventId(){
       return eventId; 
    }
    void triggerEvent(){
      // Serial.print("--> TRIGGERING: ");
      //Serial.println(eventId);
      state = MICRO_TRIGGERED;
    }
    void clearEvent(){
      //Serial.print("--> CLEARING: ");
      //Serial.println(eventId);
      state = MICRO_NOT_TRIGGERED;
    }
    bool isTriggered(){
      return (state == MICRO_TRIGGERED);
    }
    
    virtual void delayMillis(int milliseconds){
      
      lastTime = millis();
      state = MICRO_DELAY_MILLIS;
      delayLeft = milliseconds; 
    }
    
    virtual void delayMicros(int microseconds){
      lastTime = micros();
      state = MICRO_DELAY_MICROS;
      delayLeft = microseconds; 
    }
    
    void updateTime(){
     long currTime;
     if (state == MICRO_DELAY_MICROS) {
         currTime = micros();
      }
      else if (state == MICRO_DELAY_MILLIS){
         currTime = millis();
      }//NO DELAY - WHY ARE WE CALLING UPDATE TIME
      else {
        return;
      }
      //fix for overflow (long)
      //if(currTime<lastTime){
      //  lastTime -= 2147483647;
      // }
      //calc remaining delay
      delayLeft -=  currTime - lastTime;
      lastTime = currTime;
      
      if (delayLeft<=0){
         state = MICRO_TRIGGERED;
      }
    }
    
    virtual void micro_thread_run(){/*virtual base class - to implement*/}
     
  private:
    byte threadId;
    void * nextAddress;
    int eventId;
    //innefficient
    long lastTime;
    long delayLeft;
    byte state;
};

int  MICRO_Thread::threadCount = 0;
MICRO_Thread *MICRO_Thread::threadList[]= {0}; // static member definition   
    
    
    
  
class MICRO_ThreadManager{
  
  public:
    MICRO_ThreadManager();
    void debug();
    void init();
    void start();
    int getUniqueEventID();
    void  triggerEvent(int event);
    void  triggerEvent(MICRO_Event event);
  private:
    MICRO_Thread threads[MAX_THREADS];
    int currEventId;
    byte currThread;
};


MICRO_ThreadManager::MICRO_ThreadManager(){
      currThread = 0;
      //picks up where enum based auto event IDs (START etc) left off 
       currEventId=MICRO_BEGIN_AUTO_EVENTID;
}
    
    
void MICRO_ThreadManager::start(){   
	   init();
       Serial.print("looping through threads -- count: ");
       Serial.println(MICRO_Thread::threadCount);
       
       while(1){
          for (int i=0; i<MICRO_Thread::threadCount; i++){
             currThread = i;
             MICRO_Thread::threadList[i]->updateTime();
             if(MICRO_Thread::threadList[i]->isTriggered()){
				
                MICRO_Thread::threadList[i]->micro_thread_run(); 
				
                if (MICRO_Thread::threadList[i]->getNextLabel()==MICRO_START_LABEL){
                     //event fully executed so clear event so it can be triggered again
                     MICRO_Thread::threadList[i]->clearEvent();
                }
             }
           }
          
       }
     
}

/*
 * 
 */
void MICRO_ThreadManager::init(){    
       
       Serial.print("initializing threads -- count: ");
       Serial.println(MICRO_Thread::threadCount);
       
       for (int i=0; i<MICRO_Thread::threadCount; i++){
       
            currThread = i;
            MICRO_Thread::threadList[i]->init();
        }
}
 
/*
 * 
 */ 
int MICRO_ThreadManager::getUniqueEventID(){
    return currEventId++;   
}

/*
 * 
 */
void MICRO_ThreadManager::triggerEvent(int eventId){    
      
       for (int i=0; i<MICRO_Thread::threadCount; i++){
       
            if (MICRO_Thread::threadList[i]->getEventId()==eventId){
                 MICRO_Thread::threadList[i]->triggerEvent();
            }
        }
}
/*
 * 
 */
void MICRO_ThreadManager::triggerEvent(MICRO_Event event){    
      
       int eventId = event.getEventID();
       for (int i=0; i<MICRO_Thread::threadCount; i++){
       
            if (MICRO_Thread::threadList[i]->getEventId()==eventId){
                 MICRO_Thread::threadList[i]->triggerEvent();
            }
        }
}

void MICRO_ThreadManager::debug(){
    Serial.println("DEBUG!!!"); 
}
MICRO_ThreadManager Micro = MICRO_ThreadManager();



MICRO_Event::MICRO_Event(){
       setEventID(Micro.getUniqueEventID()); 
    }
int MICRO_Event::getEventID(){
      return eventID;
    }
void MICRO_Event::setEventID(int id){
      eventID=id;
    }


//**********************************************************************/
//*  END THREADING CLASSES                                             */
//**********************************************************************/
 
    
/***************************************************************************************/
/*                                                                                     */
/*     Wiring++ Threads -- User API Macros                                             */
/*                                                                                     */
/***************************************************************************************/

#define threadsafe static 
/*
 * "when" macro - triggers the statement or statement block below on the given event 
 */
 
#define when(event)\
    }\
    class  MICRO_THREAD_CLASS_FROM_LINE_NUM() : MICRO_Thread {\
        public: \
          MICRO_THREAD_CLASS_FROM_LINE_NUM()(int i):MICRO_Thread(i){}\
          MICRO_THREAD_CLASS_FROM_LINE_NUM()(MICRO_Event e):MICRO_Thread(e){}\
          void micro_thread_run();\
          void init();\
    };\
    MICRO_THREAD_CLASS_FROM_LINE_NUM() MICRO_THREAD_INSTANCE_FROM_LINE_NUM() = MICRO_THREAD_CLASS_FROM_LINE_NUM()(event);\
    void MICRO_THREAD_CLASS_FROM_LINE_NUM()::micro_thread_run(){\
       if (getNextLabel()!=MICRO_START_LABEL){\
         goto *(getNextLabel());\
       }\
    



/*
 * "thread" macro - triggers the statement or statement block below on the given event 
 * 
 */
/* 
#define thread(name)\
    }\
    class  MICRO_THREAD_CLASS_FROM_LINE_NUM() : MICRO_Thread {\
        public: \
          MICRO_THREAD_CLASS_FROM_LINE_NUM()(int i):MICRO_Thread(i){}\
          void micro_thread_run();\
          void start();\
    };\
    MICRO_THREAD_CLASS_FROM_LINE_NUM() name = MICRO_THREAD_CLASS_FROM_LINE_NUM()(MICRO_NEVER_EVENT);\
    void MICRO_THREAD_CLASS_FROM_LINE_NUM()::start(){\
       triggerEvent();\
    }\
    void MICRO_THREAD_CLASS_FROM_LINE_NUM()::micro_thread_run(){\
       if (getNextLabel()!=MICRO_START_LABEL){\
         goto *(getNextLabel());\
       }
*/

/*
 * "scoped thread" macro - same as thread except instance variables and methods are available in the thread's scope
 * 
 */
/* 
#define scopedThread(name,instance)\
    }\
    namespace MICRO_NAMESPACE_FROM_LINE_NUM{using namespace MICRO_APPEND_ITEMS(instance,_NAMESPACE);\
    class  MICRO_THREAD_CLASS_FROM_LINE_NUM() : MICRO_Thread {\
        public: \
          MICRO_THREAD_CLASS_FROM_LINE_NUM()(int i):MICRO_Thread(i){}\
          void micro_thread_run();\
          void start();\
    };}\
    MICRO_NAMESPACE_FROM_LINE_NUM::MICRO_THREAD_CLASS_FROM_LINE_NUM() name = MICRO_NAMESPACE_FROM_LINE_NUM::MICRO_THREAD_CLASS_FROM_LINE_NUM()(MICRO_NEVER_EVENT);\
    void MICRO_NAMESPACE_FROM_LINE_NUM::MICRO_THREAD_CLASS_FROM_LINE_NUM()::start(){\
       triggerEvent();\
    }\
    void MICRO_NAMESPACE_FROM_LINE_NUM::MICRO_THREAD_CLASS_FROM_LINE_NUM()::micro_thread_run(){\
       if (getNextLabel()!=MICRO_START_LABEL){\
         goto *(getNextLabel());\
       }
*/

#define events void events()
#define threads void threads()

#define thread(name)\
    }\
    namespace MICRO_NAMESPACE_FROM_LINE_NUM{\
    class  MICRO_THREAD_CLASS_FROM_LINE_NUM() : MICRO_Thread {\
        public: \
          MICRO_THREAD_CLASS_FROM_LINE_NUM()(int i):MICRO_Thread(i){}\
          void micro_thread_run();\
          void start();\
    };}\
    MICRO_NAMESPACE_FROM_LINE_NUM::MICRO_THREAD_CLASS_FROM_LINE_NUM() name = MICRO_NAMESPACE_FROM_LINE_NUM::MICRO_THREAD_CLASS_FROM_LINE_NUM()(MICRO_NEVER_EVENT);\
    void MICRO_NAMESPACE_FROM_LINE_NUM::MICRO_THREAD_CLASS_FROM_LINE_NUM()::start(){\
       triggerEvent();\
    }\
    void MICRO_NAMESPACE_FROM_LINE_NUM::MICRO_THREAD_CLASS_FROM_LINE_NUM()::micro_thread_run(){\
       if (getNextLabel()!=MICRO_START_LABEL){\
         goto *(getNextLabel());\
       }\
       
       
#define with(instance) using namespace MICRO_APPEND_ITEMS(instance,_NAMESPACE);
       
#define Scope(instance,component) MICRO_APPEND_ITEMS(component,_Scope)(instance)
 

      
 /*
 * "yield" macro - makes a label and sets next address to it.  
 *  after flow is returned, address is set to 0 since we're not loopung on label
 */
        
#define yield() \
  setNextLabel(&& MICRO_GOTO_LABEL());\
  return;\
  MICRO_GOTO_LABEL():\
      setNextLabel(MICRO_START_LABEL);\
      
/*
 * "broadcast" macro - calls event handler's trigger method for given eventId  
 */
        
#define broadcast(event) Micro.triggerEvent(event)


/*
 * "delay" macro - calls delayMillis
 * note - any delays above this would be arduino delays
 */
        
#define delay(time) delayMillis(time);\
   setNextLabel(&& MICRO_GOTO_LABEL());\
    return;\
   MICRO_GOTO_LABEL():\
      setNextLabel(MICRO_START_LABEL);\
      
/*
 * "delay" macro - calls delayMillis
 * note - any delays above this would be arduino delays
 */

#define delayMicroseconds(time) delayMicros(time);\
   setNextLabel(&& MICRO_GOTO_LABEL());\
    return;\
   MICRO_GOTO_LABEL():\
      setNextLabel(MICRO_START_LABEL);\

/*
 * "start" macro - calls threadmanager.start()
 * note - eventually start  will be called for us from behind the scenes (main)
 */
//#define micro_threads_startup() Micro.init();Micro.start();

#define EventList enum
//**********************************************************************/
//*  END THREADING API                                                 */
//**********************************************************************/
 
#endif // ifndef MICRO_THREADS





 
 
