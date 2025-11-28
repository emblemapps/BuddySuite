//28Nov2025
#include <SPI.h>
#include <BuddySuiteESP32C3.h>
//#include <./Pics/picMinty.h>
//#include <./Pics/picDestiny.h>
//#include <./Pics/GS850_320x215.h>
//#include <./fonts/Open_Sans_Italic_21.h> 
//#include <./fonts/Open_Sans_Italic_16.h> 
#include <./fonts/Open_Sans_Italic_23.h> 
//For ESP -> ST7789 TFT connections, see "Utils" tab
Utils utils;
JB_Main jbMain;

void setup() {
  Serial.begin(115200);
   jbMain.initJB();
   jbMain.startJB();
}

void loop() 
{
	//jbMain.test();
	jbMain.loopJB();
 // delay(200);
}



//void testlines(uint16_t color) {
//  tft.fillScreen(ST77XX_BLACK);
//  for (int16_t x=0; x < tft.width(); x+=6) {
//    tft.drawLine(0, 0, x, tft.height()-1, color);
//    delay(0);
//  }
//  for (int16_t y=0; y < tft.height(); y+=6) {
//    tft.drawLine(0, 0, tft.width()-1, y, color);
//    delay(0);
//  }
//
//  tft.fillScreen(ST77XX_BLACK);
//  for (int16_t x=0; x < tft.width(); x+=6) {
//    tft.drawLine(tft.width()-1, 0, x, tft.height()-1, color);
//    delay(0);
//  }
//  for (int16_t y=0; y < tft.height(); y+=6) {
//    tft.drawLine(tft.width()-1, 0, 0, y, color);
//    delay(0);
//  }
//
//  tft.fillScreen(ST77XX_BLACK);
//  for (int16_t x=0; x < tft.width(); x+=6) {
//    tft.drawLine(0, tft.height()-1, x, 0, color);
//    delay(0);
//  }
//  for (int16_t y=0; y < tft.height(); y+=6) {
//    tft.drawLine(0, tft.height()-1, tft.width()-1, y, color);
//    delay(0);
//  }
//
//  tft.fillScreen(ST77XX_BLACK);
//  for (int16_t x=0; x < tft.width(); x+=6) {
//    tft.drawLine(tft.width()-1, tft.height()-1, x, 0, color);
//    delay(0);
//  }
//  for (int16_t y=0; y < tft.height(); y+=6) {
//    tft.drawLine(tft.width()-1, tft.height()-1, 0, y, color);
//    delay(0);
//  }
//}
//
//void testdrawtext(char *text, uint16_t color) {
//  tft.setCursor(0, 0);
//  tft.setTextColor(color);
//  tft.setTextWrap(true);
//  tft.print(text);
//}
//
//void testfastlines(uint16_t color1, uint16_t color2) {  //240x320
//  tft.fillScreen(ST77XX_BLUE);
//	for (int y=230; y<250; ++y)
//	{  tft.fillScreen(ST77XX_BLACK);
//		 tft.setCursor(0, 30); tft.setTextColor(ST77XX_WHITE,ST77XX_BLUE); tft.setTextSize(4); tft.println(String("y=") + String(y));
//		 tft.drawFastHLine(0, y, tft.width(), color1);
//		 delay(1000);
//	}
////  for (int16_t y=0; y <= tft.height(); y+=20) {
////    tft.drawFastHLine(0, y, tft.width(), color1);
////  }
//////  for (int16_t x=0; x < tft.width(); x+=20) {
////    tft.drawFastVLine(x, 0, tft.height(), color2);
////  }
//}
//
//void testdrawrects(uint16_t color) {
//  tft.fillScreen(ST77XX_BLACK);
//  for (int16_t x=0; x < tft.width(); x+=6) {
//    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
//  }
//}
//
//void testfillrects(uint16_t color1, uint16_t color2) {
//  tft.fillScreen(ST77XX_BLACK);
//  for (int16_t x=tft.width()-1; x > 6; x-=6) {
//    tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
//    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
//  }
//}
//
//void testfillcircles(uint8_t radius, uint16_t color) {
//  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
//    for (int16_t y=radius; y < tft.height(); y+=radius*2) {
//      tft.fillCircle(x, y, radius, color);
//    }
//  }
//}
//
//void testdrawcircles(uint8_t radius, uint16_t color) {
//  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
//    for (int16_t y=0; y < tft.height()+radius; y+=radius*2) {
//      tft.drawCircle(x, y, radius, color);
//    }
//  }
//}
//
//void testtriangles() {
//  tft.fillScreen(ST77XX_BLACK);
//  uint16_t color = 0xF800;
//  int t;
//  int w = tft.width()/2;
//  int x = tft.height()-1;
//  int y = 0;
//  int z = tft.width();
//  for(t = 0 ; t <= 15; t++) {
//    tft.drawTriangle(w, y, y, x, z, x, color);
//    x-=4;
//    y+=4;
//    z-=4;
//    color+=100;
//  }
//}
//
//void testroundrects() {
//  tft.fillScreen(ST77XX_BLACK);
//  uint16_t color = 100;
//  int i;
//  int t;
//  for(t = 0 ; t <= 4; t+=1) {
//    int x = 0;
//    int y = 0;
//    int w = tft.width()-2;
//    int h = tft.height()-2;
//    for(i = 0 ; i <= 16; i+=1) {
//      tft.drawRoundRect(x, y, w, h, 5, color);
//      x+=2;
//      y+=3;
//      w-=4;
//      h-=6;
//      color+=1100;
//    }
//    color+=100;
//  }
//}
//
//void tftPrintTest() {
//  tft.setTextWrap(false);
//  tft.fillScreen(ST77XX_BLACK);
//  tft.fillScreen(ST77XX_BLACK);
//  tft.setTextColor(ST77XX_WHITE);
//  tft.setTextSize(0);
//  tft.setTextSize(1);
//  tft.setTextColor(ST77XX_GREEN);
//  tft.print(8675309, HEX); // print 8,675,309 out in HEX!
//  tft.print(millis() / 1000);
//  tft.setTextColor(ST77XX_WHITE);
//  tft.print(" seconds.");
//}
