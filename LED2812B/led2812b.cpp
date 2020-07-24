#include "led2812b.h"

/* 
	This library is modified (reduced) version of PixelArray
  (https://os.mbed.com/users/JacobBramley/code/PixelArray/)
*/

LED2812B::LED2812B(PinName pinMOSI): _spi(pinMOSI, NC, NC) {
	//  '0': 100             mark: 0.42us, space: 0.83us
	//  '1': 110             mark: 0.83us, space: 0.42us
	_spi.frequency(2400000);  // 800kHz * 3
	_spi.format(12);          // Send four NeoPixel bits in each packet.
}

static void SendFourBits(SPI& spi, uint32_t bits)
{
    // Encode '0' bits as 100 and '1' bits as 110.
    // We have this bit pattern: 00000000abcd
    // We want this bit pattern: 1a01b01c01d0
    uint32_t ac = (bits * 0x088) &        // 0abcdabcd000
                  0x410; // 0a00000c0000

    uint32_t bd = (bits * 0x022) &        // 000abcdabcd0
                  0x082; // 0000b00000d0

    static uint32_t const base = 04444;   // 100100100100

    spi.write(base | ac | bd);        // 1a01b01c01d0
}

void LED2812B::send_pixel(Pixel& pixel)
{
    // Pixels are sent as follows:
    // - The first transmitted pixel is the pixel closest to the transmitter.
    // - The most significant bit is always sent first.
    //
    // g7,g6,g5,g4,g3,g2,g1,g0,r7,r6,r5,r4,r3,r2,r1,r0,b7,b6,b5,b4,b3,b2,b1,b0
    // \_____________________________________________________________________/
    //                           |      _________________...
    //                           |     /   __________________...
    //                           |    /   /   ___________________...
    //                           |   /   /   /
    //                          GRB,GRB,GRB,GRB,...
    //

	SendFourBits(_spi, (pixel.green >> 4) & 0xf);
	SendFourBits(_spi, (pixel.green >> 0) & 0xf);
	SendFourBits(_spi, (pixel.red   >> 4) & 0xf);
	SendFourBits(_spi, (pixel.red   >> 0) & 0xf);
	SendFourBits(_spi, (pixel.blue  >> 4) & 0xf);
	SendFourBits(_spi, (pixel.blue  >> 0) & 0xf);
}

void LED2812B::update(Pixel buffer[], uint32_t length)
{
    // Manually set the color fields of the four pixels in the pixel buffer.
    
    // Loop through and send each pixel to the NeoPixel.
    for (uint32_t i = 0; i < length; i++) {
        
        send_pixel(buffer[i]);
    }

    wait_us(latch_time_us_);
}