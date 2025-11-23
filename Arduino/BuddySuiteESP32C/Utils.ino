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

//Adafruit_GFX.cpp
 void setPiss(const GFXfont *f, String test) 
 {
  GFXfont * gfxFont = (GFXfont *)f;
//  unsigned char c='e';
//  c -= (uint8_t)pgm_read_byte(&gfxFont->first);
//  //GFXglyph *glyph = pgm_read_glyph_ptr(gfxFont, c);
//  GFXglyph *glyph  = gfxFont->glyph + c;
//	uint16_t yo = pgm_read_byte(&glyph->xAdvance);

	//Serial.println( ((char)c) + String(" xAdvance=") + String(yo));

	// Length (with one extra character for the null terminator)

//String testStr="abcd";
char char_array[test.length() + 1];
test.toCharArray(char_array, test.length()+1);

for (uint8_t idx=0; idx<test.length(); ++idx)
{
	unsigned char c= char_array[idx];
  c -= (uint8_t)pgm_read_byte(&gfxFont->first);
  GFXglyph *glyph  = gfxFont->glyph + c;
	uint16_t yo = pgm_read_byte(&glyph->xAdvance);

	//Serial.println( ((char)c) + String(" xAdvance=") + String(yo));
	Serial.println( ((char)char_array[idx])  + String("=") + String(yo));
}
  

  /**
   * c -= (uint8_t)pgm_read_byte(&gfxFont->first);
    GFXglyph *glyph = pgm_read_glyph_ptr(gfxFont, c);
    uint8_t *bitmap = pgm_read_bitmap_ptr(gfxFont);

    uint16_t bo = pgm_read_word(&glyph->bitmapOffset);
    uint8_t w = pgm_read_byte(&glyph->width), h = pgm_read_byte(&glyph->height);
    int8_t xo = pgm_read_byte(&glyph->xOffset),
           yo = pgm_read_byte(&glyph->yOffset);
	   // &glyph->xAdvance	xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx   
    uint8_t xx, yy, bits = 0, bit = 0;
    int16_t xo16 = 0, yo16 = 0;
   */
 }
