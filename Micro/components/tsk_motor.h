//authors: Robert Hayes
//2014 TechSmartKids LLC
//micro framework: Ed Baafi, (c) 2013 ModKit
//Motor Class

#ifndef TSKMOTOR_H
#define TSKMOTOR_H

#include <micro_component.h>

class TSKMotor{
	public:
		Motor(GpioPwmPin P1, GpioPwmPin P2);
		void cc(int speed);
		void c(int speed);
		void stop();
		void drive(int sSpeed);
	private:
		GpioPwmPin FPin;
		GpioPwmPin RPin;
};

TSKMotor::TSKMotor(GpioPwmPin P1, GpioPwmPin P2):FPin(P1),RPin(P2){
	FPin.setMode(OUTPUT).pwmWrite(0);
	RPin.setMode(OUTPUT).pwmWrite(0);
}

void TSKMotor::cc(int speed)
{
	
	constrain(speed,0,100);	
	RPin.pwmWrite(speed);
	FPin.pwmWrite(0);
	
}

void TSKMotor:: c(int speed)
{
	
	constrain(speed,0,100);
	RPin.pwmWrite(0);
	FPin.pwmWrite(speed);

}

void TSKMotor::stop(){
	FPin.pwmWrite(0);
	RPin.pwmWrite(0);
}

void TSKMotor::drive(int sSpeed){
	if(sSpeed<0){
		c(-1*sSpeed);
	}else{
		cc(sSpeed);
	}
}

#endif