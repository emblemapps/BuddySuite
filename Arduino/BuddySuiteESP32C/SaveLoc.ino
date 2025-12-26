//26Dec2025
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
      oldSelected = selected;
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
     if (displayString.equals(valuesJB.toString()))
     {
         String msgStr=String("Settings already stored in M") + String (filename.substring(2,3));
         jb_SaveScreenHndlr.setStatusMessage(msgStr);
         return;
     }
     littleFS.writeTextFile(filename, saveString);
     String msgStr=String("Settings saved in M") + String (filename.substring(2,3));
     jb_SaveScreenHndlr.setStatusMessage(msgStr);
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
   oldSelected = selected;
   selected = true;
   tft.drawRoundRect(248, yPos-20, 	67, 25, 7, ST77XX_YELLOW);
   printButtonString(ST77XX_YELLOW);
}

void SaveLocation::unSelect()
{
   oldSelected = selected;
   selected = false;    
   tft.drawRoundRect(248, yPos-20, 	67, 25, 7, ST77XX_BLUE);
   printButtonString();
}

void SaveLocation::printButtonString(uint16_t fgColor)
{  
  if(oldButtonString.equals(buttonStrDisplayed) && oldSelected && selected)
  {
      return;
  }
   oldButtonString = buttonStrDisplayed;
   tft.setFont      (&Roboto_Condensed_Italic_17);
   tft.setTextColor (fgColor, colorTextBG_darkBlue);
   setCursorForButtonString();
   tft.fillRoundRect(250, yPos-18, 	64, 22, 5, colorTextBG_darkBlue); //slightly smaller than the buttons to hide previous text
   tft.println      (buttonStrDisplayed);
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
      if (displayString.equals(jb_SaveScreenHndlr.currentSettingsString)) 
      { 
         String msgStr = "Saved settings already loaded!";
         jb_SaveScreenHndlr.setStatusMessage(msgStr);
         return; 
      } //trying to load what's already loaded

      valuesJB.setTojMl     (tojMl)    ;  
      valuesJB.deemsRatio = deemsRatio ;
      valuesJB.pgRatio    = pgRatio    ;
      animateButtonProgressBar()       ;
      String msgStr=String("Settings loaded from M") + String (filename.substring(2,3));
      jb_SaveScreenHndlr.setStatusMessage(msgStr);
}

void SaveLocation::animateButtonProgressBar()
{
   for(int pos=250; pos<314; ++pos)
      {
         uint8_t heit = 22; int startYposition = yPos-18;  //normal
         if (pos<252 || pos>311) {heit=16; startYposition=yPos-16;}  //rounded edges, make end vertical lines shorter and start a bit higher
         tft.drawFastVLine(pos, startYposition, heit, ST77XX_BLUE); //0x04df);
         setCursorForButtonString();
         tft.println      (buttonStrDisplayed);
         delay(3);
      }
}

void SaveLocation::setCursorForButtonString()
{
        if (buttonStrDisplayed.equals("save" )) {tft.setCursor(263,  yPos-3); }
   else if (buttonStrDisplayed.equals("load" )) {tft.setCursor(265,  yPos-2); }
   else if (buttonStrDisplayed.equals("clear")) {tft.setCursor(262,  yPos-2); }
}

void SaveLocation::printDisplayString(boolean animate)
{
   if (displayString.equals(oldDisplayString)) {return;}
   oldDisplayString = displayString;
   tft.setFont(&Open_Sans_Italic_21);  tft.setTextColor(ST77XX_CYAN, colorTextBG_darkBlue);
   tft.setCursor    (xPos, yPos); 
   tft.fillRoundRect(xPos, yPos-19, 195, 24, 3, colorTextBG_darkBlue);      //yPos-10 ->too low

   if (animate)
   for(int i=0; i < displayString.length(); i++ )
    {
      char c = displayString[i];
      tft.print(c);
      delay(10);
   }
   else
   {
      tft.println(displayString);  
   }
}

void SaveLocation::deleteFile()
{
   littleFS.deleteFile(filename); 
   String msgStr=String("M") + String (filename.substring(2,3)) + String(" cleared");
   jb_SaveScreenHndlr.setStatusMessage(msgStr);
}
