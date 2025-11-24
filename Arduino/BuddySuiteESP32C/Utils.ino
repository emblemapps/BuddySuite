/**
 * Connections
 * 
 * 
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
			Serial.println(((char)char_array[idx])  + String("=") + String(pixelWidthCurrent)+ String(", total pixels so far=") + String(pixelLengthCount));
		}
		return pixelLengthCount;
 }
  

  /**
   * Also for reading glyphs struct .....
    GFXglyph *glyph = pgm_read_glyph_ptr(gfxFont, c);
    uint8_t *bitmap = pgm_read_bitmap_ptr(gfxFont);
    uint16_t bo = pgm_read_word(&glyph->bitmapOffset);
    uint8_t w 	= pgm_read_byte(&glyph->width), h = pgm_read_byte(&glyph->height);
    int8_t xo 	= pgm_read_byte(&glyph->xOffset),
    int8_t yo  = pgm_read_byte(&glyph->yOffset);
   */
 
