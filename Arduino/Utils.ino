//19Dec2025
/**
 * Connections
 * ESP32C3  ST7789 Display (currently 320x240)
 * 3.3V				BL  brown
 * GPIO 21		CS	purple
 * GPIO 10		DC	blue
 * GPIO 9			RST	green
 * GPIO	6			SDA	yellow
 * GPIO 4			SCL	orange
 * 3.3V				VCC	red
 * GND				GND	gray
 */
// #include "SPIFFS.h" 
// #include <SPIFFS_ImageReader.h> //https://forum.arduino.cc/t/st7789-draw-bmp-files-faster/685758/5
// #include <FS.h>
 void Utils::rightJustifyPad(String & mlStr, int16_t reqLen)
{
  String spaces(""); String sp(" ");
  int16_t len = mlStr.length();
  int16_t len2add = reqLen-len;
  if(len2add<1) {return;}
  for(int16_t x=0 ;x<len2add;++x)
  {
    spaces = sp + spaces;
  }
  mlStr = spaces + mlStr;
}

/***************************************************************************************
* Stolen from tft_eSPI.cpp
* Function name:           color24to16
* Description:             convert 24-bit colour to a 16-bit 565 colour value  ffffff
***************************************************************************************/
uint32_t Utils::color24to16(uint32_t color888)
{
  uint16_t r = (color888 >> 8) & 0xF800;
  uint16_t g = (color888 >> 5) & 0x07E0;
  uint16_t b = (color888 >> 3) & 0x001F;
  return (r | g | b);
}

 String Utils::makeDRatString (const CurrentValuesJB & valuesJB)
 {
     return makeDratString(valuesJB.deemsRatio);
     
    //uint8_t dRatX10 = valuesJB.deemsRatio * 10;
		// uint8_t prefix=1;
    // if(dRatX10<10)
    //  	{
    //    	prefix=2;
    //    	dRatX10 = dRatX10 *2;
    //  	} 
		//  	uint8_t 	digit1 = (dRatX10/10);
    //  	uint8_t 	digit2 = dRatX10 - (digit1*10);
    //  	String 		outStr = String(prefix) + String(":")+ String(digit1) + String(".") + String(digit2);	
    //return outStr;
 }

 String Utils::makeDratString(const float drat)
 {
    uint8_t dRatX10 = drat * 10;
		uint8_t prefix=1;
    if(dRatX10<10)
     	{
       	prefix=2;
       	dRatX10 = dRatX10 *2;
     	} 
		 	uint8_t 	digit1 = (dRatX10/10);
     	uint8_t 	digit2 = dRatX10 - (digit1*10);
     	String 		outStr = String(prefix) + String(":")+ String(digit1) + String(".") + String(digit2);	
      return outStr;
 }

/**
 * adapted from code in Adafruit_GFX.cpp
 */
 uint16_t getStringWidthPixels(const GFXfont *f, const String & strInput) 
 {
 	GFXfont * gfxFont = (GFXfont *)f;
	char char_array[strInput.length() + 1];
	strInput.toCharArray(char_array, strInput.length()+1);

	uint16_t pixelLengthCount = 0;
	for (uint8_t idx=0; idx<strInput.length(); ++idx)
		{
			unsigned char currentChar = char_array[idx];
  		currentChar -= (uint8_t)pgm_read_byte(&gfxFont->first);
  		GFXglyph *glyph  = gfxFont->glyph + currentChar;
			uint16_t pixelWidthCurrent = pgm_read_byte(&glyph->xAdvance);
			pixelLengthCount+=pixelWidthCurrent;
			//Serial.println(((char)char_array[idx])  + String("=") + String(pixelWidthCurrent)+ String(", total pixels so far=") + String(pixelLengthCount));
		}
		return pixelLengthCount;
 }
  /**
   * Also for reading glyphs struct .....
    GFXglyph *glyph = pgm_read_glyph_ptr(gfxFont, c);
    uint8_t *bitmap = pgm_read_bitmap_ptr(gfxFont);
    uint16_t bo = pgm_read_word(&glyph->bitmapOffset);
    uint8_t w 	= pgm_read_byte(&glyph->width), 
    uint8_t h   = pgm_read_byte(&glyph->height);
    int8_t xo 	= pgm_read_byte(&glyph->xOffset),
    int8_t yo  = pgm_read_byte(&glyph->yOffset);
   */

//https://github.com/ThingPulse/minigrafx/blob/master/src/MiniGrafx.cpp#L654

/** "3.5 3.00 70" */
void splitToFloats(const String & StringIn, float array[], uint8_t arraySize)
{
  String chopStr = StringIn;
  int StringCount=0;
    while (StringIn.length() > 0)
    {
        int index = chopStr.indexOf(' ');
        if (index == -1) // No space found
        { break; }
        else       //space found
        {
          String currStr= chopStr.substring(0, index);
          array[StringCount++] = currStr.substring(0, index).toFloat();
          chopStr = chopStr.substring(index+1);
        }
    }
    array[StringCount]= chopStr.toFloat();
}

   /** while (str.length() > 0)
  {
    int index = str.indexOf(' ');
    if (index == -1) // No space found
    {
      strs[StringCount++] = str;
      break;
    }
    else
    {
      strs[StringCount++] = str.substring(0, index);
      str = str.substring(index+1);
    }
  }
  */
  
