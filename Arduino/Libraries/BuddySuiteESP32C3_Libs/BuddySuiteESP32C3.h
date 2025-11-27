//27Nov2025
#ifndef HEADER_CurrentValues
#define HEADER_CurrentValues
enum Solubility {SOLUBLE, PART_SOLUBLE, NOT_SOLUBLE};
class CurrentValuesJB
{ 
public: 
        void  setTojMl(float tojMl);
		float getTojMl();
		float deemsRatio			=0; 	
		int16_t pgRatio				=0;  //percentage PG
		float pgMl					=0;
		float vgMl					=0;
		uint16_t deemsMg			=0;
		float totalWeightOfDJuice_g	=0;
		float weightPg_g			=0;
		float weightVg_g			=0;
		void  setup();
		//uint8_t solubility=0; //0=SOLUBLE, 1=PART_SOLUBLE, 2=NOT_SOLUBLE
		Solubility solubility;
		void incrementValue (const int & incValue, uint8_t fieldId);		
private:	
		float tojMl					=0; //initialised in the setup
};
#endif



#ifndef HEADER_JBCalc
#define HEADER_JBCalc
//given total djuice, deem ratio, and pg/vg ratio, calculate pg, vg and dmt weight
#define VG_WEIGHTG_PER_ML 1.261
#define PG_WEIGHTG_PER_ML 1.036 
class JB_Calc
{ 
public: 
		void setup(); //never called
		void calculate(CurrentValuesJB & values, boolean Dont_Update_DeemsMg);
		void calculateForDeemsWeight(CurrentValuesJB & values);
private:				 
};
#endif

#ifndef HEADER_LcdHdlr
#define HEADER_LcdHdlr
//#include <./Pics/picMinty.h>
//#include <./Pics/picDestiny.h>
//#include <./Pics/GS850_320x215.h>
//#include <./fonts/Open_Sans_Italic_21.h> 
//#include <./fonts/Open_Sans_Italic_16.h> 
//#include <./fonts/Open_Sans_Italic_23.h> 

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#define TFT_CS        21
#define TFT_RST       9 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC        10
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);  
class LcdHdlr
{	
	public: 
			LcdHdlr(){}
			void setup(){tft.init(240, 320);}          			//2.0" 320x240 ST7789 TFT}
			void drawBitMap(Adafruit_ST7789 tft)
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
	protected:
		uint16_t colorTextBG    		  = 0x0004; // 5.6.5 RGB
		uint32_t colorScreenBG  		  = ST77XX_CYAN;
		uint16_t colorText1     		  = ST77XX_YELLOW;
		uint16_t colorText2     		  = 0X7E0;
		uint32_t colorCursor   	 		  = 0xFAAA;
		const uint8_t xMarginLeftPixels   = 12 ;
		const uint8_t xMarginRightPixels  = 12 ;		
};
#endif

#ifndef HEADER_JBMain
#define HEADER_JBMain
class JB_Main
{
	public:
			void initJB();
			void startJB();
			void test();
	private:
};
#endif


#ifndef HEADER_JBLcdHdlr
#define HEADER_JBLcdHdlr
class JB_LcdHdlr:public  LcdHdlr
{
	public: 
		JB_LcdHdlr(){}
		//void setup();
		void setupScreen();
		void updateScreen(CurrentValuesJB & values);
		void setSelectedField(uint8_t sel); //0-dJuice Reqd, 1-dRatio g/ml, 2-PG/VG, 3-DMT
		void setJoystickMeter(uint16_t & rawXPos);  //0-4096
private:
		const uint8_t xOffsetMg 		  = 148;
		const uint8_t xOffsetMl           = 150;
		const uint8_t lineSpacing		  = 30;
		const uint8_t textToUnitGapPixels = 3 ; //eg 1.3<gap>ml
		uint16_t 	  olubleStrLenPixels  = 0 ; //set in setupScreen()
	    uint16_t 	  quasi_StrLenPixels  = 0 ; //set in setupScreen()
		const String  quasi_Str           = "Quasi-";
		const String  mlStr 		= "ml"; 
		const String  olubleStr     = "oluble";
		
		float 	 oldTojMl           = 0;
		float 	 oldDeemsRatio 		= 0; 
		int16_t  oldPgRatio	 		= 0;
		uint16_t oldDeemsMg			= 0;
        uint16_t oldTotalWeightOfDJuice_g = 0;
		float oldPgMl               = 0;
		float oldVgMl               = 0;
		Solubility oldSolubility	= NOT_SOLUBLE;	 //something that mismatches initial setup so we force update to get "Soluble" and not "oluble"
		
		void setDjuiceRequiredField	(CurrentValuesJB & values);
		void setDRatField			(CurrentValuesJB & values);
		void setPgRatField			(CurrentValuesJB & values);
		void setPgMlOrVgMlField 	(CurrentValuesJB & values, boolean PG);
		void setDeemsMgField		(const CurrentValuesJB & values);
		void setSolubilityField		(const CurrentValuesJB & values);	
		void setTotalJuiceGramsField(const CurrentValuesJB & values);	
};
#endif

#ifndef HEADER_Utils
#define HEADER_Utils
class Utils
{
	public:
		void rightJustifyPad(String & mlStr, int16_t reqLen);
	private:	
};
#endif

#ifndef HEADER_JoystickReader
#define HEADER_JoystickReader
#define JOYSTICK_X 3     
#define JOYSTICK_Y 4
class JoystickReader
{
	public:
				
	protected:
			void setup();
			boolean isCentredYRaw(int joystickInYRaw);
			boolean isCentredXRaw(int joystickInXRaw);
			boolean isCentredY();
			boolean isCentredX();
			boolean isCentred();
			//void getSelectedRow(uint8_t & selectedRow);
			//void readAndConvertJoystick(const int & incRawX, const int & incRawY);	
	private:
            //void makeJoystickMeterString(uint8_t & incX);			
};
#endif

#ifndef HEADER_JoystickReaderJB
#define HEADER_JoystickReaderJB
class JoystickReaderJB
{
	public:
	protected:
			void getSelectedRow(uint8_t & selectedRow);
			void readAndConvertJoystick(const int & incRawX, const int & incRawY);	
	private:
            void makeJoystickMeterString(uint8_t & incX);	
			
};
#endif
