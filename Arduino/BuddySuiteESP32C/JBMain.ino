//07Dec2025

JB_JoystickReader joystickReader; //this order currentVals still isn't seeing joystickreader
CurrentValuesJB valuesJB;
JB_Calc 	 			jb_calc;
JB_LcdHdlr 			jb_lcdHandler;
JB_SaveLcdH     jb_SaveScreenHndlr;
uint8_t rowSelected, oldRow=0;

/** called once at startup*/
void JB_Main::initJB() 
{
	joystickReader.setup();
	jb_lcdHandler	.setup(true);
  jb_calc				.setup();
  valuesJB			.setup();
	jb_SaveScreenHndlr.setup(false); //showsplash
}

void JB_Main::startJB()
{
	jb_lcdHandler.setupScreen();
	jb_calc.calculate(valuesJB, false);
  jb_lcdHandler.updateScreen(valuesJB);
	delay(1000);
	jb_SaveScreenHndlr.setupScreen();
	delay(100000);
}

void JB_Main::loopJB()
{
	joystickReader.getSelectedRow(rowSelected); //0 - dJuice Reqd >  1 - dRatio g/ml > 2 - PG/VG 3 - DMT
	if(rowSelected!=oldRow)
   { 
  	  jb_lcdHandler.setSelectedField(rowSelected);   
	    oldRow = rowSelected; 
   }
 
 if(joystickReader.isCentredYRaw() && !joystickReader.isCentredXRaw() )
 {
		 valuesJB.incrementValue(joystickReader.getJoystickXMappedVal(), rowSelected);
	   if(rowSelected==3){jb_calc.calculateForDeemsWeight(valuesJB);}
	   else {jb_calc.calculate(valuesJB, false);}
	   jb_lcdHandler.updateScreen			(valuesJB);   
 }
  jb_lcdHandler.setJoystickMeter(joystickReader.joystickXRaw, valuesJB); 

	//boolean hi = digitalRead(JOYSTICK_PUSHSW_PIN);
  //Serial.println(String(hi));
  
 delay (0);
 }

void JB_Main::test()
{
//PG Ratio test
for (int16_t f=30; f>-1; f-=1)
	{
			valuesJB.pgRatio=f;
		 	jb_calc.calculate(valuesJB, false);
     	jb_lcdHandler.updateScreen(valuesJB);
     	delay (200);
	}

/**
////dratio test
for (float f=0; f<21; f+=0.5)
	{
			valuesJB.deemsRatio=f;
		 	jb_calc.calculate(valuesJB, false);
     	jb_lcdHandler.updateScreen(valuesJB);
     	delay (100);
	}
*/
	//djuice req'd test
	for (float f=0; f<90; f+=0.9)
	{
			valuesJB.setTojMl(f);
		 	jb_calc.calculate(valuesJB, false);
     	jb_lcdHandler.updateScreen(valuesJB);
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
