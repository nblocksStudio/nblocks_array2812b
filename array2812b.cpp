#include "array2812b.h"



nBlock_Array2812B::nBlock_Array2812B(PinName MOSI, uint32_t numberLEDs):
	_led_array(MOSI) {
	
	// Number of LEDs to be used
	num_leds = numberLEDs;
	
	// Reset flag
	must_update = 0;	
	
}


void nBlock_Array2812B::triggerInput(uint32_t inputNumber, uint32_t value){
	// input 0 receives an array of bytes
	if (inputNumber == 0) {
		// Copy values to internal array
		uint8_t * source_values;
		source_values = ((uint8_t *)value);
		for (uint32_t i = 0; i < num_leds; i++) {
			pixels[i].red   = source_values[i*3];
			pixels[i].green = source_values[(i*3) + 1];
			pixels[i].blue  = source_values[(i*3) + 2];
		}
		// Set flag so we update the LEDs at the end of frame
		must_update =  1;
	}
}

void nBlock_Array2812B::endFrame(void){

	if (must_update) {
		must_update = 0;
		_led_array.update(pixels, _NUM_PIXELS);
	}
	
	
}


