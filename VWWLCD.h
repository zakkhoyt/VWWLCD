#ifndef WS_LCD_H
#define WS_LCD_H

#include <U8glib.h>

class VWWLCD{
private: 
	U8GLIB_ST7920_128X64 *u8g;


	void u8g_prepare(void);
	void u8g_barGraphFromSales(char* title, uint8_t *subSales, uint8_t size);

public:
	VWWLCD();

	void drawCycle();
	void draw(void); 

};

#endif // WS_LCD_H

