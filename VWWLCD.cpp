#include "VWWLCD.h"
#include <Arduino.h>

const uint8_t screenHeight = 64;
const uint8_t screenWidth = 128;
    
const uint8_t graphHeight = 50;
const uint8_t graphWidth = 128;

VWWLCD::VWWLCD(){

  /** Documentation from u8g->h
  // we are using a 128x64 display
  class U8GLIB_ST7920_128X64 : public U8GLIB
  {
    public:
      U8GLIB_ST7920_128X64(uint8_t sck, uint8_t mosi, uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE)
        : U8GLIB(&u8g_dev_st7920_128x64_sw_spi, sck, mosi, cs, a0, reset)
        { }
      U8GLIB_ST7920_128X64(uint8_t cs, uint8_t a0, uint8_t reset = U8G_PIN_NONE)
        : U8GLIB(&u8g_dev_st7920_128x64_hw_spi, cs, a0, reset)
        { }
      U8GLIB_ST7920_128X64(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
          uint8_t en, uint8_t cs1, uint8_t cs2, uint8_t di, uint8_t rw = U8G_PIN_NONE, uint8_t reset = U8G_PIN_NONE)
        : U8GLIB(&u8g_dev_st7920_128x64_8bit, d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, cs2, di, rw, reset)
        { }
      // U8GLIB_ST7920_128X64(uint8_t cs) 
      //   : U8GLIB(&u8g_dev_st7920_128x64_sw_spi, cs, U8G_PIN_NONE, U8G_PIN_NONE)
      //   { }
  };
  */


  u8g = new U8GLIB_ST7920_128X64(13, 11, 12, U8G_PIN_NONE);
  
  // flip screen, if required
  // u8g->setRot180();
  
  // set SPI backup if required
  //u8g->setHardwareBackup(u8g_backup_avr_spi);

  // assign default color value
  if ( u8g->getMode() == U8G_MODE_R3G3B2 ) {
    u8g->setColorIndex(255);     // white
  }
  else if ( u8g->getMode() == U8G_MODE_GRAY2BIT ) {
    u8g->setColorIndex(3);         // max intensity
  }
  else if ( u8g->getMode() == U8G_MODE_BW ) {
    u8g->setColorIndex(1);         // pixel on
  }
  else if ( u8g->getMode() == U8G_MODE_HICOLOR ) {
    u8g->setHiColorByRGB(255,255,255);
  }
}




  void VWWLCD::u8g_prepare(void) {
    u8g->setFont(u8g_font_6x10);
    u8g->setFontRefHeightExtendedText();
    u8g->setDefaultForegroundColor();
    u8g->setFontPosTop();
  }

 

void VWWLCD::u8g_barGraphFromSales(char* title, uint8_t *subSales, uint8_t size) {

  const uint8_t dayWidth = graphWidth / (float)size;
  const uint8_t dayXSpacing = 1;

  uint8_t max = 0;
  uint8_t maxIndex = 0;
  uint8_t min = 255;
  uint8_t minIndex = 0;

  for(uint8_t saleIndex = 0; saleIndex < size; saleIndex++){
    if(subSales[saleIndex] > max){
      max = subSales[saleIndex];
      maxIndex = saleIndex;
    }    

    if(subSales[saleIndex] < min){
      min = subSales[saleIndex];
      minIndex = saleIndex;
    }
  }

  const float saleHeight = graphHeight / (float)max;

  char str[128] = "";
  sprintf(str, "%s: max=%d min=%d", title, max, min);


  u8g->drawStr( 0, 0, str);
    uint8_t graphYOffset = (screenHeight - graphHeight);
    for(uint8_t day = 0; day < 30; day++){
      uint8_t x = 0, y = 0, w = 0, h = 0;
      x = day * dayWidth;
      y = graphYOffset + graphHeight - (subSales[day] * saleHeight);
      w = dayWidth;
      h = graphYOffset + graphHeight - y;
      u8g->drawFrame(x, y, w, h);
    }
  }




  void VWWLCD::drawCycle(){

    u8g->firstPage();  
    do {
      draw();
    } while( u8g->nextPage() );

    delay(250);
  }

// 128x64
void VWWLCD::draw(void) {
  u8g_prepare();

  // TODO: Parse incoming text and then pass to method
  // uint8_t subSales[30] = {1, 2, 20 ,50, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  uint8_t subSales[30] = {1, 2, 20 , 10, 5, 6, 7, 8, 9, 10};
  u8g_barGraphFromSales("Sales", subSales, 10);
  
}






