//author: Ed Baafi
//(c)2014 Modkit LLC

#ifndef WPP_ANALOG
#define WPP_ANALOG
template <class analogValueClass>
class AnalogValue_5v 
{
	
public:
	float voltage() const{
	    return .05*((analogValueClass*)this)->percent();
	}
};

template <class analogValueClass>
class AnalogValue_10bit {
	
private:
	uint16_t rawVal;
public:
	AnalogValue_10bit(float percent):rawVal((percent/100.0)*1023){}
	uint16_t raw() const {
		return rawVal;
	}
	float percent() const{
		return 100*(rawVal/1023.0);
	}
	operator float () const
    {
		
        return percent();
    }
	
	
};


class AnalogValue_5v_10bit: public AnalogValue_10bit<AnalogValue_5v_10bit>,  public AnalogValue_5v <AnalogValue_5v_10bit>{
	
public:
	AnalogValue_5v_10bit(float percent):AnalogValue_10bit<AnalogValue_5v_10bit>(percent){}
	
};



#endif // WPP_ANALOG