#include <wpp.h>
#include <micro.h>
#include <components/button.h>
#include <components/light_sensor.h>
#include <components/LED.h>

Button button = Button(PIN19);
LightSensor light = LightSensor(PIN18);
LED myled = LED(PIN9);

threads{
  thread(THREAD1){
     Serial.println("THREAD1 called");
     
     //pwmWrite takes percent ON as float (0.0-100.0) 
     
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
  when(button.PRESSED){
    Serial.println("BUTTON PRESSED (BUILTIN)");
  }
  when(light.BRIGHTER){
    Serial.println("BRIGHTER");
    myled.setBrightness(myled.getBrightness()+10);
  }
  when(light.DARKER){
    Serial.println("DARKER");
    myled.setBrightness(myled.getBrightness()-10);
  }
  when(light.LIGHT){
    Serial.println("Press x to blind yourself.");
    myled.off();
  }
  when(light.DARK){
    Serial.println("It's Dark.  Use a torch.");
    myled.on();
  }
}






