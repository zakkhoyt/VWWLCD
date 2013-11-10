
#include <U8glib.h>
#include "VWWLCD.h"
//U8GLIB_ST7920_128X64 u8g(13, 11, 12, U8G_PIN_NONE);

VWWLCD *u8g;

void setup(void) {

  Serial.begin(9600);
  
  // flip screen, if required
  //u8g.setRot180();
  u8g = new VWWLCD();
  pinMode(13, OUTPUT);           
  digitalWrite(13, HIGH);  
}

void loop(void) {
  
  // picture loop  
  // u8g.firstPage();  
  // do {
  //   draw();
  // } while( u8g.nextPage() );
  
  // // increase the state
  // draw_state++;
  // if ( draw_state >= 8*8 )
  //   draw_state = 0;
  
  // // rebuild the picture after some delay
  // delay(150);
  u8g->drawCycle();

}


