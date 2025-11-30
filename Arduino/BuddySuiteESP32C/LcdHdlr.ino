//30Nov2025
void LcdHdlr::setup()
{
	tft.init(240, 320);
	showStartupSplash();
}  //2.0" 320x240 ST7789 TFT}

void LcdHdlr::showStartupSplash()
{
		drawBitMap(tft);//2 secdelay built in		
}
#include <./Pics/splash1.h>
void LcdHdlr::drawBitMap(Adafruit_ST7789 tft)
	{
				tft.fillScreen(ST77XX_BLACK);
				tft.setRotation(1);
				tft.drawRGBBitmap(0, 0, splash1, 320,240);
				delay (2000);
				
				//tft.fillScreen(ST77XX_BLACK);
				//tft.drawRGBBitmap(0, 0, bitmap_DestinyVideo320_170, 320,170);
				//delay (10000);
				tft.fillScreen(ST77XX_BLACK);
			   //tft.drawRGBBitmap(0, 0, lcd_gs850, 320,215);
				/**Many more drawbitmap functs in Adafruit_gfx.h
				void drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[], int16_t w, int16_t h);
				void drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h);
				void drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[], const uint8_t mask[], int16_t w, int16_t h);
				void drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, uint8_t *mask, int16_t w, int16_t h);
				*/
	}
