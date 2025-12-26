//26Dec2025
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

	movedRecently=true;

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
}
     	 
boolean JBSAV_JoystickReader::wasMovedRecently()
		 {
			  boolean ret  = movedRecently;
  			movedRecently=false;   //done like this so we don't need to reset it
  			return ret;
		 }
		      
void JBSAV_JoystickReader::readAndConvertJoystickX(const int & incRawX) {}
