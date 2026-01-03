//03Jan2026
#include <./Pics/SplashDRV3.h>
#include <./Pics/picSave_26x26.h>
#include <./Pics/thumbsup_23x24.h>
#include <./Pics/thumbsdown_23x24.h>

void LcdHdlr::setup(boolean showSplash)
{
	tft.init(240, 320);
	if(showSplash) {showStartupSplash();}
	tft.setFont(&Open_Sans_Italic_23); 	// https://oleddisplay.squix.ch/
	tft.setRotation(1);
	#ifdef INVERT_DISPLAY
		tft.setRotation(3);
	#endif
	
}  //2.0" 320x240 ST7789 TFT}

void LcdHdlr::showStartupSplash()
{
		drawBitMap(tft);//2 secdelay built in		
}

void LcdHdlr::drawBitMap(Adafruit_ST7789 tft)
	{
				tft.fillScreen(ST77XX_BLACK);
				tft.setRotation(1);
				#ifdef INVERT_DISPLAY
				tft.setRotation(3);
				#endif
  			tft.drawRGBBitmap(0, 0, BackgroundImage, 320,240);
				tft.setRotation  (0);
				#ifdef INVERT_DISPLAY
				tft.setRotation(2);
				#endif
				tft.drawRGBBitmap(240-152, 0, TitleText_152x320, 152, 320);
				delay (1500);
				tft.setRotation  (1);
				#ifdef INVERT_DISPLAY
				tft.setRotation(3);
				#endif
				tft.drawRGBBitmap(0, 0, BackgroundImage, 320,240);
				//delay (500);
				tft.fillScreen(ST77XX_BLACK);
				/**Many more drawbitmap functs in Adafruit_gfx.h
				void drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[], int16_t w, int16_t h);
				void drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h);
				void drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[], const uint8_t mask[], int16_t w, int16_t h);
				void drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, uint8_t *mask, int16_t w, int16_t h);
				*/
	}

void LcdHdlr::setJoystickMeter(const int & rawXPos, const CurrentValuesJB & values)
{
	int xPosMapped = 0;
	int hardRight=4095;
	int hardLeft = 20;
	if (joystickReaderJB.isCentredXRaw(rawXPos))  //+ or - 500 of joystickCentreXRaw if(joystickInXRaw<=joystickCentreXRaw-500 || joystickInXRaw>=joystickCentreXRaw+500)
		{
			xPosMapped=13;		//centre
  	}
	// else if(rawXPos>joystickReaderJB.joystickCentreXRaw) {xPosMapped = map(rawXPos,    joystickReaderJB.joystickCentreXRaw, 4095, 13,25);} //not centre, joystick rightgoing from centre
	// else if(rawXPos<joystickReaderJB.joystickCentreXRaw) {xPosMapped = map(rawXPos,20, joystickReaderJB.joystickCentreXRaw, 1,13);} //not centre, joystick leftgoing  from centre
  
	else if(rawXPos>joystickReaderJB.joystickCentreXRaw+500) {xPosMapped = map(rawXPos, joystickReaderJB.joystickCentreXRaw, hardRight, 10,25);} //not centre, joystick rightgoing from centre
	else if(rawXPos<joystickReaderJB.joystickCentreXRaw-500) {xPosMapped = map(rawXPos, hardLeft, joystickReaderJB.joystickCentreXRaw,   1,16);} //not centre, joystick leftgoing  from centre

//Serial.println(String("rawXPos= " ) +  String(rawXPos) + String(", xPosMapped=") + String(xPosMapped));
// 1 2 3 4 5 6 7 8 9 a b c |d| c b a 9 8 7 6 5 4 3 2 1
	
	//Serial.println(String("rawXPos=") + String(rawXPos) + String(", joystickCentreXRaw=") + String(joystickReaderJB.joystickCentreXRaw) + String(", xPosMapped=") + String(xPosMapped) + String(", xPosMappedOld=") + String(xPosMappedOld));

  uint16_t xDisp=1000; //somewhere off display
  switch(xPosMapped)
	{
		case 13 : xDisp = (tft.width()/2) - (joystickMarkerLength/2);											 break; // centre 	
		case 25 : xDisp = tft.width() 		- xMarginRightPixels - joystickMarkerLength - 1; break; // fully right
		case 1 	: xDisp = xMarginRightPixels + 1; 																				 break; // fully left
		case 24: case 22: case 20: case 18: case 16: case 14: case 2: case 4: case 6: case 8: case 10: case 12: return;
		case 15: case 17: case 19: case 21: case 23: xDisp = ((tft.width()/2) - (joystickMarkerLength/2)) + ((joystickMarkerLength + 2) * (((xPosMapped%14)+1)/2)); break;
		case 11: case 9:  case  7: case  5: case 3 : xDisp = ((tft.width()/2) - (joystickMarkerLength/2)) - ((joystickMarkerLength + 2) * (((12-xPosMapped)+1)/2)); break;
	 default: return;
	}

 if 	(xPosMapped==xPosMappedOld) {return;}
 			 xPosMappedOld = xPosMapped;
	
	//uint16_t markerColor=0xd800; //see https://rgbcolorpicker.com/565
	uint16_t markerColor=colorCursor;
	switch (abs(xPosMapped -13))
	{
//		case 0 : markerColor =ST77XX_RED; break;
//		case 2 : markerColor = 0xd80f   ; break;
  		case 4 : markerColor = 0x00df   ; break; //lighter blue
		case 6 : markerColor = 0x033f   ; break; //turquoise
  		case 8 : markerColor = 0x04bf   ; break; //light purple
  		case 10: markerColor = 0x063f   ; break;
		case 12: markerColor = 0x97ff   ; break;  //0xfcff
	}
	
  tft.fillRect		 (xDispOld, joystickMarkerYpos,   joystickMarkerLength, joystickMarkerHeight, colorTextBG_darkBlue); //clear old
  tft.drawFastHLine(xDispOld, joystickMarkerYpos+1, joystickMarkerLength, colorText1); //short yellow  line to replace upper border fragment
  tft.drawFastHLine(xDispOld, joystickMarkerYpos+5, joystickMarkerLength, (values.solubility==NOT_SOLUBLE?ST77XX_RED:values.solubility==PART_SOLUBLE?0xFE00:colorText2)); //short yellow line to replace lower border fragment
  tft.fillRect		 (xDisp,    joystickMarkerYpos,   joystickMarkerLength, joystickMarkerHeight, markerColor); //just to centre and get the right spread of the display
  xDispOld = xDisp;
}  
