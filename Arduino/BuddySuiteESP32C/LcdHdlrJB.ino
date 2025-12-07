//07Dec2025
  // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library, you can override it here
  // Allowable spped depends on chip & wiring Too fast may get you a black screen some times, continuous.
  //tft.setSPISpeed(40000000);

void JB_LcdHdlr::setupScreen()
		{		
				//tft.setFont(&Open_Sans_Italic_23); 	// https://oleddisplay.squix.ch/
				//tft.setRotation(1);
				tft.fillScreen(colorTextBG_darkBlue);
				//////////////////////////////////////////////////////////////////////////////////
				tft.drawRoundRect(0, 0, 	tft.width(), tft.height()-135, 10, colorText1);  //border line top
				tft.drawRoundRect(0, 108, tft.width(), tft.height()-110, 10, colorText2);//border line botton
		  	//////////////////////////////////////////////////////////////////////////////////
				uint8_t yOffset = 30; // uint8_t lineSpacing=30;uint8_t xMarginLeftPixels = 12;
				tft.setTextColor(colorText1, colorTextBG_darkBlue);
				tft.setCursor(xMarginLeftPixels, yOffset); tft.print("dJuice Req'd");  
				
				uint16_t strLenPixels = getStringWidthPixels(&Open_Sans_Italic_23, mlStr);
				tft.setCursor(tft.width() - strLenPixels - xMarginRightPixels, yOffset);
				tft.print(mlStr);  
				
				yOffset+=lineSpacing;
				tft.setCursor(xMarginLeftPixels, yOffset); tft.print("dRatio g/ml");
				yOffset+=lineSpacing;
				tft.setCursor(xMarginLeftPixels, yOffset); tft.print("PG/VG");
				/////////////////////////////////////////////////////////////////////////////////////////////////
				tft.setTextColor(colorText2, colorTextBG_darkBlue); 
				yOffset+=lineSpacing+15;
  			tft.setCursor(xMarginLeftPixels, yOffset); tft.print("PG") ; tft.setCursor(xOffsetMl, yOffset); tft.print("ml"); tft.setCursor(297, yOffset); tft.print("g");
  			yOffset+=lineSpacing;
  			tft.setCursor(xMarginLeftPixels, yOffset); tft.print("VG") ; tft.setCursor(xOffsetMl, yOffset); tft.print("ml"); tft.setCursor(297, yOffset); tft.print("g");
  			yOffset+=lineSpacing;
  			tft.setCursor(xMarginLeftPixels, yOffset); tft.print("DMT"); tft.setCursor(xOffsetMg, yOffset); tft.print("mg");
				yOffset+=lineSpacing;

				tft.setTextColor(ST77XX_CYAN, colorTextBG_darkBlue); 
  			tft.setCursor(xMarginLeftPixels, yOffset); 	tft.print("Total");  
  			tft.setCursor(xOffsetMg, yOffset);					tft.print("g");
  			olubleStrLenPixels = getStringWidthPixels(&Open_Sans_Italic_23, olubleStr);
  			tft.setCursor(tft.width() - xMarginRightPixels - olubleStrLenPixels, yOffset); tft.print(olubleStr);

  			quasi_StrLenPixels = getStringWidthPixels(&Open_Sans_Italic_23, quasi_Str); //housekeeping for the solubility display update
  			setSelectedField(0);
		}

void JB_LcdHdlr::updateScreen(CurrentValuesJB & values)  
{
	tft.setTextColor			 (colorText1, colorTextBG_darkBlue);
	setDjuiceRequiredField (values);
	setDRatField 					 (values);
	setPgRatField					 (values);
	tft.setTextColor		   (colorText2, colorTextBG_darkBlue); 
	setPgMlOrVgMlField     (values, true);
	setPgMlOrVgMlField     (values, false);
	setDeemsMgField        (values);
	tft.setTextColor			 (ST77XX_CYAN, colorTextBG_darkBlue);
	setSolubilityField     (values);
	setTotalJuiceGramsField(values);
}
void JB_LcdHdlr::setSelectedField(uint8_t sel) //0-dJuice Reqd, 1-dRatio g/ml, 2-PG/VG, 3-DMT
{
	const int yHeight = 22; 	const int xOffset 	= 200; 	const int xLen 		= 25;
	int currSel=0;
	for (int yOffset=30; yOffset<91; yOffset+=30)
		{
	   tft.fillTriangle(xOffset, yOffset, xOffset, yOffset-yHeight, xOffset+xLen,  yOffset- (yHeight/2),  (sel==currSel? colorCursor : colorTextBG_darkBlue));
	   ++currSel;
		}
	int yOffset = 190;	
	tft.fillTriangle(xOffset-8, yOffset, xOffset-8+xLen, (yOffset-yHeight/2), xOffset-8+xLen, (yOffset+yHeight/2) ,  (sel==currSel? ST77XX_BLUE : colorTextBG_darkBlue)); 
} 

void JB_LcdHdlr::setDjuiceRequiredField(CurrentValuesJB & values)
	{
			if (oldTojMl == values.getTojMl()) {return;}   //return if this field isn't being changed, saves display flicker
			uint8_t yOffset = 30;  
			float needed 		= values.getTojMl();
			oldTojMl 				= needed;
			String outStr 	= String(needed,1); //"0.1" "9.3" "20.8"	
			
			uint16_t outStrLenPixels = getStringWidthPixels(&Open_Sans_Italic_23, outStr);
			uint16_t mlStrLenPixels  = getStringWidthPixels(&Open_Sans_Italic_23,  mlStr);
			uint8_t  rectXlen 			 = 51;
			tft.fillRect (tft.width() - textToUnitGapPixels - mlStrLenPixels  - xMarginRightPixels- rectXlen, yOffset-20, rectXlen, 24, colorTextBG_darkBlue); //ST77XX_RED colorTextBG_darkBlue
			tft.setCursor(tft.width() - outStrLenPixels - textToUnitGapPixels - mlStrLenPixels  - xMarginRightPixels, yOffset);
			tft.print(outStr);  
	}
		
void JB_LcdHdlr::setDRatField(CurrentValuesJB & values)
		{
			if(oldDeemsRatio==values.deemsRatio){return;}
			oldDeemsRatio 	= values.deemsRatio;
			uint8_t yOffset = 60;  uint8_t xOffset=245;
			uint8_t dRatX10 = values.deemsRatio * 10;
			uint8_t prefix=1;
     	if(dRatX10<10)
     	{
       	prefix=2;
       	dRatX10 = dRatX10 *2;
     	} 
		 	uint8_t 	digit1 = (dRatX10/10);
     	uint8_t 	digit2 = dRatX10 - (digit1*10);
     	String 		outStr = String(prefix) + String(":")+ String(digit1) + String(".") + String(digit2);	
			uint16_t 	outStrLenPixels = getStringWidthPixels(&Open_Sans_Italic_23, outStr);
     	uint8_t 	rectXlen = 70;
     	tft.fillRect (tft.width() - xMarginRightPixels - rectXlen, yOffset-20, rectXlen, 24, colorTextBG_darkBlue ); // ST77XX_BLACK colorTextBG_darkBlue
			tft.setCursor(tft.width() - outStrLenPixels - xMarginRightPixels, yOffset);
			tft.print(outStr);  
		}
		
		void JB_LcdHdlr::setPgRatField(CurrentValuesJB & values)
		{
			if(oldPgRatio==values.pgRatio){return;} //return if this display isn't being changed.  Saves flicker.
			oldPgRatio=values.pgRatio;
			uint8_t yOffset = 90;  
			uint8_t pgPerc 	= values.pgRatio;
			uint8_t vgPerc 	= 100-pgPerc;
      String outStr = String(pgPerc) + ('/') + String(vgPerc);  
      uint16_t 	outStrLenPixels = getStringWidthPixels(&Open_Sans_Italic_23, outStr);	
      uint8_t 	rectXlen = 70;
     	tft.fillRect (tft.width() - xMarginRightPixels - rectXlen, yOffset-20, rectXlen, 24, colorTextBG_darkBlue); // ST77XX_RED colorTextBG_darkBlue
      tft.setCursor(tft.width() - outStrLenPixels - xMarginRightPixels, yOffset);
			tft.print(outStr);	
		}
		
		void JB_LcdHdlr::setPgMlOrVgMlField(CurrentValuesJB & values, boolean PG)
		{
			if ( PG && ((roundf(oldPgMl*100)/100.0)==roundf(values.pgMl*100)/100.0)) 				{return;}
			else  if (!PG && ((roundf(oldVgMl*100)/100.0)==roundf(values.vgMl*100)/100.0))  {return;}

			uint8_t yOffset = 135; 
			if(PG) 	{oldPgMl=values.pgMl;}
			else		{yOffset = 165; 
							 oldVgMl=values.vgMl;}

			float ml 		 = (PG? values.pgMl:values.vgMl );
			String MlStr = String(ml,2); 
			uint16_t mlStrLenPixels = getStringWidthPixels(&Open_Sans_Italic_23, MlStr);
			uint8_t rectXlen = 70;
			tft.fillRect (xOffsetMl - rectXlen-textToUnitGapPixels,		yOffset-20, rectXlen, 24, colorTextBG_darkBlue ); //ST77XX_RED colorTextBG_darkBlue
			tft.setCursor(xOffsetMl - textToUnitGapPixels - mlStrLenPixels, yOffset); tft.print(MlStr);
			//////////////////////////////////////////////////
			float gWeight = (PG?ml*1.036:ml*1.261);
    	String gStr;
    	if(gWeight<10){gStr  =String(gWeight,2);}
    	else    			{gStr  =String(gWeight,1);}
			
			uint16_t strLenPixels = getStringWidthPixels(&Open_Sans_Italic_23, gStr); 
			tft.fillRect (tft.width()- xMarginRightPixels - textToUnitGapPixels - rectXlen-12,	yOffset-20, rectXlen, 24,colorTextBG_darkBlue ); //ST77XX_RED colorTextBG_darkBlue
  		tft.setCursor(tft.width()- xMarginRightPixels - strLenPixels - textToUnitGapPixels-12, yOffset); 	tft.print(gStr);    
		}		 
		
		void JB_LcdHdlr::setDeemsMgField(const CurrentValuesJB & values)
		{
			if(oldDeemsMg==values.deemsMg){return;}  //return if this display isn't being changed.  Saves flicker.
			oldDeemsMg = values.deemsMg;
			uint8_t 	yOffset = 195;
			uint16_t  deemsMg = values.deemsMg;
			String 		mgDeems = String(deemsMg);
			uint16_t 	strLenPixels = getStringWidthPixels(&Open_Sans_Italic_23,mgDeems);
			uint8_t 	rectXlen = 70;
			tft.fillRect (xOffsetMg - rectXlen-textToUnitGapPixels,		  yOffset-20, rectXlen, 24, colorTextBG_darkBlue); //ST77XX_RED
			tft.setCursor(xOffsetMg - strLenPixels-textToUnitGapPixels, yOffset); 	tft.print(mgDeems); 
		}

		void JB_LcdHdlr::setSolubilityField(const CurrentValuesJB & values)
		{
			if (oldSolubility==values.solubility) {return;}
			oldSolubility=values.solubility;
			
			uint8_t yOffset = 225; uint8_t xOffset = 235;//xoffset is for the "oluble" printed at setupscreen()
			//solubility=NOT_SOLUBLE;
			String solStr = "S"; String upperLineString = "";
			switch(values.solubility)
  		{  
    		case PART_SOLUBLE:  upperLineString = quasi_Str; tft.drawRoundRect(0, 108, tft.width(), tft.height()-110, 10, 0xFE00);	break;
    		case SOLUBLE:       tft.drawRoundRect(0, 108, tft.width(), tft.height()-110, 10, colorText2);														break;
    		case NOT_SOLUBLE:   solStr = "Ins";  tft.drawRoundRect(0, 108, tft.width(), tft.height()-110, 10, ST77XX_RED);					break;
    		default:            																																																		break;
  		}	
   		uint16_t  strLenPixels = getStringWidthPixels(&Open_Sans_Italic_23,solStr);
   		uint8_t 	xrectXlen 	 = 40;//35
  		tft.fillRect (tft.width() - xMarginRightPixels - olubleStrLenPixels - xrectXlen,    yOffset-20,  xrectXlen, 24, colorTextBG_darkBlue); //ST77XX_RED colorTextBG_darkBlue
  		tft.setCursor(tft.width()	- xMarginRightPixels - olubleStrLenPixels - strLenPixels, yOffset); 	tft.print(solStr); 
	  	xrectXlen =   quasi_StrLenPixels+5;
  		tft.fillRect (tft.width() - xMarginRightPixels - xrectXlen, yOffset-27-20,  xrectXlen, 24, colorTextBG_darkBlue); //ST77XX_RED colorTextBG_darkBlue
  		if(values.solubility==SOLUBLE) {tft.drawRGBBitmap(200,205, thumbsup_23x24, 23,24);}
  		tft.setCursor(tft.width() - xMarginRightPixels - quasi_StrLenPixels, yOffset-27); 					  tft.print(upperLineString); 
 	}
 		
void JB_LcdHdlr::setTotalJuiceGramsField(const CurrentValuesJB & values)
{	
	if  ((roundf(oldTotalWeightOfDJuice_g*10)/10.0)==(roundf(values.totalWeightOfDJuice_g*10)/10.0)) 	{return;}
	oldTotalWeightOfDJuice_g = values.totalWeightOfDJuice_g;
	uint8_t yOffset = 225; 
	float totalWeightOfDJuice_g = values.totalWeightOfDJuice_g;
	String out=String(totalWeightOfDJuice_g,(totalWeightOfDJuice_g>=10?1:2));
	uint16_t 	strLenPixels = getStringWidthPixels(&Open_Sans_Italic_23,out);
	uint8_t   rectXlen     = 60;
	tft.fillRect (xOffsetMg - rectXlen-textToUnitGapPixels,	yOffset-21, rectXlen, 24, colorTextBG_darkBlue); //ST77XX_RED
  tft.setCursor(xOffsetMg-strLenPixels-textToUnitGapPixels, yOffset); 				tft.print(out);
}		
