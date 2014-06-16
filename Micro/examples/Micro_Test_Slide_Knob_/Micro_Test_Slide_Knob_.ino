#include <wpp.h>
#include <micro.h>
#include <components/lin_pot.h>
#include <components/rot_pot.h>
#include <components/LED.h>

LinPot slider = LinPot(PIN19);
RotPot knob = RotPot(PIN18);
LED myled = LED(PIN9);

threads{
  thread(THREAD1){
     Serial.println("THREAD1 called");
     
     myled.on();
     
     delay(1000);
     
     myled.off();
     
     delay(2000);
     
     myled.on();
    
     PIN10.setMode(OUTPUT).digitalWrite(HIGH);
     
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
  when(slider.MOVED){
    Serial.println("SLIDER MOVED");
    myled.setBrightness(myled.getBrightness()+10);
  }
  when(knob.TURNED){
    Serial.println("TURNED");
  }
  when(knob.TURNED_CLOCKWISE){
    Serial.println("Red Pill");
    myled.on();
  }
  when(knob.TURNED_COUNTERCLOCKWISE){
    Serial.println("Blue Pill");
    myled.off();
  }
}






