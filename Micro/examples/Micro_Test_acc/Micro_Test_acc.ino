#include <wpp.h>
#include <micro.h>
#include <components/accelerometer.h>
#include <components/LED.h>

Accelerometer myacc = Accelerometer(PIN18, PIN19);
LED myled = LED(PIN9);

threads{
  thread(THREAD1){
     Serial.println("THREAD1 called");
     
     //pwmWrite takes percent ON as float (0.0-100.0) 
     
     myled.on();
     
     delay(1000);
     
     myled.off();
     
     delay(1000);
     
     /*
     PIN20.setMode(INPUT);
     //Analog object casts to float  (percent as 0.0-100.0) but has .raw() and .percent() methods
     Analog a= PIN20.analogRead();
     Serial.println(a);
     Serial.println(a.raw());
     Serial.println(a.percent());*/
  
  } 
}
events{
  when(START){
    Serial.println("STARTED!!!");
    THREAD1.start();  
  }
  when(myacc.SHAKENX){
    Serial.println("Oooooyyyeeaaaaah");
  }
  when(myacc.SHAKENY){
    Serial.println("Weeeeeeeee!");
  }
}
