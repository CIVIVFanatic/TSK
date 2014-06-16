//author: Ed Baafi
//(c)2014 Modkit LLC
#ifndef WPP_PINS
#define WPP_PINS

#include "Arduino.h"
#include "wpp_analog.h"
#include "wpp_pwm.h"

//This will be defined for each microcontroller to represent the native Analog values on the system along with the VCC value.
//On systems with more than one "native" analog resolution (e.g. micro with ADC+DAC) the best resolution is considered native
//And of course we'd get automatic conversion between resolutions
#define WPP_ANALOG_BIT_RESOLUTION 10
#define WPP_SYSTEM_VOLTAGE 5
typedef AnalogValue_5v_10bit Analog;


#define WPP_PWM_BIT_RESOLUTION 8
typedef PWMValue_8bit PWM;


/*
 *  Lower Level Pin objects:
 *    These are not exposed to the user or compoenent developers but are necessary for 
 *    method chaining to return appropriate class (derived class not base)
 */

inline void _setPullup(uint8_t pin, uint8_t val){
	digitalWrite(pin,val);
}
inline void _digitalWrite(uint8_t pin, uint8_t val){
	digitalWrite(pin,val);
}
inline void _pwmWrite(uint8_t pin, uint8_t val){
	analogWrite(pin,val);
}

inline uint8_t _digitalRead(uint8_t pin){
	return digitalRead(pin);	
}

inline uint16_t _analogRead(uint8_t pin){
	return analogRead(pin);	
}

template <class pinClass>
class wpp_digital_io_pin{
  public:
	wpp_digital_io_pin(uint8_t pin):digital_pin_num(pin){};
      pinClass& digitalWrite(uint8_t value){
         _digitalWrite(digital_pin_num, value); 
		 return *(pinClass*)this;
      }
      pinClass& setMode(uint8_t mode){
         pinMode(digital_pin_num, mode); 
         return *(pinClass*)this;
      }
	  pinClass& setPullup(uint8_t val){
		_setPullup(digital_pin_num, val); 
		return *(pinClass*)this;
	  }
	  uint8_t digitalRead(){
		return _digitalRead(digital_pin_num); 
	  }
	
	
     
  private:
      uint8_t digital_pin_num;
  
};


template <class pinClass>
class wpp_pwm_pin{
  
  public:
      wpp_pwm_pin(uint8_t pin):digital_pin_num(pin){}
      
      pinClass& pwmWrite(PWM value){
         _pwmWrite(digital_pin_num, value.raw()); 
         return *(pinClass*)this;
      }
      private:
         uint8_t digital_pin_num;
      
};

template <class pinClass>
class wpp_analog_in_pin{
  public:
      
      wpp_analog_in_pin(uint8_t pin):analog_in_pin_num(pin){};
      Analog analogRead(){
		  //((2<<(WPP_ANALOG_BIT_RESOLUTION-1))-1.0) -> 1023 for 10bit ADC Resolution
         return Analog((_analogRead(analog_in_pin_num)/   ((2<<(WPP_ANALOG_BIT_RESOLUTION-1))-1.0) )*100.0) ; 
      }  
     
  private:
      uint8_t analog_in_pin_num;
  
};

//GpioPin

//DigitalIO_AnalogIN_Pin

/*
 * User Level Pin Interfaces:
 *   These are what library/component authors specify when taking a Pin parameter
 *
 * Format: PinAbcXyz where Abc and Xyz are shortcuts for pin functionality
 *   Dio = Digital I/O,  Ain = Analog In,  Pwm = Pulse Width Modulation
 *
 * Usage: A component author will specify the minimal Pin interface 
 *    E.g. GpioPin which allows the user to pass in GpioPin, GpioPwmPin, GpioAdcPin etc 
 *
 * Implementation: 
 *   For single functionality User Pins, we just inherit from the actual functionality
 *     E.g. class GpioPin:  public wpp_digital_io_pin<GpioPin>;
 *   For multiple functionality we inherit actual functionality and inherit associated User Pin Class from each.
 *        E.g. class GpioPwmPin: public GpioPin,public PwmPin, public wpp_digital_io_pin<GpioPwmPin>,public wpp_pwm_pin<GpioPwmPin>;
 *     Then we have to specify that we prefer actual functionality
 *        E.g.  using wpp_digital_io_pin<GpioPwmPin>::digitalWrite_;
 *              using wpp_digital_io_pin<GpioPwmPin>::pinMode_;
 *     This allows a Pin to be instantiated with all of its functionality where method chaining will return class with all functionality, 
 *     yet passing it into a component with less functionality only pigeonholes the pin in that context  (where the pigeonholed functionailty is enough).  
 */


class GpioPin:  public wpp_digital_io_pin<GpioPin>{
  
  public:
      GpioPin(uint8_t pin):wpp_digital_io_pin<GpioPin>(pin){
        
      }
};

class AdcPin: public wpp_analog_in_pin<AdcPin>{
  
  public:
      AdcPin(uint8_t pin):wpp_analog_in_pin<AdcPin>(pin){
        
      }
};

class PwmPin: public wpp_pwm_pin<PwmPin>{
  
  public:
      PwmPin(uint8_t pin):wpp_pwm_pin<PwmPin>(pin){
        
      }
};

class AdcGpioPin: public AdcPin,public GpioPin, public wpp_analog_in_pin<AdcGpioPin>, public wpp_digital_io_pin<AdcGpioPin>{
  
  public:
      AdcGpioPin(uint8_t pin):AdcPin(pin),GpioPin(pin),wpp_analog_in_pin<AdcGpioPin>(pin),wpp_digital_io_pin<AdcGpioPin>(pin){
        
      }
      using wpp_analog_in_pin<AdcGpioPin>::analogRead;
	  using wpp_digital_io_pin<AdcGpioPin>::setPullup;
      using wpp_digital_io_pin<AdcGpioPin>::digitalWrite;
	  using wpp_digital_io_pin<AdcGpioPin>::digitalRead;
      using wpp_digital_io_pin<AdcGpioPin>::setMode;
};
class GpioPwmPin: public GpioPin,public PwmPin, public wpp_digital_io_pin<GpioPwmPin>,public wpp_pwm_pin<GpioPwmPin>{
  
  public:
      GpioPwmPin(uint8_t pin): GpioPin(pin), PwmPin(pin),wpp_digital_io_pin<GpioPwmPin>(pin),wpp_pwm_pin<GpioPwmPin>(pin){
        
      }
      using wpp_pwm_pin<GpioPwmPin>::pwmWrite;
	  using wpp_digital_io_pin<GpioPwmPin>::setPullup;
      using wpp_digital_io_pin<GpioPwmPin>::digitalWrite;
	  using wpp_digital_io_pin<GpioPwmPin>::digitalRead;
      using wpp_digital_io_pin<GpioPwmPin>::setMode;
};


#endif // #ifndef WPP_PINS





