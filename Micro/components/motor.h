//authors: Robert Hayes
//2014 TechSmartKids LLC
//micro framework: Ed Baafi, (c) 2013 ModKit
//Motor Class

#ifndef MOTOR_H
#define MOTOR_H

#include <micro_component.h>

class Motor{
	public:
		Motor(GpioPwmPin P1);
		void stop();
		void drive(int speed);
		void drive();
		void setSpeed(int speed);

	private:
		GpioPwmPin Pin;
		int vel;
};

Motor::Motor(GpioPwmPin P1):Pin(P1),vel(100){
	Pin.setMode(OUTPUT).pwmWrite(0);
}

void Motor::stop(){
	Pin.pwmWrite(0);
}

void Motor::drive(int speed){
	Pin.pwmWrite(speed);
}

void Motor::drive()
{
	drive(vel);
}

void Motor::setSpeed(int speed)
{
	vel = speed;
}

#endif