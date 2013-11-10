#include "VWWLCD.h"
#include <Arduino.h>

VWWLCD::VWWLCD(){

  /** Documentation from u8g->h
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

  this->draw_state = 0;
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

/*void VWWLCD::draw(){

    // graphic commands to redraw the complete screen should be placed here  
  u8g->setFont(u8g_font_unifont);
  //u8g->setFont(u8g_font_osb21);
  u8g->drawStr( 0, 22, "Hello World!");
}
*/


void VWWLCD::drawString(String string){
  char charBuf[string.length()];
  string.toCharArray(charBuf, string.length());
  u8g->drawStr(0, 22, charBuf);
}

void VWWLCD::drawStringFromDigit(unsigned int digit){
  switch(digit){
    case 0:
    break;
    case 1:{
      u8g->drawStr(0, 22, "Subscription :D");
      break;
    }
    case 2:{
      u8g->drawStr(0, 22, "Subscription renewal :)");
      break;
    }
    case 3:
    u8g->drawStr(0, 22, "Cancellation... DOH! :(");
      break;
      default:
      break;

    }
  }

  void VWWLCD::drawCycle(){
/*    // picture loop
    u8g->firstPage();  
    do {
      draw();
    } while( u8g->nextPage() );*/
  // picture loop  

  u8g->firstPage();  
  do {
    draw();
  } while( u8g->nextPage() );
  
  // increase the state
  draw_state++;
  if ( draw_state >= 8*8 )
    draw_state = 0;
  
  // rebuild the picture after some delay
    delay(50);
  }








  void VWWLCD::u8g_prepare(void) {
    u8g->setFont(u8g_font_6x10);
    u8g->setFontRefHeightExtendedText();
    u8g->setDefaultForegroundColor();
    u8g->setFontPosTop();
  }

  void VWWLCD::u8g_box_frame(uint8_t a) {
    u8g->drawStr( 0, 0, "VWW drawBox");
    u8g->drawBox(5,10,20,10);
    u8g->drawBox(10+a,15,30,7);
    u8g->drawStr( 0, 30, "drawFrame");
    u8g->drawFrame(5,10+30,20,10);
    u8g->drawFrame(10+a,15+30,30,7);
  }

  void VWWLCD::u8g_disc_circle(uint8_t a) {
    u8g->drawStr( 0, 0, "VWW drawDisc");
    u8g->drawDisc(10,18,9);
    u8g->drawDisc(24+a,16,7);
    u8g->drawStr( 0, 30, "VWW drawCircle");
    u8g->drawCircle(10,18+30,9);
    u8g->drawCircle(24+a,16+30,7);
  }

  void VWWLCD::u8g_r_frame(uint8_t a) {
    u8g->drawStr( 0, 0, "VWW drawRFrame/Box");
    u8g->drawRFrame(5, 10,40,30, a+1);
    u8g->drawRBox(50, 10,25,40, a+1);
  }

  void VWWLCD::u8g_string(uint8_t a) {
    u8g->drawStr(30+a,31, " 0");
    u8g->drawStr90(30,31+a, " 90");
    u8g->drawStr180(30-a,31, " 180");
    u8g->drawStr270(30,31-a, " 270");
  }

  void VWWLCD::u8g_line(uint8_t a) {
    u8g->drawStr( 0, 0, "VWW drawLine");
    u8g->drawLine(7+a, 10, 40, 55);
    u8g->drawLine(7+a*2, 10, 60, 55);
    u8g->drawLine(7+a*3, 10, 80, 55);
    u8g->drawLine(7+a*4, 10, 100, 55);
  }

  void VWWLCD::u8g_ascii_1() {
    char s[2] = " ";
    uint8_t x, y;
    u8g->drawStr( 0, 0, "VWW ASCII page 1");
    for( y = 0; y < 6; y++ ) {
      for( x = 0; x < 16; x++ ) {
        s[0] = y*16 + x + 32;
        u8g->drawStr(x*7, y*10+10, s);
      }
    }
  }

  void VWWLCD::u8g_ascii_2() {
    char s[2] = " ";
    uint8_t x, y;
    u8g->drawStr( 0, 0, "VWW ASCII page 2");
    for( y = 0; y < 6; y++ ) {
      for( x = 0; x < 16; x++ ) {
        s[0] = y*16 + x + 160;
        u8g->drawStr(x*7, y*10+10, s);
      }
    }
  }

  void VWWLCD::u8g_extra_page(uint8_t a)
  {
    if ( u8g->getMode() == U8G_MODE_HICOLOR || u8g->getMode() == U8G_MODE_R3G3B2) {
    /* draw background (area is 128x128) */
      u8g_uint_t r, g, b;
      b = a << 5;
      for( g = 0; g < 64; g++ )
      {
        for( r = 0; r < 64; r++ )
        {
         u8g->setRGB(r<<2, g<<2, b );
         u8g->drawPixel(g, r);
       }
     }
     u8g->setRGB(255,255,255);
     u8g->drawStr( 66, 0, "VWW Color Page");
   }
   else if ( u8g->getMode() == U8G_MODE_GRAY2BIT )
   {
    u8g->drawStr( 66, 0, "VWW Gray Level");
    u8g->setColorIndex(1);
    u8g->drawBox(0, 4, 64, 32);    
    u8g->drawBox(70, 20, 4, 12);
    u8g->setColorIndex(2);
    u8g->drawBox(0+1*a, 4+1*a, 64-2*a, 32-2*a);
    u8g->drawBox(74, 20, 4, 12);
    u8g->setColorIndex(3);
    u8g->drawBox(0+2*a, 4+2*a, 64-4*a, 32-4*a);
    u8g->drawBox(78, 20, 4, 12);

  }
  else
  {
    u8g->drawStr( 0, 12, "VWW setScale2x2");
    u8g->setScale2x2();
    u8g->drawStr( 0, 6+a, "VWW setScale2x2");
    u8g->undoScale();
  }
}




void VWWLCD::draw(void) {
  u8g_prepare();
  switch(draw_state >> 3) {
    case 0: u8g_box_frame(draw_state&7); break;
    case 1: u8g_disc_circle(draw_state&7); break;
    case 2: u8g_r_frame(draw_state&7); break;
    case 3: u8g_string(draw_state&7); break;
    case 4: u8g_line(draw_state&7); break;
    case 5: u8g_ascii_1(); break;
    case 6: u8g_ascii_2(); break;
    case 7: u8g_extra_page(draw_state&7); break;
  }
}
