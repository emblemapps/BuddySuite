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

#ifndef HEADER_Utils
#define HEADER_Utils
class Utils
{
	public:
		void rightJustifyPad(String & mlStr, int16_t reqLen);
	private:	
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

#ifndef HEADER_JBLcdHdlr
#define HEADER_JBLcdHdlr
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789

class JB_LcdHdlr
{
	public: 
		void setup();	
		void updateScreen(CurrentValuesJB & values);
		void setSelectedField(uint8_t sel); //0-dJuice Reqd, 1-dRatio g/ml, 2-PG/VG, 3-DMT
		void setJoystickMeter(uint16_t & rawXPos);  //0-4096
private:
		const uint8_t xMarginLeftPixels   = 12 ;
		const uint8_t xMarginRightPixels  = 12 ;
		const uint8_t xOffsetMg 		  = 148;
		const uint8_t xOffsetMl           = 150;
		const uint8_t lineSpacing		  = 30;
		const uint8_t textToUnitGapPixels = 3 ; //eg 1.3<gap>ml
		uint16_t 	  olubleStrLenPixels  = 0 ; //set in setupScreen()
		const String  mlStr 		= "ml"; 
		const String  olubleStr     = "oluble";
		uint16_t colorTextBG    	= 0x0004; // 5.6.5 RGB
		uint32_t colorScreenBG  	= ST77XX_CYAN;
		uint16_t colorText1     	= ST77XX_YELLOW;
		uint16_t colorText2     	= 0X7E0;
		uint32_t colorCursor   	 	= 0xFAAA;  
		float 	 oldTojMl           = 0;
		float 	 oldDeemsRatio 		= 0; 
		int16_t  oldPgRatio	 		= 0;
		uint16_t oldDeemsMg			= 0;
        uint16_t oldTotalWeightOfDJuice_g = 0;		
		void setupScreen();
		void setDjuiceRequiredField	(CurrentValuesJB & values);
		void setDRatField			(CurrentValuesJB & values);
		void setPgRatField			(CurrentValuesJB & values);
		void setPgMlOrVgMlField 	(CurrentValuesJB & values, boolean PG);
		void setDeemsMgField		(const CurrentValuesJB & values);
		void setSolubilityField		(const CurrentValuesJB & values);	
		void setTotalJuiceGramsField(const CurrentValuesJB & values);
		
};
#endif
