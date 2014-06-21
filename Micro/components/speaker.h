//authors: Ed Baafi, Robert Hayes
//(c)2013 Modkit LLC

#include <micro_component.h>

class Speaker{
    public:
	//Speaker(GpioPwmPin p):pin(p){};
	Speaker(GpioPwmPin p):pin(p){};
	void playNote(int note);
	void playNote(int note, int duration);
	void stop();
	//playMelody();
    private:
        //GpioPwmPin pin;
	GpioPwmPin pin;
};

void Speaker::playNote(int note){
    tone(pin.getPin(),note);
}

void Speaker::playNote(int note, int duration){
    tone(pin.getPin(),note,duration);
}

void Speaker::stop(){
    noTone(pin.getPin());
}