#ifndef WIRING_PLUS_PLUS
#define WIRING_PLUS_PLUS

#include <micro_helper_macros.h>

#ifdef ARDUINO
    #include "wpp_pins_arduino.h"

	#define PIN0_SETUP 0
	typedef GpioPin PIN0_TYPE;

	#define PIN1_SETUP 1
	typedef GpioPin PIN1_TYPE;

	#define PIN2_SETUP 2
	typedef GpioPin PIN2_TYPE;

	#define PIN3_SETUP 3
	typedef GpioPwmPin PIN3_TYPE;

	#define PIN4_SETUP 4
	typedef GpioPin PIN4_TYPE;

	#define PIN5_SETUP 5
	typedef GpioPwmPin PIN5_TYPE;

	#define PIN6_SETUP 6
	typedef GpioPwmPin PIN6_TYPE;

	#define PIN7_SETUP 7
	typedef GpioPin PIN7_TYPE;

	#define PIN8_SETUP 8
	typedef GpioPin PIN8_TYPE;

	#define PIN9_SETUP 9
	typedef GpioPwmPin PIN9_TYPE;

	#define PIN10_SETUP 10
	typedef GpioPwmPin PIN10_TYPE;

	#define PIN11_SETUP 11
	typedef GpioPwmPin PIN11_TYPE;

	#define PIN12_SETUP 12
	typedef GpioPin PIN12_TYPE;

	#define PIN13_SETUP 13
	typedef GpioPin PIN13_TYPE;

	#define PIN14_SETUP 14
	typedef AdcGpioPin PIN14_TYPE;

	#define PIN15_SETUP 15
	typedef AdcGpioPin PIN15_TYPE;

	#define PIN16_SETUP 16
	typedef AdcGpioPin PIN16_TYPE;

	#define PIN17_SETUP 17
	typedef AdcGpioPin PIN17_TYPE;

	#define PIN18_SETUP 18
	typedef AdcGpioPin PIN18_TYPE;

	#define PIN19_SETUP 19
	typedef AdcGpioPin PIN19_TYPE;

	#define PIN20_SETUP 20
	typedef AdcGpioPin PIN20_TYPE;

	#define usePinAs(p,n) MICRO_PIN_TYPE_FROM_PIN(p) n  =  MICRO_PIN_TYPE_FROM_PIN(p)(MICRO_PIN_SETUP_FROM_PIN(p))
	#define usePin(p) MICRO_PIN_TYPE_FROM_PIN(p) p  =  MICRO_PIN_TYPE_FROM_PIN(p)(MICRO_PIN_SETUP_FROM_PIN(p))
	#define useAllPins() usePin(PIN8);usePin(PIN9);usePin(PIN10);usePin(PIN11);usePin(PIN12);usePin(PIN13);usePin(PIN14);usePin(PIN15);usePin(PIN16);usePin(PIN17);usePin(PIN18);usePin(PIN19);usePin(PIN20);


	useAllPins();


#else
    #include "wpp_pins.h"

#endif ARDUINO




#endif /* WIRING_PLUS_PLUS */


