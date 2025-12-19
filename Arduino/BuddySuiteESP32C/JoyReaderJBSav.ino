//19Dec2025
void JBSAV_JoystickReader::getSelectedRow()
{
	boolean yMoved=false; boolean xMoved=false;
	joystickXRaw = analogRead(JOYSTICK_X_PIN);  joystickYRaw = analogRead(JOYSTICK_Y_PIN);
  // Serial.print("here");
	if(isCentredXRaw(oldJoystickXRaw) && !(isCentredXRaw(joystickXRaw))) {xMoved=true;} //has moved in X
	if(isCentredYRaw(oldJoystickYRaw) && !(isCentredYRaw(joystickYRaw))) {yMoved=true;} //has moved in Y

	oldJoystickXRaw = joystickXRaw;
	oldJoystickYRaw = joystickYRaw;

	if (!(yMoved || xMoved ))  {return;} 

	if (xMoved && yMoved) //both moved, let's take whichever moved the most from centre
	{
		int yExcursion = abs(joystickCentreYRaw - joystickYRaw);
		int xExcursion = abs(joystickCentreXRaw - joystickXRaw);
		if (xExcursion>=yExcursion){xMoved=true; yMoved=false;} else {xMoved = false; yMoved=true;}
	}

if (millisSinceRowLastChanged > millis() - 250) {/**Serial.println (String("too recent, returning"));*/return;} 
 	  millisSinceRowLastChanged = millis();

	if (xMoved){jb_SaveScreenHndlr.joystickMoveX(joystickXRaw>joystickCentreXRaw);}
	if (yMoved)
	{
	 if(joystickYRaw > joystickCentreYRaw) 
	   {
			 rowSelectedJBSAV = (rowSelectedJBSAV<5?(rowSelectedJBSAV+1):0);
			 //Serial.println(String("rowSel inc=") + String(rowSelectedJBSAV));
			}
else {
				rowSelectedJBSAV = (rowSelectedJBSAV>0?(rowSelectedJBSAV-1):5);
				//Serial.println(String("rowSel decr=") + String(rowSelectedJBSAV));
			}
   jb_SaveScreenHndlr.setSelectedRow(rowSelectedJBSAV);
	}

	
     

	
	//Serial.println(String("JBSAV_JSREADER: xRaw=") + String(joystickXRaw) + String(", yRaw=") + String(joystickYRaw));
	/*readAndConvertJoystickX	 (joystickXRaw)  ;  //Converts raw X joystick input values ~0-4095 to ~ -10 to +10 in joystickXMapped, also populates joystickForce enum
 
 if (isCentredYRaw(oldJoystickYRaw) && !isCentredYRaw(joystickYRaw)) //has the joystick moved from Y centre?
 {
 	   if (millisSinceRowLastChanged > millis() - 350)  {return;} 
 	   millisSinceRowLastChanged = millis();
     if(joystickCentreYRaw > joystickYRaw){rowSelectedJB--;}
     else {rowSelectedJB++;}
   
    rowSelectedJB = rowSelectedJB%4;
    //Serial.println (String("y=") + String(joystickY) + String(", row=") + String(rowSelected) + String(", isCentred?") + (joystick.isCentred(joystickY))); 
 }
 oldJoystickYRaw=joystickYRaw;
	*/
}

	
      
void JBSAV_JoystickReader::readAndConvertJoystickX(const int & incRawX) {}