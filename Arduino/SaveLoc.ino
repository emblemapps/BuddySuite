//19Dec2025
/**
   float tojMl=0;
	int16_t pgRatio=0;
	float deemsRatio = 0;
*/

/*Constructor filenames will be const at jb1.sav to jb5.sav*/
SaveLocation::SaveLocation(String filenameIn, int yPosIn)
{
   filename = filenameIn;
   yPos = yPosIn;
}


String ButtonStrings[] = {"save", "load", "clear"};

void SaveLocation::joystickMoveX(boolean right)
{
      if (right) 
      { 
         if (buttonStringIndex<2) {buttonStringIndex++;} else{buttonStringIndex=0;}  
      }
      else if (!right) //just for clarity
      {
         if (buttonStringIndex>0) {buttonStringIndex--;} else{buttonStringIndex=2;}
      }
      if(isEmpty) { buttonStringIndex=0;}
      buttonStrDisplayed=ButtonStrings[buttonStringIndex];
      printButtonString(ST77XX_YELLOW);
}

void SaveLocation::saveFile()
{
     String saveString =  String (valuesJB.getTojMl())  + String(" ") + String(valuesJB.deemsRatio) + String(" ") + String(valuesJB.pgRatio);
     //String saveString =  "3.5 5.00 65";
     littleFS.writeTextFile(filename, saveString);
     animateButtonProgressBar();
}

void SaveLocation::setValues(float (& valsArray) [])
{  
   isEmpty=false;
   tojMl       =  valsArray[0];
	deemsRatio  =  valsArray[1];
	pgRatio     =  valsArray[2];
   makeDisplayString();
}

void SaveLocation::select()
{  
   tft.drawRoundRect(248, yPos-20, 	67, 25, 7, ST77XX_YELLOW);
   printButtonString(ST77XX_YELLOW);
}

void SaveLocation::unSelect()
{
   tft.drawRoundRect(248, yPos-20, 	67, 25, 7, ST77XX_BLUE);
   printButtonString();
}

void SaveLocation::doClick()
{
      if (buttonStrDisplayed.equals("save" )) {saveFile  () ;}
 else if (buttonStrDisplayed.equals("load" )) {loadFile  () ;}
 else if (buttonStrDisplayed.equals("clear")) {deleteFile() ;} 

      buttonStrDisplayed = ButtonStrings[0];
      buttonStringIndex=0;
}

/**
populates the displayString String
*/
void SaveLocation::makeDisplayString()
{
   displayString = String(tojMl, 1) + String("ml ") + (utils.makeDratString(deemsRatio)) + String(" ") +
   String((int)(pgRatio)) + String("/") + String((int)(100-pgRatio));
}

void SaveLocation::setDisplayString(String displayStringIn)
{
   displayString = displayStringIn;
   if((displayString.equals(""))){isEmpty = true;}
}

void SaveLocation::printButtonString()
{
    printButtonString (ST77XX_BLUE);
}

void SaveLocation::loadFile()
{   
      valuesJB.setTojMl     (tojMl)    ;  
      valuesJB.deemsRatio = deemsRatio ;
      valuesJB.pgRatio    = pgRatio    ;
      animateButtonProgressBar();
}

void SaveLocation::animateButtonProgressBar()
{
   for(int pos=250; pos<314; ++pos)
      {//rawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
         uint8_t heit = 22; int startYposition = yPos-18;  //normal
         if (pos<252 || pos>311) {heit=16; startYposition=yPos-16;}  //rounded edges, make end vertical lines shorter and start a bit higher
         tft.drawFastVLine(pos, startYposition, heit, ST77XX_BLUE); //0x04df);
         setCursorForButtonString();
         tft.println      (buttonStrDisplayed);
         delay(3);
      }
      //delay(250);
}

void SaveLocation::setCursorForButtonString()
{
        if (buttonStrDisplayed.equals("save" )) {tft.setCursor(263,  yPos-3); }
   else if (buttonStrDisplayed.equals("load" )) {tft.setCursor(265,  yPos-2); }
   else if (buttonStrDisplayed.equals("clear")) {tft.setCursor(262,  yPos-2); }
}

void SaveLocation::printButtonString(uint16_t fgColor)
{  
      tft.setFont(&Roboto_Condensed_Italic_17);
      tft.setTextColor (fgColor, colorTextBG_darkBlue);
      setCursorForButtonString();
      tft.fillRoundRect(250, yPos-18, 	64, 22, 5, colorTextBG_darkBlue); //slightly smaller than the buttons to hide previous text
      tft.println      (buttonStrDisplayed);
}

void SaveLocation::printDisplayString()
{
   tft.setFont(&Open_Sans_Italic_21);  tft.setTextColor(ST77XX_CYAN, colorTextBG_darkBlue);
   tft.setCursor    (xPos, yPos); 
   tft.fillRoundRect(xPos, yPos-19, 195, 24, 3, colorTextBG_darkBlue);      //yPos-10 ->too low
   tft.println(displayString);  //littleFS.readFile(filenamey);
}

void SaveLocation::deleteFile()
{
   littleFS.deleteFile(filename); 
}
