//5Dec2025
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


void LcdHdlr::setJoystickMeter(const int & rawXPos)
{
	int xPosMapped = 0;
	if (!(rawXPos < joystickCentreXRaw-250)  && !(rawXPos >joystickCentreXRaw+250))
		{
			xPosMapped=13;		//centre
  	}
	else if(rawXPos>joystickCentreXRaw) {xPosMapped = map(rawXPos,    joystickCentreXRaw, 4095, 13,25);} //not centre, joystick rightgoing from centre
	else if(rawXPos<joystickCentreXRaw) {xPosMapped = map(rawXPos,20, joystickCentreXRaw, 1,13);} //not centre, joystick leftgoing  from centre

// 1 2 3 4 5 6 7 8 9 a b c |d| c b a 9 8 7 6 5 4 3 2 1
	if 	(xPosMapped==xPosMappedOld) {return;}
			 xPosMappedOld = xPosMapped;

  uint16_t xDisp=1000; //somewhere off display
  switch(xPosMapped)
	{
		case 13 : xDisp = (tft.width()/2) - (joystickMarkerLength/2);											break; // centre 	
		case 25 : xDisp = tft.width() - xMarginRightPixels - joystickMarkerLength - 1; 		break; // fully right
		case 1 	: xDisp = xMarginRightPixels + 1; 																				break; // fully left
		case 24: case 22: case 20: case 18: case 16: case 14: case 2: case 4: case 6: case 8: case 10: case 12: return;
		case 15: case 17: case 19: case 21: case 23: xDisp = ((tft.width()/2) - (joystickMarkerLength/2)) + ((joystickMarkerLength + 2) * (((xPosMapped%14)+1)/2)); break;
		case 11: case 9:  case  7: case  5: case 3 : xDisp = ((tft.width()/2) - (joystickMarkerLength/2)) - ((joystickMarkerLength + 2) * (((12-xPosMapped)+1)/2)); break;
	}
	//Serial.println (String("xposMapped=") + String(xPosMapped)+ String(",  xDisp=") + String(xDisp));
	uint16_t markerColor=ST77XX_RED;
	//markerColor += ((abs(xPosMapped-8)) * 0xb0);
	tft.fillRect		 (xDispOld, joystickMarkerYpos,   joystickMarkerLength, joystickMarkerHeight, colorTextBG_darkBlue); //clear old
  tft.drawFastHLine(xDispOld, joystickMarkerYpos+1, joystickMarkerLength, colorText1); //short green  line to replace upper border fragment
  tft.drawFastHLine(xDispOld, joystickMarkerYpos+5, joystickMarkerLength, colorText2); //short yellow line to replace lower border fragment
  tft.fillRect		 (xDisp,    joystickMarkerYpos,   joystickMarkerLength, joystickMarkerHeight, markerColor); //just to centre and get the right spread of the display
  xDispOld = xDisp;
}  
