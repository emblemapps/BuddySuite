//07Dec2025
#ifndef HEADER_JoystickReader
#define HEADER_JoystickReader
#define JOYSTICK_X_PIN 2     
#define JOYSTICK_Y_PIN 3
class JoystickReader
{
	public:		
			
	    	void setup();
			//boolean isCentredYRaw(int joystickInYRaw);
			//boolean isCentredXRaw(int joystickInXRaw);
			//boolean isCentredYRaw();
			//boolean isCentredXRaw();
			//boolean isCentred();
			//void getSelectedRow(uint8_t & selectedRow);
			//void readAndConvertJoystick(const int & incRawX, const int & incRawY);
    protected:
			
	private:
            //void makeJoystickMeterString(uint8_t & incX);			
};
#endif

#ifndef HEADER_JoystickReaderJB
#define HEADER_JoystickReaderJB
enum JoystickForce {NONE, LIGHT, MEDIUM, HARD};
JoystickForce joystickForce=NONE;
class JB_JoystickReader
{
	public:
		    int oldJoystickXRaw=0;
			int joystickXRaw=0;
			void setup();
			boolean isCentredYRaw(int joystickInYRaw);
			boolean isCentredXRaw(int joystickInXRaw);
			boolean isCentredYRaw();
			boolean isCentredXRaw();
			//boolean isCentred();
			void getSelectedRow(uint8_t & selectedRow);
			void readAndConvertJoystick(const int & incRawX, const int & incRawY);	
			int getJoystickXMappedVal();
			//joystickForce = NONE;
	private:
            void makeJoystickMeterString(uint8_t & incX);
			int joystickXMapped=0;
			
};
#endif

#ifndef HEADER_CurrentValuesJB
#define HEADER_CurrentValuesJB
enum Solubility {SOLUBLE, PART_SOLUBLE, NOT_SOLUBLE};
class CurrentValuesJB
{ 
public: 
		//JB_JoystickReader joystickReaderJBin;
        void  setTojMl(float tojMl);
		float getTojMl();
		float deemsRatio			=0; 	
		int16_t pgRatio				=0;  //percentage PG
		float pgMl					=0;
		float vgMl					=0;
		int16_t deemsMg				=0;
		float totalWeightOfDJuice_g	=0;
		float weightPg_g			=0;
		float weightVg_g			=0;
		//void setup(JB_JoystickReader & joystickReaderJBinput);
		void setup();
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

#ifndef HEADER_JBMain
#define HEADER_JBMain
class JB_Main
{
	public:
			void initJB();
			void startJB();
			void loopJB();
			void test();
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
		void setup(boolean showSplash);          			//2.0" 320x240 ST7789 TFT}
		void drawBitMap(Adafruit_ST7789 tft);
		void showStartupSplash();
		void setJoystickMeter(const int & rawXPos, const CurrentValuesJB & values);  //0-4096		
	protected:
		const uint16_t colorTextBG_darkBlue	  = 0x0004; // 5.6.5 RGB
		const uint16_t colorCursor   	 	  = ST77XX_BLUE;
		const uint16_t colorText1     		  = ST77XX_YELLOW;
		const uint16_t colorText2     		  = 0X7E0;
		const uint8_t  xMarginLeftPixels   	  = 12 ;
		const uint8_t  xMarginRightPixels  	  = 12 ;
		const uint8_t  joystickMarkerLength	  = 21 ;   
		const uint8_t  joystickMarkerHeight	  = 8  ;
		const uint8_t  joystickMarkerYpos 	  = 103;
		int   xPosMappedOld 				  = 99 ; //somewhere off-screen
		int   xDispOld 						  = 153; //centre, may need dehackying
		//unsigned long  millisJoystickMeterLastChanged			= 0;
		};
#endif

#ifndef HEADER_JBLcdHdlr
#define HEADER_JBLcdHdlr
class JB_LcdHdlr:public LcdHdlr
{
	public: 
		JB_LcdHdlr(){}
		//void setup();
		void setupScreen();
		void updateScreen(CurrentValuesJB & values);
		void setSelectedField(uint8_t sel); //0-dJuice Reqd, 1-dRatio g/ml, 2-PG/VG, 3-DMT	
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
		//const String  olubleStr     = "ðŸ‘";
		
		float 	 oldTojMl           = 0;
		float 	 oldDeemsRatio 		= 0; 
		float  	 oldPgRatio	 		= 0;
		int16_t  oldDeemsMg			= 0;
        float oldTotalWeightOfDJuice_g = 0;
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
		uint32_t color24to16(uint32_t color888);
	private:	
};
#endif

#ifndef HEADER_JB_Save_LchH
#define HEADER_JB_Save_LchH

class JB_SaveLcdH: public LcdHdlr
{
	public:
		//void setup();
		void setupScreen();
		
	private:	
};
#endif

#ifndef HEADER_LittleFS
#define HEADER_LittleFS
#include "LittleFS.h" 
//#include <SPIFFS_ImageReader.h> //https://forum.arduino.cc/t/st7789-draw-bmp-files-faster/685758/5
#include <FS.h>
class LittleFSManager
{
	public: 
			void setup();
			//void listFiles();
			void writeTextFile();  //writeTextFile
			void readFile(String & filename);
			void listFiles();
	protected:
	private:
};
#endif
