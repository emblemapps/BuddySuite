//03Jan2026
JBSAV_JoystickReader joystickReaderJBSAV;
JB_JoystickReader joystickReaderJB; //this order currentVals still isn't seeing joystickreader
CurrentValuesJB valuesJB;
JB_Calc 	 			jb_calc;
JB_LcdHdlr 			jb_lcdHandler;
JB_SaveLcdH     jb_SaveScreenHndlr;
uint8_t rowSelectedJB, oldRowJB=0;
uint8_t rowSelectedJBSAV=0;

/** called once at startup*/
void JB_Main::initJB() 
{
	joystickReaderJB.setup(); 
	jb_lcdHandler	.setup(true);
  jb_calc				.setup();
  valuesJB			.setup();
	jb_SaveScreenHndlr.setup(false); //showsplash
}
// timeJbSAV_Started=millis();  when 
void JB_Main::startJB()
{
	jb_lcdHandler.setupScreen();
	jb_calc.calculate(valuesJB, false);
  jb_lcdHandler.updateScreen(valuesJB, false);
}

void JB_Main::loop()
{
			ScreenShowing oldScreenShowing = jb_lcdHandler.screenShowing;
	    jsPushSwitchReader.checkForSwitchPush();
			if (oldScreenShowing==JB  && jb_lcdHandler.screenShowing==JBSAV) 
 			{
					// Serial.println("just opened save screen");
					timeJbSAV_Started=millis(); //this works
		  }

      if (jb_lcdHandler.screenShowing==JB)    {loopJB()   ;}
 else if (jb_lcdHandler.screenShowing==JBSAV) 
 {
	 long durationJBSavScreen =   millis() -  timeJbSAV_Started;
	 if(jsPushSwitchReader.wasPressedRecently()  || joystickReaderJBSAV.wasMovedRecently()) {timeJbSAV_Started=millis();}
	
	 long time_remaining_til_timeout_secs = (jb_SaveScreenHndlr.idleScreenTimeout_ms - durationJBSavScreen)/1000;
   if(time_remaining_til_timeout_secs<11)
	 {
	 		jb_SaveScreenHndlr.setStatusMessage (String(" TIMEOUT    ") + String ((time_remaining_til_timeout_secs<16 ? "0" : "")) + String(time_remaining_til_timeout_secs), &DSEG14_Modern_Bold_Italic_17);
 	 }
	if(durationJBSavScreen>jb_SaveScreenHndlr.idleScreenTimeout_ms)
	{
		jsPushSwitchReader.returnToJuiceBuddyScreen();
		return;	
	} 
	 loopJBSav();
 }
}

void JB_Main::loopJBSav()
{
	delay(50);
	joystickReaderJBSAV.getSelectedRow(); //0-back, 1-M1, 2-M2, 3-M3, 4-M4, 5-M5
	//Serial.println("JBMain::loopJBSav called");
	jb_SaveScreenHndlr.printStatusMessage();
}

void JB_Main::loopJB()
{
	joystickReaderJB.getSelectedRow(); //0 - dJuice Reqd >  1 - dRatio g/ml > 2 - PG/VG 3 - DMT
	if(rowSelectedJB!=oldRowJB)
   { 
  	  jb_lcdHandler.setSelectedField(rowSelectedJB);   
	    oldRowJB = rowSelectedJB; 
   }
 
 if(joystickReaderJB.isCentredYRaw() && !joystickReaderJB.isCentredXRaw())
 {
		 valuesJB.incrementValue(joystickReaderJB.getJoystickXMappedVal(), rowSelectedJB);
	   if(rowSelectedJB==3){jb_calc.calculateForDeemsWeight(valuesJB);}
	   else {jb_calc.calculate(valuesJB, false);}
	   jb_lcdHandler.updateScreen			(valuesJB, false);   
 }
  jb_lcdHandler.setJoystickMeter(joystickReaderJB.getJoystickXRaw(), valuesJB); 

 delay (0);
 }

void JB_Main::test()
{
//PG Ratio test
for (int16_t f=30; f>-1; f-=1)
	{
			valuesJB.pgRatio=f;
		 	jb_calc.calculate(valuesJB, false);
     	jb_lcdHandler.updateScreen(valuesJB, false);
     	delay (200);
	}
	//djuice req'd test
	for (float f=0; f<90; f+=0.9)
	{
			valuesJB.setTojMl(f);
		 	jb_calc.calculate(valuesJB, false);
     	jb_lcdHandler.updateScreen(valuesJB, false);
     	delay (200);
	}
}

//void printValues()
//{
//	Serial.println (String("TotalJuice Reqd=") + String(valuesJB.getTojMl()));
//	Serial.println (String("Deems Ratio=1:") + String(valuesJB.deemsRatio));
//  Serial.println (String("PG/VG=")+ String(valuesJB.pgRatio) + String("/") 		+ String ((100-valuesJB.pgRatio)));
//  Serial.println (String("PG=") 	+ String(valuesJB.pgMl) 	 + String(", (") 	+ String (valuesJB.weightPg_g) + String("g)"));
//  Serial.println (String("VG=") 	+ String(valuesJB.vgMl) 	 + String(", (") 	+ String (valuesJB.weightVg_g) + String("g)"));
//  Serial.println (String("Total juice Weight=") + String(valuesJB.totalWeightOfDJuice_g));
//  Serial.println (String("Solubility=") + String(valuesJB.solubility));
//}
