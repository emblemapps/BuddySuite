  //tft.init(320, 240);           //1.3" or 1.54" 240x240 ST7789 TFT:
   //tft.init(240, 280);           //1.69" 280x240 ST7789 TFT:
   //tft.init(135, 240);           //       ST7789 240x135
   //tft.init(172, 320);           // 1.47" 172x320 ST7789 TFT:
   //tft.init(170, 320);           // 1.9"  170x320 ST7789 TFT
   // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library, you can override it here
  // Allowable spped depends on chip & wiring Too fast may get you a black screen some times, continuous.
  //tft.setSPISpeed(40000000);
  
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);  
//Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void JB_LcdHdlr::setupScreen()
		{		  
				tft.fillScreen(colorTextBG);
				//////////////////////////////////////////////////////////////////////////////////
				tft.drawRoundRect(0, 0, tft.width(), tft.height()-135, 10, colorText1);
				tft.drawRoundRect(0, 108, tft.width(), tft.height()-110, 10, colorText2);
		  	//////////////////////////////////////////////////////////////////////////////////

				uint8_t yOffset = 30; uint8_t xMargin = 12; uint8_t lineSpacing=30;
				tft.setTextColor(colorText1, colorTextBG);  	
				tft.setCursor(xMargin, yOffset); tft.print("dJuice Req'd");  tft.setCursor(281 , yOffset); tft.print("ml");  
				yOffset+=lineSpacing;
				tft.setCursor(xMargin, yOffset); tft.print("dRatio g/ml");
				yOffset+=lineSpacing;
				tft.setCursor(xMargin, yOffset); tft.print("PG/VG");
				/////////////////////////////////////////////////////////////////////////////////////////////////
				tft.setTextColor(colorText2, colorTextBG); 
				yOffset+=lineSpacing+15;
  			tft.setCursor(xMargin, yOffset); tft.print("PG"); tft.setCursor(150, yOffset); tft.print("ml"); tft.setCursor(297, yOffset); tft.print("g");
  			yOffset+=lineSpacing;
  			tft.setCursor(xMargin, yOffset); tft.print("VG"); tft.setCursor(150, yOffset); tft.print("ml");  tft.setCursor(297, yOffset); tft.print("g");
  			yOffset+=lineSpacing;
  			tft.setCursor(xMargin, yOffset); tft.print("DMT");tft.setCursor(150, yOffset);tft.print("mg");
				yOffset+=lineSpacing;
				tft.setTextColor(ST77XX_CYAN, colorTextBG);
  			tft.setCursor(235, yOffset); tft.print(("oluble"));
		}

void JB_LcdHdlr::setup()
{
	tft.init(240, 320);            			//2.0" 320x240 ST7789 TFT
	tft.setFont(&Open_Sans_Italic_23); 	// https://oleddisplay.squix.ch/
	tft.setRotation(1);

  setupScreen();
  delay(500);
//	for (int x=0;x<1000;x++)
//	{
//		drawBitMap();
//	}
}	

void JB_LcdHdlr::updateScreen(CurrentValuesJB & values)  
{
	tft.setTextColor(colorText1, colorTextBG);
	setDjuiceRequiredField(values);
	setDRatField 					(values);
	setPgRatField					(values);
	setPgMlOrVgMlField    (values, true);
	setPgMlOrVgMlField    (values, false);
	setDeemsMgField       (values);
	tft.setTextColor(ST77XX_CYAN, colorTextBG);
	setSolubilityField    (values);
}
void JB_LcdHdlr::setSelectedField(uint8_t sel){} //0-dJuice Reqd, 1-dRatio g/ml, 2-PG/VG, 3-DMT
void JB_LcdHdlr::setJoystickMeter(uint16_t & rawXPos){}  //0-4096

  	 //colorTextBG    = 0x0004; // //16-bit 5-6-5 Color to draw text with   00000 000000 01000 1F
		//uint32_t JB_LcdHdlr::colorScreenBG  = TFT_CYAN;
		//uint32_t JB_LcdHdlr::colorText1     = TFT_YELLOW;
		//uint32_t JB_LcdHdlr::colorText2     = TFT_PINK;
		//uint32_t JB_LcdHdlr::colorCursor    = 0xFAAA; 
		 
		
		void JB_LcdHdlr::setDjuiceRequiredField(CurrentValuesJB & values)
		{
			uint8_t yOffset = 30;  uint8_t xOffset=245;
			float needed = values.getTojMl();
			String mlStr = String(needed,1); //"0.1" "9.3" "20.8"		
			 	
			tft.setCursor(xOffset, yOffset); tft.print(mlStr);  
		}
		
		void JB_LcdHdlr::setDRatField(CurrentValuesJB & values)
		{
			uint8_t yOffset = 60;  uint8_t xOffset=245;
			uint8_t dRatX10 = values.deemsRatio * 10;
			uint8_t prefix=1;
     	if(dRatX10<10)
     	{
       prefix=2;
       dRatX10 = dRatX10 *2;
     	} 
		 	uint8_t digit1 = (dRatX10/10);
     	uint8_t digit2 = dRatX10 - (digit1*10);
     	String out = String(prefix) + String(":")+ String(digit1) + String(".") + String(digit2);	
		 	tft.setCursor(xOffset, yOffset); tft.print(out);		
		}
		
		
		void JB_LcdHdlr::setPgRatField(CurrentValuesJB & values)
		{
			uint8_t yOffset = 90;  uint8_t xOffset=245;
			uint8_t pgPerc 	= values.pgRatio;
			uint8_t vgPerc 	= 100-pgPerc;
      String out = String(pgPerc) + ('/') + String(vgPerc);  	
		 	tft.setCursor(xOffset, yOffset); tft.print(out);	
		}
		
		void JB_LcdHdlr::setPgMlOrVgMlField(CurrentValuesJB & values, boolean PG)
		{
			uint8_t yOffset = 135;  if (!PG) {yOffset = 165;}
			uint8_t xOffset = 95;
			
			float ml = (PG? values.pgMl:values.vgMl );
			String MlStr = String(ml,2); 
			tft.setCursor(xOffset, yOffset); tft.print(MlStr);
		}		 
		
		void JB_LcdHdlr::setDeemsMgField(const CurrentValuesJB & values)
		{
			uint8_t yOffset = 195; uint8_t xOffset = 88;
			uint16_t  deemsMg = values.deemsMg;
			String mgDeems = String(deemsMg);
			utils.rightJustifyPad(mgDeems, 5);
			tft.setCursor(xOffset, yOffset); tft.print(mgDeems); 
		}
		void JB_LcdHdlr::setSolubilityField(const CurrentValuesJB & values)
		{
			uint8_t yOffset = 225; uint8_t xOffset = 235;//xoffset is for the "oluble" printed at setupscreen()
			Solubility solubility = values.solubility;
			//solubility=NOT_SOLUBLE;
			String solStr = "S"; String upperLineString = "      ";
			switch(solubility)
  		{
    		case PART_SOLUBLE:  upperLineString = "Quasi-"; break;
    		case SOLUBLE:       														break;
    		case NOT_SOLUBLE:   solStr = "Ins";    					break;
    		default:            														break;
  		}	
  		 //utils.rightJustifyPad(solStr,6);
  		 uint16_t strLenPixels = getStringWidthPixels(&Open_Sans_Italic_23,solStr);
  		 //tft.drawRect (242-strLenPixels, yOffset-23,strLenPixels, 23, ST77XX_RED );
  		 tft.setCursor(xOffset-strLenPixels, yOffset); 	tft.print(solStr); 
  		 tft.setCursor(xOffset-5, yOffset-30); 					tft.print(upperLineString); 
  		
			/**
			 *
  
  
  utils.rightJustifyPad(solStr,8);
  char buffer[10];
  solStr.toCharArray(buffer, 9);

  display.setCursor(87, 50);
  display.print(upperLineString); 
  
  display.setCursor(41, 57);
  display.print(buffer); 
			 */
		}	
		
		
void JB_LcdHdlr::setTotalJuiceGramsField(float totalWeightOfDJuice_g){}		

void drawBitMap()
{
	tft.fillScreen(ST77XX_BLACK);
	//tft.drawRGBBitmap(0, 0, bitmap_Minty320_170, 320,170);
	delay (10000);
	tft.fillScreen(ST77XX_BLACK);
	//tft.drawRGBBitmap(0, 0, bitmap_DestinyVideo320_170, 320,170);
	delay (10000);
	tft.fillScreen(ST77XX_BLACK);
	//tft.drawRGBBitmap(0, 0, lcd_gs850, 320,215);
	               
	
	/**Many more drawbitmap functs in Adafruit_gfx.h
	void drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[], int16_t w, int16_t h);
  void drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h);
  void drawRGBBitmap(int16_t x, int16_t y, const uint16_t bitmap[], const uint8_t mask[], int16_t w, int16_t h);
  void drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, uint8_t *mask, int16_t w, int16_t h);
   */
}
