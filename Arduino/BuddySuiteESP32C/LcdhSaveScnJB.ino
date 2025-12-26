//26Dec2025
void JB_SaveLcdH::setupScreen(CurrentValuesJB & valuesJB)
{
        tft.setRotation  (1);
		tft.fillScreen   (colorTextBG_darkBlue);
        tft.setCursor    ((xMarginRightPixels-4), 54);
        tft.setTextColor (ST77XX_YELLOW, colorTextBG_darkBlue);
        tft.setFont      (&Open_Sans_Condensed_Bold_19);
        tft.print        ("Current setting: ");  
        currentSettingsString="";
        printCurrentSettingsString(valuesJB, false);
        tft.setFont      (&Open_Sans_Italic_23); 	// https://oleddisplay.squix.ch/
        tft.drawRoundRect(0,  0, tft.width(), tft.height(), 10, colorText1);  //yellow border line
        tft.drawRGBBitmap(51, 8, saveIcon26x26, 26,26);
        tft.setCursor    (88, 28);
        tft.setTextColor (colorText2, colorTextBG_darkBlue);
        tft.println      ("Save/Load Juice");
        tft.drawRoundRect(248, 60, 	67, 25, 7, ST77XX_BLUE); //back button
        tft.setTextColor (ST77XX_BLUE, colorTextBG_darkBlue);
        tft.setCursor    (264, 78);
        tft.setFont      (&Roboto_Condensed_Italic_17);
        tft.print        ("back");
        jb_lcdHandler.screenShowing=JBSAV;  //JB, JBSAV
        displaySaveLocationsFramework();
        populateSaveLocationsArray   ();
        displaySaveLocationsStrings  (false);
        setSelectedRow (0); 
        rowSelectedJBSAV=0;
}

/**
Prints the M1: to M5:, plus the round rectangle on the RH
*/
void JB_SaveLcdH::displaySaveLocationsFramework()
{
    tft.setTextColor(colorText1,colorTextBG_darkBlue);
    tft.setFont (&Open_Sans_Condensed_Bold_19);
    int yOffset=110;
    for(uint8_t memloc = 1; memloc <6; ++memloc)
      { 
            saveLocations[memloc-1].oldDisplayString =""; //so it prints out the DisplayString the first time the display appears
            tft.setCursor (xMarginRightPixels-3, yOffset);
            tft.println   (String ("M") + String(memloc) + String(":"));
            tft.drawRoundRect(248, yOffset-20, 	67, 25, 7, ST77XX_BLUE); 
            yOffset+=lineSpacing;
      }
} 


void JB_SaveLcdH::setSelectedRow(int selectedRow)
{			
    tft.setFont(&Roboto_Condensed_Italic_17);
    tft.setTextColor (ST77XX_BLUE, colorTextBG_darkBlue);
    tft.setCursor(264, 78); tft.print("back");
    tft.drawRoundRect(248, 60, 	67, 25, 7, ST77XX_BLUE); //back button
     
    for (uint8_t savloc = 0; savloc <5; ++savloc)
    {
        if(saveLocations[savloc].selected) //unselect only those that are selected, saves display flicker
        {
            saveLocations[savloc].unSelect();
        }
    }

    switch (selectedRow)
     {
        case 0: tft.setTextColor(ST77XX_YELLOW, colorTextBG_darkBlue); tft.setCursor(264, 78); tft.print("back"); tft.drawRoundRect(248, 60, 	67, 25, 7, ST77XX_YELLOW); break;
        case 1:   
        case 2:
        case 3:
        case 4:
        case 5: saveLocations[selectedRow-1].select(); break;
     }
}

void JB_SaveLcdH::populateSaveLocationsArray()
{
    String filenames[5] = {"<Empty>", "<Empty>", "<Empty>", "<Empty>", "<Empty>"};
    littleFS.listSavFiles (filenames);   //gets the filenames into the filenames array
    
    for(uint8_t memloc = 1; memloc <6; ++memloc)
    {
       if((filenames[memloc-1].equals("<Empty>")))
       {
            saveLocations[memloc-1].setDisplayString("");
       }
       else
       {
            String valuesFromFile           = littleFS.readFile(filenames[memloc-1]);
            float valFloats[]               = {0,0,0};  // "3.5 3.00 70" 
            splitToFloats(valuesFromFile, valFloats, 3); //split to actual floats
            saveLocations[memloc-1].setValues(valFloats);
       }
       saveLocations[memloc-1].printButtonString();
    }
}	

void JB_SaveLcdH::displaySaveLocationsStrings(boolean animate)
{
    for(uint8_t memloc = 1; memloc <6; ++memloc)
    {
        saveLocations[memloc-1].printDisplayString(animate);
    }
}

void JB_SaveLcdH::doClick()
{
    saveLocations[rowSelectedJBSAV-1].doClick();
    populateSaveLocationsArray();
    displaySaveLocationsStrings(true);
    printCurrentSettingsString(valuesJB, true);//update in case of load
}

void JB_SaveLcdH::joystickMoveX(boolean right)
{   
   if(rowSelectedJBSAV>0)
   {
    saveLocations[rowSelectedJBSAV-1].joystickMoveX(right);
   }
}

void JB_SaveLcdH::setStatusMessage(String & message)
{
    statusMessage = message;
}

unsigned long timeStatusMessageFirstDisplayed=0;
boolean messageDisplayed=false;
void JB_SaveLcdH::printStatusMessage()
{
        if (statusMessage.equals("")){messageDisplayed=false;return;} //no message, return
        //if we get here we must have a non-empty message to display with messageDisplayed true or false (not yet printed)
        if(!messageDisplayed) //display message once at the start
        {  
            messageDisplayed = true;
            timeStatusMessageFirstDisplayed = millis(); 
            tft.setTextColor (ST77XX_ORANGE, colorTextBG_darkBlue);
            tft.setCursor    (7, 78);
            tft.setFont      (&Roboto_Condensed_Italic_17);
            tft.print        (statusMessage);
        }
        
        if ( (millis()-timeStatusMessageFirstDisplayed) > 2000)
        {
        tft.fillRoundRect(4, 65, 242, 21, 2, colorTextBG_darkBlue);//colorTextBG_darkBlue);
        statusMessage="";
        }
}

//String old
void JB_SaveLcdH::printCurrentSettingsString(CurrentValuesJB & valuesJB, boolean flashText)
{
        if (valuesJB.toString().equals(currentSettingsString)) { return; }
        currentSettingsString = valuesJB.toString();
        tft.setFont      (&Open_Sans_Condensed_Bold_19);
        tft.setTextColor (0xddff, colorTextBG_darkBlue);
        tft.fillRoundRect(148, 37, 168, 20, 3, colorTextBG_darkBlue);  // tft.drawRoundRect(248, 60, 	67, 25, 7, ST77XX_BLUE); //back button
        for( uint8_t flsh = 0; flsh<50; ++flsh)  //50 - just more than flashcount, it never reaches 50
        {
                 tft.setCursor    (152, 54); 
                 tft.print      (valuesJB.toString());
                 if (!flashText || flsh==4) {break;}
                 delay(60);  
                 tft.fillRoundRect(148, 37, 168, 20, 3, colorTextBG_darkBlue); 
                 delay(60);    
        }  
}

// Back To You or I walk Away (2nd try)- Zakirovek & Bakhadiroff, Kasimoff (2nd try)
