#ifndef WS_LCD_H
#define WS_LCD_H

#include <U8glib.h>

class VWWLCD{
private: 
	U8GLIB_ST7920_128X64 *u8g;
	uint8_t draw_state;

	void u8g_prepare(void);
	void u8g_box_frame(uint8_t a);
	void u8g_disc_circle(uint8_t a);
	void u8g_r_frame(uint8_t a);
	void u8g_string(uint8_t a);
	void u8g_line(uint8_t a);
	void u8g_ascii_1();
	void u8g_ascii_2();
	void u8g_extra_page(uint8_t a);


public:
	VWWLCD();

	void drawString(String string);
	void drawStringFromDigit(unsigned int digit);
	void drawCycle();

	void draw(void); 

};

#endif // WS_LCD_H

