//Robert Hayes
//TechSmartKids

#include <micro_component.h>
#include <Servo.h>

class ContinuousServo{
    public:
	ContinuousServo(GpioPwmPin p);
	void writeClockwise(int speed);
	void writeCC(int speed);
	void stop();
	int readAngle();
	bool isAttached();

    private:
	const int stopVal;
	GpioPwmPin pin;
	Servo servo;
};

ContinuousServo::ContinuousServo(GpioPwmPin p):pin(p),stopVal(95){
	servo.attach(pin.getPin()); 
}

void ContinuousServo::writeClockwise(int speed){
	servo.write(map(speed,0,100,stopVal,180));
}

void ContinuousServo::writeCC(int speed){
	servo.write(map(speed,0,100,stopVal,0));
}

void ContinuousServo::stop(){
	servo.write(stopVal);
}

int ContinuousServo::readAngle(){
    return servo.read();
}

bool ContinuousServo::isAttached(){
    return servo.attached();
}