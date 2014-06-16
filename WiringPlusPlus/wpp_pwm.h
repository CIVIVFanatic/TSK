//author: Ed Baafi
//(c)2014 Modkit LLC

#ifndef WPP_PWM
#define WPP_PWM


class PWMValue_8bit {
	
private:
	uint16_t rawVal;
public:
	PWMValue_8bit(float percent):rawVal((percent/100.0)*255){}
	uint16_t raw() const {
		return rawVal;
	}
	float percent() const{
		return 100*(rawVal/255.0);
	}
	operator float () const
    {
		
        return percent();
    }
};


#endif // WPP_PWM