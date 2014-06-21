//Robert Hayes
//TechSmartKids

#include <micro_component.h>
#include <Servo.h>

class MicroServo{
    public:
	MicroServo(GpioPwmPin p);
	void writeAngle(int a);
	int readAngle();
	bool isAttached();

    private:
	int angle;
	GpioPwmPin pin;
	Servo servo;
};

MicroServo::MicroServo(GpioPwmPin p):pin(p),angle(90){
	servo.attach(pin.getPin());
}


void MicroServo::writeAngle(int a){
    servo.write(a);
}

int MicroServo::readAngle(){
    return servo.read();
}

bool MicroServo::isAttached(){
    return servo.attached();
}