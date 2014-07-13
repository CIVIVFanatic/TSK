//authors: Robert Hayes
//2014 TechSmartKids LLC
//micro framework: Ed Baafi, (c) 2013 ModKit
//Motor Class

#ifndef MOTOR_H
#define MOTOR_H

#include <micro_component.h>

class Motor{
public:
  Motor(GpioPwmPin P1, GpioPwmPin P2);
  void forward(int speed);
  void reverse(int speed);
  void drive(int sSpeed);
private:
  GpioPwmPin FPin;
  GpioPwmPin RPin;
};

Motor::Motor(GpioPwmPin P1, GpioPwmPin P2):FPin(P1),RPin(P2){
  FPin.setMode(OUTPUT).pwmWrite(0);
  RPin.setMode(OUTPUT).pwmWrite(0);
}

void Motor::forward(int speed){
  if(speed<0){
	  speed = 0;
  }else if(speed>100){
	  speed = 100;
  }
  RPin.pwmWrite(0);
  FPin.pwmWrite(speed);
}

void Motor::reverse(int speed){
  if(speed<0){
	  speed = 0;
  }else if(speed>100){
	  speed = 100;
  }
  FPin.pwmWrite(0);
  RPin.pwmWrite(speed);
}

void Motor::drive(int sSpeed){
  if(sSpeed>=0){
	  forward(sSpeed);
  }else{
	  reverse(sSpeed);
  }
}

#endif

    
