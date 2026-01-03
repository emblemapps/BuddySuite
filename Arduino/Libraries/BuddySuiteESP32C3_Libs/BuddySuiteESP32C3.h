//03Jan2026
#ifndef HEADER_JoystickReader
#define HEADER_JoystickReader
#define JOYSTICK_X_PIN 2     
#define JOYSTICK_Y_PIN 3

enum JoystickForce {NONE, LIGHT, MEDIUM, HARD};
JoystickForce joystickForce=NONE;
class JoystickReader
{
	public:		
			int joystickCentreXRaw	 =0;
			boolean hasBeenCalibrated= false;
			void setup()   //calibrate centres on power up
			{
				if(!hasBeenCalibrated)
				{
					joystickCentreXRaw=analogRead(JOYSTICK_X_PIN);
					joystickCentreYRaw=analogRead(JOYSTICK_Y_PIN);
					hasBeenCalibrated=true;
				}
				oldJoystickXRaw=joystickCentreXRaw;
				oldJoystickYRaw=joystickCentreYRaw;				
			}
			boolean isCentredYRaw(int joystickInYRaw)
			{
				if(joystickInYRaw<=joystickCentreYRaw-550 || joystickInYRaw>=joystickCentreYRaw+550)
				{return false;}
				return true;
			}
			boolean isCentredYRaw()
			{
				return isCentredYRaw(analogRead(JOYSTICK_Y_PIN));
			}
			boolean isCentredXRaw(int joystickInXRaw)
			{
				if(joystickInXRaw<=joystickCentreXRaw-500 || joystickInXRaw>=joystickCentreXRaw+500)
				{return false;}
				return true;
			}
			boolean isCentredXRaw()
			{
				return isCentredXRaw(analogRead(JOYSTICK_X_PIN));
			}
			int getJoystickXRaw()
			{
				return joystickXRaw;
			}
			int getJoystickXMappedVal()
			{
				return joystickXMapped;
			}				
    protected:
			int oldJoystickXRaw=0;
			int oldJoystickYRaw=0;
			int joystickXRaw   =0;	
			int joystickYRaw   =0;
			int joystickXMapped=0;	
			int joystickCentreXMapped=0; 
			int joystickCentreYRaw	 =0;
	private:			
};
#endif

#ifndef HEADER_JoystickReaderJB
#define HEADER_JoystickReaderJB
class JB_JoystickReader : public JoystickReader
{
	public: 
			void getSelectedRow();
			void readAndConvertJoystickX(const int & incRawX);	
	private:
			unsigned long  millisSinceRowLastChanged = 0;	
};
#endif

#ifndef HEADER_JoystickReaderJBSAV
#define HEADER_JoystickReaderJBSAV
class JBSAV_JoystickReader : public JoystickReader
{
	public: 
			void getSelectedRow();
			void readAndConvertJoystickX(const int & incRawX);	
			boolean wasMovedRecently();
	private:
			boolean movedRecently;
			unsigned long millisSinceRowLastChanged = 0;	
};
#endif

#ifndef HEADER_JoystickPushSwReader
#define HEADER_JoystickPushSwReader
#define JOYSTICK_PUSHSW_PIN 1
class JoystickPushSwitchReader : public JoystickReader
{
	public:
			void setup();
			void checkForSwitchPush();
			void returnToJuiceBuddyScreen();
			boolean wasPressedRecently();
	private: 
			void sendPushSwitchNotification();
			boolean pressedRecently;
};
#endif

#ifndef HEADER_CurrentValuesJB
#define HEADER_CurrentValuesJB
enum Solubility {SOLUBLE, PART_SOLUBLE, NOT_SOLUBLE};
#define MIN_tojMl 0
#define MAX_tojMl 50
#define MIN_PG 0
#define MAX_PG 100
#define MIN_DEEMSRATIO 0.5
#define MAX_DEEMSRATIO 20
class CurrentValuesJB
{ 
public: 
		unsigned long  millisLastChangedtojMl		= 0;
		unsigned long  millisLastChangeddeemsRatio	= 0;
		unsigned long  millisLastChangedpgRatio		= 0;
		unsigned long  LastChangeddeemsMg			= 0;
		const uint16_t joystickIncrementDelayMillis = 190;
		void  setTojMl(float tojMl);
		float getTojMl();
		float deemsRatio			=0; 	
		int16_t pgRatio				=0;  //percentage PG
		float pgMl					=0;
		float vgMl					=0;
		unsigned long deemsMg		=0;
		float totalWeightOfDJuice_g	=0;
		float weightPg_g			=0;
		float weightVg_g			=0;
		void  setup();
		Solubility solubility;
		void incrementValue (const int & incValue, uint8_t fieldId);
		String toString();
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
			void loop();
			void loopJBSav();
			void test();
	private:
			unsigned long timeJbSAV_Started; //for the return to JB timeout
};
#endif

#ifndef HEADER_LcdHdlr
#define HEADER_LcdHdlr
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#define TFT_CS        21
#define TFT_RST       9 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC        10
const uint16_t colorTextBG_darkBlue	  = 0x0004; // 5.6.5 RGB
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST); 
enum ScreenShowing{JB, JBSAV}; 
class LcdHdlr
{	
	public: 
		LcdHdlr(){}
		ScreenShowing screenShowing;
		void setup(boolean showSplash);          			//2.0" 320x240 ST7789 TFT}
		void drawBitMap(Adafruit_ST7789 tft);
		void showStartupSplash();
		void setJoystickMeter(const int & rawXPos, const CurrentValuesJB & values);  //0-4096			
	protected:
		const uint16_t colorTextBG_darkBlue	  = 0x0004; // 5.6.5 RGB
		const uint16_t colorCursor   	 	  = 0x29F; //ST77XX_BLUE;
		const uint16_t colorText1     		  = ST77XX_YELLOW;
		const uint16_t colorText2     		  = 0X7E0;
		const uint8_t  xMarginLeftPixels   	  = 12 ;
		const uint8_t  xMarginRightPixels  	  = 12 ;
		const uint8_t  joystickMarkerLength	  = 21 ;   
		const uint8_t  joystickMarkerHeight	  = 8  ;
		const uint8_t  joystickMarkerYpos 	  = 103;
		const uint8_t  lineSpacing		 	  = 30 ;
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
		void updateScreen(CurrentValuesJB & values, boolean updateAll);
		void setSelectedField(uint8_t sel); //0-dJuice Reqd, 1-dRatio g/ml, 2-PG/VG, 3-DMT	
	private:
		boolean updateAll = false;
		const uint8_t xOffsetMg 		  = 144;
		const uint8_t xOffsetMl           = 150;
		const uint8_t textToUnitGapPixels = 3 ; //eg 1.3<gap>ml
		uint16_t 	  olubleStrLenPixels  = 0 ; //set in setupScreen()
	    uint16_t 	  quasi_StrLenPixels  = 0 ; //set in setupScreen()
		const String  quasi_Str     = "Quasi-";
		const String  mlStr 		= "ml"; 
		const String  olubleStr     = "oluble";
		float 	 oldTojMl           = 0;
		float 	 oldDeemsRatio 		= 0; 
		float  	 oldPgRatio	 		= 0;
		int16_t  oldDeemsMg			= 0;
		float 	 oldPgMl            = 0;
		float 	 oldVgMl            = 0;
        float 	 oldTotalWeightOfDJuice_g = 0;
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
		String makeDRatString (const CurrentValuesJB & valuesJB);
		String makeDratString (const float drat);
	private:	
};
#endif

#ifndef HEADER_JB_Save_LchH
#define HEADER_JB_Save_LchH
class JB_SaveLcdH: public LcdHdlr
{
	public:
		const uint16_t idleScreenTimeout_ms = 60000;
		void setupScreen(CurrentValuesJB & valuesJB);
		void setSelectedRow(int selectedRow);
		void joystickMoveX(boolean toRight);
		void setStatusMessage(String & message, const GFXfont *f);
		void doClick();
		String currentSettingsString=""; 
		void printStatusMessage();
		const GFXfont *statusMessageFont;
	private:
			String statusMessage="";
			unsigned long maxIdleDuration =  10 * 1000; //60 secs for now
			void displaySaveLocationsFramework();
			void populateSaveLocationsArray();
			void displaySaveLocationsStrings(boolean animate);
			void printCurrentSettingsString(CurrentValuesJB & valuesJB, boolean flashText);		
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
			void deleteFile(String & filenameIn);
			void writeTextFile(String & Filename, String & text2Write);  //writeTextFile
			String readFile(String & filename);
			void listSavFiles(String (& params) [5]);
	protected:
	private:
};
#endif

#ifndef HEADER_SaveLocationJB
#define HEADER_SaveLocationJB
//#include <SPIFFS_ImageReader.h> //https://forum.arduino.cc/t/st7789-draw-bmp-files-faster/685758/5
enum SelectState {SELECTED, UNSELECTED};
class SaveLocationJB
{
	public: 
			SelectState selectState= UNSELECTED;
			SaveLocationJB(String filenameIn, int yPosIn);
			void loadFile();  // sets the three calc variables of the current valuesJb
			void saveFile();
			void deleteFile();
			void setValues(float (& valsArray) []);
			void printDisplayString(boolean animate);
			//void refreshButtonString();
			void printButtonString();
			void printButtonString(uint16_t color);
			uint8_t buttonStringIndex = 0;
			void joystickMoveX(boolean right);
			void select();
			void unSelect();
			void doClick();
			boolean isEmpty=true;
			void   clear();
			String filename="";
			String saveString = "";
			void   setDisplayString(String displayStringIn);
			float  tojMl=0;
			float  deemsRatio = 0;
			int16_t pgRatio=0;
			String oldDisplayString ="";
			boolean selected=false;
			boolean oldSelected =false;
	protected:
	private:
				String buttonStrDisplayed="save";
				String displayString ="";
				String oldButtonString = "";
				uint16_t oldButtonTextColor = 0;
				void makeDisplayString();
				void setCursorForButtonString();
				void animateButtonProgressBar();
				int yPos;
				int xPos=49;
				
};
String ButtonStrings[] = {"save", "load", "clear"};
SaveLocationJB saveLocations [] = {SaveLocationJB("jb1.sav", 110), SaveLocationJB("jb2.sav",140), SaveLocationJB("jb3.sav", 170), SaveLocationJB("jb4.sav", 200), SaveLocationJB("jb5.sav", 230)};
#endif
