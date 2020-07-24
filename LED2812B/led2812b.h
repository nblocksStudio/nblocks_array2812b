#ifndef __LED2812B
#define __LED2812B

#include "mbed.h"

/* 
	This library is modified (reduced) version of PixelArray
  (https://os.mbed.com/users/JacobBramley/code/PixelArray/)
*/

struct Pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

class LED2812B {
public:
	LED2812B(PinName pinMOSI);
	void update(Pixel buffer[], uint32_t length);
	
private:
	SPI _spi;
	
	static int const latch_time_us_ = 50;
	
	void send_pixel(Pixel& pixel);
};




#endif