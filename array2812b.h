#ifndef __NB_ARRAY2812B
#define __NB_ARRAY2812B

// This is max number of pixels possible, actual number of
// used pixels will be set in constructor
#define _NUM_PIXELS 64

#include "nworkbench.h"
#include "LED2812B/led2812b.h"

class nBlock_Array2812B: public nBlockSimpleNode<1> {
public:

    nBlock_Array2812B(PinName MOSI, uint32_t numberLEDs);
    void triggerInput(uint32_t inputNumber, uint32_t value);
	void endFrame();
	
   
private:

    // Declare array/buffer of type Pixel.
    Pixel pixels[_NUM_PIXELS];	
	//uint8_t  arrayValues[_NUM_PIXELS*3UL] =  { 0UL };
	
	
    // The pixel array control class.
    LED2812B _led_array;

	uint32_t num_leds;
	uint32_t must_update = 0;
};

#endif