//authors: Ed Baafi, Robert Hayes
//(c)2013 Modkit LLC

#include <micro_component.h>

class Speaker{
    public:
	//Speaker(GpioPwmPin p):pin(p){};
	Speaker(int p):pin(p){};
	void playNote(int note);
	void playNote(int note, int duration);
	void stop();
	//playMelody();
    private:
        //GpioPwmPin pin;
	int pin;
};

void Speaker::playNote(int note){
    tone(pin,note);
}

void Speaker::playNote(int note, int duration){
    tone(pin,note,duration);
}

void Speaker::stop(){
    noTone(pin);
}