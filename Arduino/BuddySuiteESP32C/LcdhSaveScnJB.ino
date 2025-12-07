//07Dec2025
unsigned long timeStarted;
/**
Called from JBMain
*/
// void JB_SaveLcdH::setup()
// {
//   /**tft.init(240, 320);
// 	showStartupSplash();*/
// }

void JB_SaveLcdH::setupScreen()
{
        timeStarted = millis();
        tft.setFont (&Open_Sans_Italic_23); 	// https://oleddisplay.squix.ch/
				tft.setRotation(1);
				tft.fillScreen(colorTextBG_darkBlue);

        tft.drawRoundRect(0, 0, 	tft.width(), tft.height(), 10, colorText1);  //yellow border line
        tft.drawRGBBitmap(41, 13, saveIcon26x26, 26,26);
        tft.setCursor    (77, 32);
        tft.setTextColor (colorText2, colorTextBG_darkBlue);
        tft.println      ("Save Current Juice");
}